# MedVision.Imaging

Image processing library for DICOM medical images.

## Features

- **DicomImage** - High-level wrapper for DICOM images
- **PixelDataProcessor** - Extract and process pixel data (8-bit, 16-bit signed/unsigned)
- **WindowLevel** - Window/Level transformations with CT presets

## Usage

```cpp
#include "medvision/dicom/DicomReader.h"
#include "medvision/imaging/DicomImage.h"
#include "medvision/imaging/PixelDataProcessor.h"
#include "medvision/imaging/WindowLevel.h"

// Read DICOM file
medvision::dicom::DicomReader reader;
medvision::dicom::DicomDataSet dataset;
reader.ReadFile("image.dcm", dataset);

// Wrap in DicomImage
medvision::imaging::DicomImage image(dataset);

// Process pixel data
std::vector<float> pixelBuffer;
medvision::imaging::PixelDataProcessor::ProcessPixelData(image, pixelBuffer);

// Apply window/level
medvision::imaging::WindowLevel wl(40, 400); // Abdomen preset
std::vector<uint8_t> displayBuffer;
wl.Apply(pixelBuffer, displayBuffer);

// Now displayBuffer contains 8-bit values ready for display
```

## Requirements

- C++14
- MedVision.Dicom library

## Build

```
msbuild MedVision.Imaging.vcxproj /p:Configuration=Debug /p:Platform=x64
```

## Status

? Phase 1 Week 1 - Complete
- DicomImage class
- PixelDataProcessor (8-bit, 16-bit)
- WindowLevel with CT presets
