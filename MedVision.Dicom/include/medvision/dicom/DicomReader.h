#pragma once

#include "DicomDataSet.h"
#include <string>
#include <memory>
#include <fstream>

namespace medvision
{
	namespace dicom
	{

		/// DICOM file reader
		class DicomReader
		{
		public:
			DicomReader();
			~DicomReader();

			/// Read DICOM file from path
			bool ReadFile(const std::string& filePath, DicomDataSet& dataSet);

			/// Read DICOM data from memory buffer
			bool ReadBuffer(const uint8_t* buffer, size_t length, DicomDataSet& dataSet);

			/// Get last error message
			const std::string& GetLastError() const { return lastError_; }

			/// Get detected transfer syntax
			const std::string& GetTransferSyntax() const { return transferSyntax_; }

			/// Check if file has DICOM preamble
			bool HasDicomPreamble() const { return hasPreamble_; }

		private:
			bool ReadPreamble();
			bool ReadMetaInformation(DicomDataSet& dataSet);
			bool ReadDataSet(DicomDataSet& dataSet);
			bool ReadDataElement(DicomDataSet& dataSet);

			bool ReadTag(DicomTag& tag);
			bool ReadVR(VR& vr);
			bool ReadLength(uint32_t& length, VR vr);
			bool ReadData(std::vector<uint8_t>& data, uint32_t length);

			uint16_t ReadUInt16();
			uint32_t ReadUInt32();
			bool ReadBytes(uint8_t* buffer, size_t count);

			void SetError(const std::string& error);
			VR DetermineImplicitVR(const DicomTag& tag) const;

		private:
			std::ifstream file_;
			const uint8_t* buffer_;
			size_t bufferLength_;
			size_t bufferPos_;

			bool isExplicitVR_;
			bool isBigEndian_;
			bool hasPreamble_;
			std::string transferSyntax_;
			std::string lastError_;
		};

	} // namespace dicom
} // namespace medvision
