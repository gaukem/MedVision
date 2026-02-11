#pragma once

#include <vector>
#include <cstdint>

namespace medvision
{
	namespace imaging
	{
		/// Window/Level transformation for DICOM images
		class WindowLevel
		{
		public:
			WindowLevel();
			WindowLevel(double center, double width);

			// Setters
			void SetCenter(double center) { center_ = center; }
			void SetWidth(double width);

			// Getters
			double GetCenter() const { return center_; }
			double GetWidth() const { return width_; }

			// Apply window/level transformation
			// Converts float pixel values to 8-bit display values
			void Apply(const std::vector<float>& input, std::vector<uint8_t>& output) const;

			// Apply in-place (float to float, normalized 0-1)
			void ApplyNormalized(std::vector<float>& pixels) const;

			// Calculate auto W/L from percentiles
			static WindowLevel FromPercentiles(const std::vector<float>& pixels, double lowPct = 0.02, double highPct = 0.98);

			// Common CT presets
			static WindowLevel Lung() { return WindowLevel(-600, 1500); }
			static WindowLevel Abdomen() { return WindowLevel(40, 400); }
			static WindowLevel Bone() { return WindowLevel(300, 1500); }
			static WindowLevel Brain() { return WindowLevel(40, 80); }
			static WindowLevel Liver() { return WindowLevel(60, 150); }
			static WindowLevel Mediastinum() { return WindowLevel(50, 350); }

		private:
			double center_;
			double width_;
		};

	} // namespace imaging
} // namespace medvision
