#include "medvision/imaging/WindowLevel.h"
#include <algorithm>
#include <cmath>

namespace medvision
{
	namespace imaging
	{
		WindowLevel::WindowLevel()
			: center_(0.0)
			, width_(1.0)
		{
		}

		WindowLevel::WindowLevel(double center, double width)
			: center_(center)
			, width_(width)
		{
			if (width_ < 1.0)
			{
				width_ = 1.0;
			}
		}

		void WindowLevel::SetWidth(double width)
		{
			width_ = width;
			if (width_ < 1.0)
			{
				width_ = 1.0;
			}
		}

		void WindowLevel::Apply(const std::vector<float>& input, std::vector<uint8_t>& output) const
		{
			output.resize(input.size());

			double minValue = center_ - width_ / 2.0;
			double maxValue = center_ + width_ / 2.0;

			for (size_t i = 0; i < input.size(); ++i)
			{
				double value = input[i];

				if (value <= minValue)
				{
					output[i] = 0;
				}
				else if (value >= maxValue)
				{
					output[i] = 255;
				}
				else
				{
					double normalized = (value - minValue) / width_;
					output[i] = static_cast<uint8_t>(normalized * 255.0);
				}
			}
		}

		void WindowLevel::ApplyNormalized(std::vector<float>& pixels) const
		{
			double minValue = center_ - width_ / 2.0;
			double maxValue = center_ + width_ / 2.0;

			for (size_t i = 0; i < pixels.size(); ++i)
			{
				double value = pixels[i];

				if (value <= minValue)
				{
					pixels[i] = 0.0f;
				}
				else if (value >= maxValue)
				{
					pixels[i] = 1.0f;
				}
				else
				{
					pixels[i] = static_cast<float>((value - minValue) / width_);
				}
			}
		}

		WindowLevel WindowLevel::FromPercentiles(const std::vector<float>& pixels, double lowPct, double highPct)
		{
			if (pixels.empty())
			{
				return WindowLevel(0, 1);
			}

			// Create sorted copy
			std::vector<float> sorted = pixels;
			std::sort(sorted.begin(), sorted.end());

			// Calculate percentile indices
			size_t lowIdx = static_cast<size_t>(sorted.size() * lowPct);
			size_t highIdx = static_cast<size_t>(sorted.size() * highPct);

			if (highIdx >= sorted.size())
			{
				highIdx = sorted.size() - 1;
			}

			double minVal = sorted[lowIdx];
			double maxVal = sorted[highIdx];

			double center = (minVal + maxVal) / 2.0;
			double width = maxVal - minVal;

			if (width < 1.0)
			{
				width = 1.0;
			}

			return WindowLevel(center, width);
		}

	} // namespace imaging
} // namespace medvision
