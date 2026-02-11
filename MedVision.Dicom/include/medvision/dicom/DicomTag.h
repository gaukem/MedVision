#pragma once

#include <cstdint>
#include <string>

namespace medvision
{
	namespace dicom
	{

		/// Represents a DICOM tag (group, element pair)
		class DicomTag
		{
		public:
			DicomTag();
			DicomTag(uint16_t group, uint16_t element);
			explicit DicomTag(uint32_t tag);

			uint16_t GetGroup() const { return group_; }
			uint16_t GetElement() const { return element_; }
			uint32_t GetTag() const { return (static_cast<uint32_t>(group_) << 16) | element_; }

			std::string ToString() const;

			bool operator==(const DicomTag& other) const;
			bool operator!=(const DicomTag& other) const;
			bool operator<(const DicomTag& other) const;

			// Common DICOM tags
			static const DicomTag FileMetaInformationGroupLength;    // (0002,0000)
			static const DicomTag FileMetaInformationVersion;        // (0002,0001)
			static const DicomTag MediaStorageSOPClassUID;           // (0002,0002)
			static const DicomTag MediaStorageSOPInstanceUID;        // (0002,0003)
			static const DicomTag TransferSyntaxUID;                 // (0002,0010)
			static const DicomTag ImplementationClassUID;            // (0002,0012)
			static const DicomTag ImplementationVersionName;         // (0002,0013)

			static const DicomTag PatientName;                       // (0010,0010)
			static const DicomTag PatientID;                         // (0010,0020)
			static const DicomTag PatientBirthDate;                  // (0010,0030)
			static const DicomTag PatientSex;                        // (0010,0040)
			static const DicomTag PatientAge;                        // (0010,1010)

			static const DicomTag StudyInstanceUID;                  // (0020,000D)
			static const DicomTag SeriesInstanceUID;                 // (0020,000E)
			static const DicomTag StudyDate;                         // (0008,0020)
			static const DicomTag StudyTime;                         // (0008,0030)
			static const DicomTag StudyDescription;                  // (0008,1030)
			static const DicomTag Modality;                          // (0008,0060)

			static const DicomTag Rows;                              // (0028,0010)
			static const DicomTag Columns;                           // (0028,0011)
			static const DicomTag BitsAllocated;                     // (0028,0100)
			static const DicomTag BitsStored;                        // (0028,0101)
			static const DicomTag HighBit;                           // (0028,0102)
			static const DicomTag PixelRepresentation;               // (0028,0103)
			static const DicomTag SamplesPerPixel;                   // (0028,0002)
			static const DicomTag PhotometricInterpretation;         // (0028,0004)
			static const DicomTag WindowCenter;                      // (0028,1050)
			static const DicomTag WindowWidth;                       // (0028,1051)
			static const DicomTag RescaleIntercept;                  // (0028,1052)
			static const DicomTag RescaleSlope;                      // (0028,1053)
			static const DicomTag PixelData;                         // (7FE0,0010)

		private:
			uint16_t group_;
			uint16_t element_;
		};

	} // namespace dicom
} // namespace medvision
