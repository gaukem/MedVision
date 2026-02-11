#include "medvision/dicom/DicomTag.h"
#include <sstream>
#include <iomanip>

namespace medvision
{
	namespace dicom
	{

		// Common DICOM tag definitions
		const DicomTag DicomTag::FileMetaInformationGroupLength(0x0002, 0x0000);
		const DicomTag DicomTag::FileMetaInformationVersion(0x0002, 0x0001);
		const DicomTag DicomTag::MediaStorageSOPClassUID(0x0002, 0x0002);
		const DicomTag DicomTag::MediaStorageSOPInstanceUID(0x0002, 0x0003);
		const DicomTag DicomTag::TransferSyntaxUID(0x0002, 0x0010);
		const DicomTag DicomTag::ImplementationClassUID(0x0002, 0x0012);
		const DicomTag DicomTag::ImplementationVersionName(0x0002, 0x0013);

		const DicomTag DicomTag::PatientName(0x0010, 0x0010);
		const DicomTag DicomTag::PatientID(0x0010, 0x0020);
		const DicomTag DicomTag::PatientBirthDate(0x0010, 0x0030);
		const DicomTag DicomTag::PatientSex(0x0010, 0x0040);
		const DicomTag DicomTag::PatientAge(0x0010, 0x1010);

		const DicomTag DicomTag::StudyInstanceUID(0x0020, 0x000D);
		const DicomTag DicomTag::SeriesInstanceUID(0x0020, 0x000E);
		const DicomTag DicomTag::StudyDate(0x0008, 0x0020);
		const DicomTag DicomTag::StudyTime(0x0008, 0x0030);
		const DicomTag DicomTag::StudyDescription(0x0008, 0x1030);
		const DicomTag DicomTag::Modality(0x0008, 0x0060);

		const DicomTag DicomTag::Rows(0x0028, 0x0010);
		const DicomTag DicomTag::Columns(0x0028, 0x0011);
		const DicomTag DicomTag::BitsAllocated(0x0028, 0x0100);
		const DicomTag DicomTag::BitsStored(0x0028, 0x0101);
		const DicomTag DicomTag::HighBit(0x0028, 0x0102);
		const DicomTag DicomTag::PixelRepresentation(0x0028, 0x0103);
		const DicomTag DicomTag::SamplesPerPixel(0x0028, 0x0002);
		const DicomTag DicomTag::PhotometricInterpretation(0x0028, 0x0004);
		const DicomTag DicomTag::WindowCenter(0x0028, 0x1050);
		const DicomTag DicomTag::WindowWidth(0x0028, 0x1051);
		const DicomTag DicomTag::RescaleIntercept(0x0028, 0x1052);
		const DicomTag DicomTag::RescaleSlope(0x0028, 0x1053);
		const DicomTag DicomTag::PixelData(0x7FE0, 0x0010);

		DicomTag::DicomTag() : group_(0), element_(0)
		{
		}

		DicomTag::DicomTag(uint16_t group, uint16_t element)
			: group_(group), element_(element)
		{
		}

		DicomTag::DicomTag(uint32_t tag)
			: group_(static_cast<uint16_t>(tag >> 16))
			, element_(static_cast<uint16_t>(tag & 0xFFFF))
		{
		}

		std::string DicomTag::ToString() const
		{
			std::ostringstream oss;
			oss << "("
				<< std::hex << std::uppercase << std::setfill('0')
				<< std::setw(4) << group_ << ","
				<< std::setw(4) << element_ << ")";
			return oss.str();
		}

		bool DicomTag::operator==(const DicomTag& other) const
		{
			return group_ == other.group_ && element_ == other.element_;
		}

		bool DicomTag::operator!=(const DicomTag& other) const
		{
			return !(*this == other);
		}

		bool DicomTag::operator<(const DicomTag& other) const
		{
			if (group_ != other.group_)
			{
				return group_ < other.group_;
			}
			return element_ < other.element_;
		}

	} // namespace dicom
} // namespace medvision
