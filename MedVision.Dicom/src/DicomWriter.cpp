#include "medvision/dicom/DicomWriter.h"
#include "medvision/dicom/TransferSyntax.h"
#include <cstring>

namespace medvision
{
	namespace dicom
	{

		DicomWriter::DicomWriter()
			: outputBuffer_(nullptr)
			, isExplicitVR_(true)
			, isBigEndian_(false)
			, transferSyntax_(TransferSyntax::ExplicitVRLittleEndian)
		{
		}

		DicomWriter::~DicomWriter()
		{
			if (file_.is_open())
			{
				file_.close();
			}
		}

		bool DicomWriter::WriteFile(const std::string& filePath, const DicomDataSet& dataSet)
		{
			file_.open(filePath, std::ios::binary);
			if (!file_.is_open())
			{
				SetError("Cannot create file: " + filePath);
				return false;
			}

			if (!WritePreamble())
			{
				file_.close();
				return false;
			}

			if (!WriteMetaInformation(dataSet))
			{
				file_.close();
				return false;
			}

			if (!WriteDataSet(dataSet))
			{
				file_.close();
				return false;
			}

			file_.close();
			return true;
		}

		bool DicomWriter::WriteBuffer(std::vector<uint8_t>& buffer, const DicomDataSet& dataSet)
		{
			outputBuffer_ = &buffer;
			buffer.clear();

			if (!WritePreamble())
			{
				return false;
			}

			if (!WriteMetaInformation(dataSet))
			{
				return false;
			}

			if (!WriteDataSet(dataSet))
			{
				return false;
			}

			outputBuffer_ = nullptr;
			return true;
		}

		void DicomWriter::SetTransferSyntax(const std::string& transferSyntaxUID)
		{
			transferSyntax_ = transferSyntaxUID;
			isExplicitVR_ = TransferSyntax::IsExplicitVR(transferSyntaxUID);
			isBigEndian_ = TransferSyntax::IsBigEndian(transferSyntaxUID);
		}

		bool DicomWriter::WritePreamble()
		{
			// Write 128-byte preamble (all zeros)
			uint8_t preamble[128] = { 0 };
			if (!WriteBytes(preamble, 128))
			{
				return false;
			}

			// Write DICM prefix
			const char dicm[4] = { 'D', 'I', 'C', 'M' };
			if (!WriteBytes(reinterpret_cast<const uint8_t*>(dicm), 4))
			{
				return false;
			}

			return true;
		}

		bool DicomWriter::WriteMetaInformation(const DicomDataSet& dataSet)
		{
			// Meta information is always Explicit VR Little Endian
			bool savedExplicitVR = isExplicitVR_;
			bool savedBigEndian = isBigEndian_;

			isExplicitVR_ = true;
			isBigEndian_ = false;

			// Write meta information elements (group 0x0002)
			for (const auto& pair : dataSet)
			{
				const DicomElement& element = pair.second;
				if (element.GetTag().GetGroup() == 0x0002)
				{
					if (!WriteDataElement(element))
					{
						return false;
					}
				}
			}

			// Restore transfer syntax settings
			isExplicitVR_ = savedExplicitVR;
			isBigEndian_ = savedBigEndian;

			return true;
		}

		bool DicomWriter::WriteDataSet(const DicomDataSet& dataSet)
		{
			// Write all non-meta information elements
			for (const auto& pair : dataSet)
			{
				const DicomElement& element = pair.second;
				if (element.GetTag().GetGroup() != 0x0002)
				{
					if (!WriteDataElement(element))
					{
						return false;
					}
				}
			}

			return true;
		}

		bool DicomWriter::WriteDataElement(const DicomElement& element)
		{
			if (!WriteTag(element.GetTag()))
			{
				return false;
			}

			if (isExplicitVR_)
			{
				if (!WriteVR(element.GetVR()))
				{
					return false;
				}
			}

			if (!WriteLength(element.GetLength(), element.GetVR()))
			{
				return false;
			}

			if (!WriteData(element.GetData(), element.GetLength()))
			{
				return false;
			}

			return true;
		}

		bool DicomWriter::WriteTag(const DicomTag& tag)
		{
			WriteUInt16(tag.GetGroup());
			WriteUInt16(tag.GetElement());
			return true;
		}

		bool DicomWriter::WriteVR(VR vr)
		{
			std::string vrStr = VRUtils::ToString(vr);
			return WriteBytes(reinterpret_cast<const uint8_t*>(vrStr.c_str()), 2);
		}

		bool DicomWriter::WriteLength(uint32_t length, VR vr)
		{
			if (isExplicitVR_)
			{
				if (VRUtils::HasExplicitLength(vr))
				{
					// 2 bytes reserved, 4 bytes length
					WriteUInt16(0);
					WriteUInt32(length);
				}
				else
				{
					// 2 bytes length
					WriteUInt16(static_cast<uint16_t>(length));
				}
			}
			else
			{
				// Implicit VR always uses 4-byte length
				WriteUInt32(length);
			}
			return true;
		}

		bool DicomWriter::WriteData(const uint8_t* data, uint32_t length)
		{
			if (length == 0)
			{
				return true;
			}
			return WriteBytes(data, length);
		}

		void DicomWriter::WriteUInt16(uint16_t value)
		{
			uint8_t bytes[2];

			if (isBigEndian_)
			{
				bytes[0] = static_cast<uint8_t>(value >> 8);
				bytes[1] = static_cast<uint8_t>(value & 0xFF);
			}
			else
			{
				bytes[0] = static_cast<uint8_t>(value & 0xFF);
				bytes[1] = static_cast<uint8_t>(value >> 8);
			}

			WriteBytes(bytes, 2);
		}

		void DicomWriter::WriteUInt32(uint32_t value)
		{
			uint8_t bytes[4];

			if (isBigEndian_)
			{
				bytes[0] = static_cast<uint8_t>(value >> 24);
				bytes[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
				bytes[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
				bytes[3] = static_cast<uint8_t>(value & 0xFF);
			}
			else
			{
				bytes[0] = static_cast<uint8_t>(value & 0xFF);
				bytes[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
				bytes[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
				bytes[3] = static_cast<uint8_t>(value >> 24);
			}

			WriteBytes(bytes, 4);
		}

		bool DicomWriter::WriteBytes(const uint8_t* buffer, size_t count)
		{
			if (file_.is_open())
			{
				file_.write(reinterpret_cast<const char*>(buffer), count);
				return file_.good();
			}
			else if (outputBuffer_ != nullptr)
			{
				outputBuffer_->insert(outputBuffer_->end(), buffer, buffer + count);
				return true;
			}
			return false;
		}

		void DicomWriter::SetError(const std::string& error)
		{
			lastError_ = error;
		}

	} // namespace dicom
} // namespace medvision
