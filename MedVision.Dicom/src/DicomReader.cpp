#include "medvision/dicom/DicomReader.h"
#include "medvision/dicom/DicomDictionary.h"
#include "medvision/dicom/TransferSyntax.h"
#include <fstream>
#include <cstring>

namespace medvision
{
	namespace dicom
	{

		DicomReader::DicomReader()
			: buffer_(nullptr)
			, bufferLength_(0)
			, bufferPos_(0)
			, isExplicitVR_(true)
			, isBigEndian_(false)
			, hasPreamble_(false)
		{
		}

		DicomReader::~DicomReader()
		{
			if (file_.is_open())
			{
				file_.close();
			}
		}

		bool DicomReader::ReadFile(const std::string& filePath, DicomDataSet& dataSet)
		{
			file_.open(filePath, std::ios::binary);
			if (!file_.is_open())
			{
				SetError("Cannot open file: " + filePath);
				return false;
			}

			dataSet.Clear();

			if (!ReadPreamble())
			{
				return false;
			}

			if (!ReadMetaInformation(dataSet))
			{
				return false;
			}

			if (!ReadDataSet(dataSet))
			{
				return false;
			}

			file_.close();
			return true;
		}

		bool DicomReader::ReadBuffer(const uint8_t* buffer, size_t length, DicomDataSet& dataSet)
		{
			buffer_ = buffer;
			bufferLength_ = length;
			bufferPos_ = 0;

			dataSet.Clear();

			if (!ReadPreamble())
			{
				return false;
			}

			if (!ReadMetaInformation(dataSet))
			{
				return false;
			}

			if (!ReadDataSet(dataSet))
			{
				return false;
			}

			return true;
		}

		bool DicomReader::ReadPreamble()
		{
			uint8_t preamble[128];
			if (!ReadBytes(preamble, 128))
			{
				SetError("Cannot read preamble");
				return false;
			}

			char dicm[4];
			if (!ReadBytes(reinterpret_cast<uint8_t*>(dicm), 4))
			{
				SetError("Cannot read DICM prefix");
				return false;
			}

			if (std::memcmp(dicm, "DICM", 4) == 0)
			{
				hasPreamble_ = true;
			}
			else
			{
				SetError("Not a valid DICOM file (missing DICM prefix)");
				return false;
			}

			return true;
		}

		bool DicomReader::ReadMetaInformation(DicomDataSet& dataSet)
		{
			// Meta information is always Explicit VR Little Endian
			isExplicitVR_ = true;
			isBigEndian_ = false;

			// Read meta information elements (group 0x0002)
			while (true)
			{
				DicomTag tag;
				if (!ReadTag(tag))
				{
					return false;
				}

				// End of meta information
				if (tag.GetGroup() != 0x0002)
				{
					// Rewind to re-read this tag in the main dataset
					if (file_.is_open())
					{
						file_.seekg(-4, std::ios::cur);
					}
					else
					{
						bufferPos_ -= 4;
					}
					break;
				}

				VR vr;
				if (!ReadVR(vr))
				{
					return false;
				}

				uint32_t length;
				if (!ReadLength(length, vr))
				{
					return false;
				}

				std::vector<uint8_t> data;
				if (!ReadData(data, length))
				{
					return false;
				}

				DicomElement element(tag, vr);
				element.SetData(data);
				dataSet.AddElement(element);

				// Extract transfer syntax
				if (tag == DicomTag::TransferSyntaxUID)
				{
					std::string tsUID;
					element.GetString(tsUID);
					transferSyntax_ = tsUID;
					isExplicitVR_ = TransferSyntax::IsExplicitVR(tsUID);
					isBigEndian_ = TransferSyntax::IsBigEndian(tsUID);
				}
			}

			return true;
		}

		bool DicomReader::ReadDataSet(DicomDataSet& dataSet)
		{
			// Read until end of file/buffer
			while (true)
			{
				if (file_.is_open())
				{
					if (file_.eof() || file_.peek() == EOF)
					{
						break;
					}
				}
				else
				{
					if (bufferPos_ >= bufferLength_)
					{
						break;
					}
				}

				if (!ReadDataElement(dataSet))
				{
					// May reach end of data naturally
					break;
				}
			}

			return true;
		}

		bool DicomReader::ReadDataElement(DicomDataSet& dataSet)
		{
			DicomTag tag;
			if (!ReadTag(tag))
			{
				return false;
			}

			VR vr = VR::UN;

			if (isExplicitVR_)
			{
				if (!ReadVR(vr))
				{
					return false;
				}
			}
			else
			{
				// Use dictionary to determine VR
				vr = DetermineImplicitVR(tag);
			}

			uint32_t length;
			if (!ReadLength(length, vr))
			{
				return false;
			}

			// Skip pixel data and sequences for now (basic implementation)
			if (tag == DicomTag::PixelData || vr == VR::SQ)
			{
				if (length == 0xFFFFFFFF)
				{
					// Undefined length - skip for now
					SetError("Undefined length not fully supported yet");
					return false;
				}

				// Skip the data
				if (file_.is_open())
				{
					file_.seekg(length, std::ios::cur);
				}
				else
				{
					bufferPos_ += length;
				}
				return true;
			}

			std::vector<uint8_t> data;
			if (!ReadData(data, length))
			{
				return false;
			}

			DicomElement element(tag, vr);
			element.SetData(data);
			dataSet.AddElement(element);

			return true;
		}

		bool DicomReader::ReadTag(DicomTag& tag)
		{
			uint16_t group = ReadUInt16();
			uint16_t element = ReadUInt16();
			tag = DicomTag(group, element);
			return true;
		}

		bool DicomReader::ReadVR(VR& vr)
		{
			char vrStr[3] = { 0 };
			if (!ReadBytes(reinterpret_cast<uint8_t*>(vrStr), 2))
			{
				return false;
			}
			vr = VRUtils::FromString(std::string(vrStr, 2));
			return true;
		}

		bool DicomReader::ReadLength(uint32_t& length, VR vr)
		{
			if (isExplicitVR_)
			{
				if (VRUtils::HasExplicitLength(vr))
				{
					// 2 bytes reserved, 4 bytes length
					ReadUInt16(); // Skip reserved bytes
					length = ReadUInt32();
				}
				else
				{
					// 2 bytes length
					length = ReadUInt16();
				}
			}
			else
			{
				// Implicit VR always uses 4-byte length
				length = ReadUInt32();
			}
			return true;
		}

		bool DicomReader::ReadData(std::vector<uint8_t>& data, uint32_t length)
		{
			if (length == 0)
			{
				data.clear();
				return true;
			}

			data.resize(length);
			return ReadBytes(data.data(), length);
		}

		uint16_t DicomReader::ReadUInt16()
		{
			uint8_t bytes[2];
			ReadBytes(bytes, 2);

			if (isBigEndian_)
			{
				return (static_cast<uint16_t>(bytes[0]) << 8) | bytes[1];
			}
			else
			{
				return bytes[0] | (static_cast<uint16_t>(bytes[1]) << 8);
			}
		}

		uint32_t DicomReader::ReadUInt32()
		{
			uint8_t bytes[4];
			ReadBytes(bytes, 4);

			if (isBigEndian_)
			{
				return (static_cast<uint32_t>(bytes[0]) << 24) |
					(static_cast<uint32_t>(bytes[1]) << 16) |
					(static_cast<uint32_t>(bytes[2]) << 8) |
					bytes[3];
			}
			else
			{
				return bytes[0] |
					(static_cast<uint32_t>(bytes[1]) << 8) |
					(static_cast<uint32_t>(bytes[2]) << 16) |
					(static_cast<uint32_t>(bytes[3]) << 24);
			}
		}

		bool DicomReader::ReadBytes(uint8_t* buffer, size_t count)
		{
			if (file_.is_open())
			{
				file_.read(reinterpret_cast<char*>(buffer), count);
				return file_.good() || file_.eof();
			}
			else
			{
				if (bufferPos_ + count > bufferLength_)
				{
					return false;
				}
				std::memcpy(buffer, buffer_ + bufferPos_, count);
				bufferPos_ += count;
				return true;
			}
		}

		void DicomReader::SetError(const std::string& error)
		{
			lastError_ = error;
		}

		VR DicomReader::DetermineImplicitVR(const DicomTag& tag) const
		{
			VR vr = DicomDictionary::GetVR(tag);
			if (vr == VR::UN)
			{
				// Unknown tag - default to OB
				return VR::OB;
			}
			return vr;
		}

	} // namespace dicom
} // namespace medvision
