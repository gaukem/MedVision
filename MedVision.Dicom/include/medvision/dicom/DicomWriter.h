#pragma once

#include "DicomDataSet.h"
#include <string>
#include <fstream>

namespace medvision
{
	namespace dicom
	{

		/// DICOM file writer
		class DicomWriter
		{
		public:
			DicomWriter();
			~DicomWriter();

			/// Write DICOM dataset to file
			bool WriteFile(const std::string& filePath, const DicomDataSet& dataSet);

			/// Write DICOM dataset to memory buffer
			bool WriteBuffer(std::vector<uint8_t>& buffer, const DicomDataSet& dataSet);

			/// Set transfer syntax for writing (default: ExplicitVRLittleEndian)
			void SetTransferSyntax(const std::string& transferSyntaxUID);

			/// Get last error message
			const std::string& GetLastError() const { return lastError_; }

		private:
			bool WritePreamble();
			bool WriteMetaInformation(const DicomDataSet& dataSet);
			bool WriteDataSet(const DicomDataSet& dataSet);
			bool WriteDataElement(const DicomElement& element);

			bool WriteTag(const DicomTag& tag);
			bool WriteVR(VR vr);
			bool WriteLength(uint32_t length, VR vr);
			bool WriteData(const uint8_t* data, uint32_t length);

			void WriteUInt16(uint16_t value);
			void WriteUInt32(uint32_t value);
			bool WriteBytes(const uint8_t* buffer, size_t count);

			void SetError(const std::string& error);

		private:
			std::ofstream file_;
			std::vector<uint8_t>* outputBuffer_;

			bool isExplicitVR_;
			bool isBigEndian_;
			std::string transferSyntax_;
			std::string lastError_;
		};

	} // namespace dicom
} // namespace medvision
