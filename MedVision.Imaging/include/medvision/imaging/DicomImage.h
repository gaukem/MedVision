#pragma once

#include "medvision/dicom/DicomDataSet.h"
#include <vector>
#include <string>
#include <cstdint>

namespace medvision
{
	namespace imaging
	{
		/// Wrapper around DicomDataSet with image-specific operations
		class DicomImage
		{
		public:
			DicomImage();
			explicit DicomImage(const medvision::dicom::DicomDataSet& dataset);
			~DicomImage();

			// Load from dataset
			bool LoadFromDataSet(const medvision::dicom::DicomDataSet& dataset);

			// Image dimensions
			uint16_t GetWidth() const { return width_; }
			uint16_t GetHeight() const { return height_; }
			uint16_t GetBitsAllocated() const { return bitsAllocated_; }
			uint16_t GetBitsStored() const { return bitsStored_; }
			uint16_t GetHighBit() const { return highBit_; }

			// Pixel data access
			bool HasPixelData() const { return !rawPixelData_.empty(); }
			const uint8_t* GetRawPixelData() const { return rawPixelData_.data(); }
			size_t GetPixelDataSize() const { return rawPixelData_.size(); }

			// Image attributes
			std::string GetPhotometricInterpretation() const { return photometricInterpretation_; }
			uint16_t GetSamplesPerPixel() const { return samplesPerPixel_; }
			uint16_t GetPixelRepresentation() const { return pixelRepresentation_; }
			bool IsSigned() const { return pixelRepresentation_ == 1; }
			bool IsColor() const { return samplesPerPixel_ > 1; }

			// Window/Level default values from DICOM
			bool GetWindowCenter(double& center) const;
			bool GetWindowWidth(double& width) const;

			// Rescale parameters
			bool GetRescaleSlope(double& slope) const;
			bool GetRescaleIntercept(double& intercept) const;

			// Patient/Study info (convenience methods)
			std::string GetPatientName() const;
			std::string GetPatientID() const;
			std::string GetStudyDescription() const;
			std::string GetModality() const;

			// Validation
			bool IsValid() const { return width_ > 0 && height_ > 0 && HasPixelData(); }

		private:
			void ExtractImageAttributes();
			void ExtractPixelData();

		private:
			const medvision::dicom::DicomDataSet* dataset_;

			// Image dimensions
			uint16_t width_;
			uint16_t height_;
			uint16_t bitsAllocated_;
			uint16_t bitsStored_;
			uint16_t highBit_;
			uint16_t samplesPerPixel_;
			uint16_t pixelRepresentation_;

			// Image attributes
			std::string photometricInterpretation_;

			// Pixel data
			std::vector<uint8_t> rawPixelData_;

			// Window/Level defaults
			bool hasWindowCenter_;
			double windowCenter_;
			bool hasWindowWidth_;
			double windowWidth_;

			// Rescale parameters
			bool hasRescaleSlope_;
			double rescaleSlope_;
			bool hasRescaleIntercept_;
			double rescaleIntercept_;
		};

	} // namespace imaging
} // namespace medvision
