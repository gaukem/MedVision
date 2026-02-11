#pragma once

#include "DicomImage.h"
#include <vector>

namespace medvision
{
	namespace imaging
	{
		/// Process DICOM pixel data into usable format
		class PixelDataProcessor
		{
		public:
			// Process pixel data to float values (with rescale applied)
			static bool ProcessPixelData(const DicomImage& image, std::vector<float>& outputBuffer);

			// Apply rescale slope/intercept
			static void ApplyRescale(std::vector<float>& buffer, double slope, double intercept);

		private:
			static bool Process8Bit(const uint8_t* data, size_t pixels, std::vector<float>& output);
			static bool Process16BitUnsigned(const uint8_t* data, size_t pixels, std::vector<float>& output);
			static bool Process16BitSigned(const uint8_t* data, size_t pixels, std::vector<float>& output);
		};

	} // namespace imaging
} // namespace medvision
