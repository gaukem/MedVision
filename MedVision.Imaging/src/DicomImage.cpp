#include "medvision/imaging/DicomImage.h"
#include "medvision/dicom/DicomTag.h"

namespace medvision
{
	namespace imaging
	{
		DicomImage::DicomImage()
			: dataset_(nullptr)
			, width_(0)
			, height_(0)
			, bitsAllocated_(0)
			, bitsStored_(0)
			, highBit_(0)
			, samplesPerPixel_(1)
			, pixelRepresentation_(0)
			, hasWindowCenter_(false)
			, windowCenter_(0.0)
			, hasWindowWidth_(false)
			, windowWidth_(0.0)
			, hasRescaleSlope_(false)
			, rescaleSlope_(1.0)
			, hasRescaleIntercept_(false)
			, rescaleIntercept_(0.0)
		{
		}

		DicomImage::DicomImage(const medvision::dicom::DicomDataSet& dataset)
			: DicomImage()
		{
			LoadFromDataSet(dataset);
		}

		DicomImage::~DicomImage()
		{
		}

		bool DicomImage::LoadFromDataSet(const medvision::dicom::DicomDataSet& dataset)
		{
			dataset_ = &dataset;
			ExtractImageAttributes();
			ExtractPixelData();
			return IsValid();
		}

		void DicomImage::ExtractImageAttributes()
		{
			using namespace medvision::dicom;

			// Image dimensions
			dataset_->GetUInt16(DicomTag::Rows, height_);
			dataset_->GetUInt16(DicomTag::Columns, width_);
			dataset_->GetUInt16(DicomTag::BitsAllocated, bitsAllocated_);
			dataset_->GetUInt16(DicomTag::BitsStored, bitsStored_);
			dataset_->GetUInt16(DicomTag::HighBit, highBit_);
			dataset_->GetUInt16(DicomTag::SamplesPerPixel, samplesPerPixel_);
			dataset_->GetUInt16(DicomTag::PixelRepresentation, pixelRepresentation_);

			// Photometric interpretation
			dataset_->GetString(DicomTag::PhotometricInterpretation, photometricInterpretation_);

			// Window/Level defaults
			std::string wlStr;
			if (dataset_->GetString(DicomTag::WindowCenter, wlStr))
			{
				windowCenter_ = std::stod(wlStr);
				hasWindowCenter_ = true;
			}
			if (dataset_->GetString(DicomTag::WindowWidth, wlStr))
			{
				windowWidth_ = std::stod(wlStr);
				hasWindowWidth_ = true;
			}

			// Rescale parameters
			std::string rescaleStr;
			if (dataset_->GetString(DicomTag::RescaleSlope, rescaleStr))
			{
				rescaleSlope_ = std::stod(rescaleStr);
				hasRescaleSlope_ = true;
			}
			if (dataset_->GetString(DicomTag::RescaleIntercept, rescaleStr))
			{
				rescaleIntercept_ = std::stod(rescaleStr);
				hasRescaleIntercept_ = true;
			}
		}

		void DicomImage::ExtractPixelData()
		{
			using namespace medvision::dicom;

			const DicomElement* pixelDataElement = dataset_->GetElement(DicomTag::PixelData);
			if (pixelDataElement && !pixelDataElement->IsEmpty())
			{
				const uint8_t* data = pixelDataElement->GetData();
				uint32_t length = pixelDataElement->GetLength();

				rawPixelData_.assign(data, data + length);
			}
		}

		bool DicomImage::GetWindowCenter(double& center) const
		{
			if (hasWindowCenter_)
			{
				center = windowCenter_;
				return true;
			}
			return false;
		}

		bool DicomImage::GetWindowWidth(double& width) const
		{
			if (hasWindowWidth_)
			{
				width = windowWidth_;
				return true;
			}
			return false;
		}

		bool DicomImage::GetRescaleSlope(double& slope) const
		{
			if (hasRescaleSlope_)
			{
				slope = rescaleSlope_;
				return true;
			}
			slope = 1.0;
			return false;
		}

		bool DicomImage::GetRescaleIntercept(double& intercept) const
		{
			if (hasRescaleIntercept_)
			{
				intercept = rescaleIntercept_;
				return true;
			}
			intercept = 0.0;
			return false;
		}

		std::string DicomImage::GetPatientName() const
		{
			std::string value;
			dataset_->GetString(medvision::dicom::DicomTag::PatientName, value);
			return value;
		}

		std::string DicomImage::GetPatientID() const
		{
			std::string value;
			dataset_->GetString(medvision::dicom::DicomTag::PatientID, value);
			return value;
		}

		std::string DicomImage::GetStudyDescription() const
		{
			std::string value;
			dataset_->GetString(medvision::dicom::DicomTag::StudyDescription, value);
			return value;
		}

		std::string DicomImage::GetModality() const
		{
			std::string value;
			dataset_->GetString(medvision::dicom::DicomTag::Modality, value);
			return value;
		}

	} // namespace imaging
} // namespace medvision
