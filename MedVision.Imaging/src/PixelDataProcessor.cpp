#include "medvision/imaging/PixelDataProcessor.h"
#include <cstring>

namespace medvision
{
	namespace imaging
	{
		bool PixelDataProcessor::ProcessPixelData(const DicomImage& image, std::vector<float>& outputBuffer)
		{
			if (!image.HasPixelData())
			{
				return false;
			}

			size_t numPixels = static_cast<size_t>(image.GetWidth()) * image.GetHeight();
			const uint8_t* data = image.GetRawPixelData();

			bool success = false;

			if (image.GetBitsAllocated() == 8)
			{
				success = Process8Bit(data, numPixels, outputBuffer);
			}
			else if (image.GetBitsAllocated() == 16)
			{
				if (image.IsSigned())
				{
					success = Process16BitSigned(data, numPixels, outputBuffer);
				}
				else
				{
					success = Process16BitUnsigned(data, numPixels, outputBuffer);
				}
			}

			if (success)
			{
				// Apply rescale slope/intercept if present
				double slope, intercept;
				if (image.GetRescaleSlope(slope) || image.GetRescaleIntercept(intercept))
				{
					if (!image.GetRescaleSlope(slope))
					{
						slope = 1.0;
					}
					if (!image.GetRescaleIntercept(intercept))
					{
						intercept = 0.0;
					}
					ApplyRescale(outputBuffer, slope, intercept);
				}
			}

			return success;
		}

		void PixelDataProcessor::ApplyRescale(std::vector<float>& buffer, double slope, double intercept)
		{
			for (size_t i = 0; i < buffer.size(); ++i)
			{
				buffer[i] = static_cast<float>(buffer[i] * slope + intercept);
			}
		}

		bool PixelDataProcessor::Process8Bit(const uint8_t* data, size_t pixels, std::vector<float>& output)
		{
			output.resize(pixels);
			for (size_t i = 0; i < pixels; ++i)
			{
				output[i] = static_cast<float>(data[i]);
			}
			return true;
		}

		bool PixelDataProcessor::Process16BitUnsigned(const uint8_t* data, size_t pixels, std::vector<float>& output)
		{
			output.resize(pixels);
			const uint16_t* data16 = reinterpret_cast<const uint16_t*>(data);

			for (size_t i = 0; i < pixels; ++i)
			{
				output[i] = static_cast<float>(data16[i]);
			}
			return true;
		}

		bool PixelDataProcessor::Process16BitSigned(const uint8_t* data, size_t pixels, std::vector<float>& output)
		{
			output.resize(pixels);
			const int16_t* data16 = reinterpret_cast<const int16_t*>(data);

			for (size_t i = 0; i < pixels; ++i)
			{
				output[i] = static_cast<float>(data16[i]);
			}
			return true;
		}

	} // namespace imaging
} // namespace medvision
