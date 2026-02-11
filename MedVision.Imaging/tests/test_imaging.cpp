// Test application for MedVision.Imaging library
// Demonstrates DicomImage, PixelDataProcessor, and WindowLevel

#include "medvision/dicom/DicomReader.h"
#include "medvision/imaging/DicomImage.h"
#include "medvision/imaging/PixelDataProcessor.h"
#include "medvision/imaging/WindowLevel.h"
#include <iostream>
#include <iomanip>

using namespace medvision::dicom;
using namespace medvision::imaging;

void PrintImageInfo(const DicomImage& image)
{
	std::cout << "\n=== Image Information ===" << std::endl;
	std::cout << "Dimensions: " << image.GetWidth() << " x " << image.GetHeight() << std::endl;
	std::cout << "Bits Allocated: " << image.GetBitsAllocated() << std::endl;
	std::cout << "Bits Stored: " << image.GetBitsStored() << std::endl;
	std::cout << "High Bit: " << image.GetHighBit() << std::endl;
	std::cout << "Samples Per Pixel: " << image.GetSamplesPerPixel() << std::endl;
	std::cout << "Pixel Representation: " << image.GetPixelRepresentation() 
		<< (image.IsSigned() ? " (Signed)" : " (Unsigned)") << std::endl;
	std::cout << "Photometric: " << image.GetPhotometricInterpretation() << std::endl;
	std::cout << "Has Pixel Data: " << (image.HasPixelData() ? "Yes" : "No") << std::endl;

	if (image.HasPixelData())
	{
		std::cout << "Pixel Data Size: " << image.GetPixelDataSize() << " bytes" << std::endl;
	}

	// Window/Level defaults
	double center, width;
	if (image.GetWindowCenter(center) && image.GetWindowWidth(width))
	{
		std::cout << "\nWindow/Level (from DICOM):" << std::endl;
		std::cout << "  Center: " << center << std::endl;
		std::cout << "  Width: " << width << std::endl;
	}

	// Rescale parameters
	double slope, intercept;
	bool hasSlope = image.GetRescaleSlope(slope);
	bool hasIntercept = image.GetRescaleIntercept(intercept);
	if (hasSlope || hasIntercept)
	{
		std::cout << "\nRescale Parameters:" << std::endl;
		std::cout << "  Slope: " << slope << std::endl;
		std::cout << "  Intercept: " << intercept << std::endl;
	}

	// Patient info
	std::cout << "\n=== Patient Information ===" << std::endl;
	std::cout << "Patient Name: " << image.GetPatientName() << std::endl;
	std::cout << "Patient ID: " << image.GetPatientID() << std::endl;
	std::cout << "Modality: " << image.GetModality() << std::endl;
	std::cout << "Study Description: " << image.GetStudyDescription() << std::endl;
}

void PrintPixelStatistics(const std::vector<float>& pixels)
{
	if (pixels.empty())
	{
		return;
	}

	float minVal = pixels[0];
	float maxVal = pixels[0];
	double sum = 0.0;

	for (float val : pixels)
	{
		if (val < minVal) minVal = val;
		if (val > maxVal) maxVal = val;
		sum += val;
	}

	double mean = sum / pixels.size();

	std::cout << "\n=== Pixel Statistics ===" << std::endl;
	std::cout << "Min: " << minVal << std::endl;
	std::cout << "Max: " << maxVal << std::endl;
	std::cout << "Mean: " << mean << std::endl;
	std::cout << "Pixels: " << pixels.size() << std::endl;
}

void DemonstrateCTPresets(const std::vector<float>& pixels)
{
	std::cout << "\n=== CT Window/Level Presets ===" << std::endl;

	struct Preset
	{
		const char* name;
		WindowLevel wl;
	};

	Preset presets[] = {
		{ "Lung", WindowLevel::Lung() },
		{ "Abdomen", WindowLevel::Abdomen() },
		{ "Bone", WindowLevel::Bone() },
		{ "Brain", WindowLevel::Brain() },
		{ "Liver", WindowLevel::Liver() },
		{ "Mediastinum", WindowLevel::Mediastinum() }
	};

	for (const auto& preset : presets)
	{
		std::cout << std::left << std::setw(15) << preset.name
			<< " - W: " << std::setw(6) << preset.wl.GetWidth()
			<< " C: " << std::setw(6) << preset.wl.GetCenter() << std::endl;
	}

	// Auto W/L
	WindowLevel autoWL = WindowLevel::FromPercentiles(pixels, 0.02, 0.98);
	std::cout << std::left << std::setw(15) << "Auto W/L"
		<< " - W: " << std::setw(6) << static_cast<int>(autoWL.GetWidth())
		<< " C: " << std::setw(6) << static_cast<int>(autoWL.GetCenter()) << std::endl;
}

int main(int argc, char* argv[])
{
	std::cout << "MedVision.Imaging Test Application" << std::endl;
	std::cout << "===================================" << std::endl;

	if (argc < 2)
	{
		std::cout << "\nUsage: " << argv[0] << " <dicom_file.dcm>" << std::endl;
		std::cout << "\nThis application will:" << std::endl;
		std::cout << "  1. Read the DICOM file" << std::endl;
		std::cout << "  2. Extract image information" << std::endl;
		std::cout << "  3. Process pixel data" << std::endl;
		std::cout << "  4. Apply window/level transformations" << std::endl;
		std::cout << "  5. Show CT presets" << std::endl;
		return 0;
	}

	const char* filename = argv[1];
	std::cout << "\nReading file: " << filename << std::endl;

	// Step 1: Read DICOM file
	DicomReader reader;
	DicomDataSet dataset;

	if (!reader.ReadFile(filename, dataset))
	{
		std::cerr << "Error reading file: " << reader.GetLastError() << std::endl;
		return 1;
	}

	std::cout << "File read successfully!" << std::endl;
	std::cout << "Transfer Syntax: " << reader.GetTransferSyntax() << std::endl;

	// Step 2: Wrap in DicomImage
	DicomImage image(dataset);

	if (!image.IsValid())
	{
		std::cerr << "Error: Invalid DICOM image (missing dimensions or pixel data)" << std::endl;
		return 1;
	}

	PrintImageInfo(image);

	// Step 3: Process pixel data
	std::cout << "\n=== Processing Pixel Data ===" << std::endl;
	std::vector<float> pixelBuffer;

	if (!PixelDataProcessor::ProcessPixelData(image, pixelBuffer))
	{
		std::cerr << "Error processing pixel data" << std::endl;
		return 1;
	}

	std::cout << "Pixel data processed successfully!" << std::endl;
	std::cout << "Float buffer size: " << pixelBuffer.size() << " values" << std::endl;

	PrintPixelStatistics(pixelBuffer);

	// Step 4: Demonstrate CT presets
	DemonstrateCTPresets(pixelBuffer);

	// Step 5: Apply window/level
	std::cout << "\n=== Applying Window/Level ===" << std::endl;

	// Use DICOM default or auto W/L
	WindowLevel wl;
	double center, width;
	if (image.GetWindowCenter(center) && image.GetWindowWidth(width))
	{
		wl = WindowLevel(center, width);
		std::cout << "Using DICOM W/L: " << width << " / " << center << std::endl;
	}
	else
	{
		wl = WindowLevel::FromPercentiles(pixelBuffer, 0.02, 0.98);
		std::cout << "Using Auto W/L: " << wl.GetWidth() << " / " << wl.GetCenter() << std::endl;
	}

	std::vector<uint8_t> displayBuffer;
	wl.Apply(pixelBuffer, displayBuffer);

	std::cout << "Display buffer created: " << displayBuffer.size() << " bytes (8-bit)" << std::endl;

	// Show sample pixel values
	std::cout << "\n=== Sample Pixels (first 10) ===" << std::endl;
	std::cout << "Index | Float Value | Display Value (0-255)" << std::endl;
	std::cout << "------|-------------|---------------------" << std::endl;
	for (size_t i = 0; i < 10 && i < pixelBuffer.size(); ++i)
	{
		std::cout << std::setw(5) << i << " | "
			<< std::setw(11) << std::fixed << std::setprecision(2) << pixelBuffer[i] << " | "
			<< std::setw(3) << static_cast<int>(displayBuffer[i]) << std::endl;
	}

	std::cout << "\n=== Success! ===" << std::endl;
	std::cout << "The display buffer is ready for rendering to screen." << std::endl;
	std::cout << "Each pixel is now an 8-bit value (0-255) ready for display." << std::endl;

	return 0;
}
