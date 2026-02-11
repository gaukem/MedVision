# MedVision.Dicom

**Self-contained DICOM parsing library for medical imaging**

## Overview

MedVision.Dicom is a lightweight, dependency-free C++ library for reading and writing DICOM (Digital Imaging and Communications in Medicine) files. Built with C++14 standard library only.

## Features

? **Zero External Dependencies** - Uses only C++ standard library  
? **Static Library** - Easy integration into your project  
? **Explicit & Implicit VR Support** - Handles both VR encodings  
? **Little & Big Endian** - Cross-platform byte order support  
? **Clean API** - Simple, intuitive interface  
? **Namespace Isolation** - `medvision::dicom`  

## Supported Features

### ? Currently Implemented
- DICOM file reading (with DICM preamble)
- DICOM file writing
- Meta information parsing (Group 0x0002)
- Explicit VR Little Endian (default)
- Implicit VR Little Endian
- Data element parsing (strings, integers, floats)
- Standard DICOM tags (Patient, Study, Series, Image modules)
- Transfer syntax detection
- DICOM dictionary (50+ common tags)

### ?? Not Yet Implemented
- Sequence (SQ) parsing
- Pixel data decompression (JPEG, JPEG2000, RLE)
- Undefined length elements
- Big Endian support (rare)
- Network DICOM (DIMSE)

## Project Structure

```
MedVision.Dicom/
戍式式 include/medvision/dicom/   # Public headers
弛   戍式式 DicomTag.h              # Tag representation
弛   戍式式 VR.h                    # Value Representations
弛   戍式式 DicomElement.h          # Single data element
弛   戍式式 DicomDataSet.h          # Element container
弛   戍式式 DicomReader.h           # File reader
弛   戍式式 DicomWriter.h           # File writer
弛   戍式式 DicomDictionary.h       # Tag definitions
弛   戌式式 TransferSyntax.h        # Transfer syntax utilities
戍式式 src/                        # Implementation files
戌式式 tests/                      # Unit tests (future)
```

## Usage Example

### Reading a DICOM File

```cpp
#include "medvision/dicom/DicomReader.h"
#include "medvision/dicom/DicomDataSet.h"
#include "medvision/dicom/DicomTag.h"
#include <iostream>

using namespace medvision::dicom;

int main() {
    DicomReader reader;
    DicomDataSet dataSet;
    
    if (!reader.ReadFile("CT_Image.dcm", dataSet)) {
        std::cerr << "Error: " << reader.GetLastError() << std::endl;
        return 1;
    }
    
    // Read patient information
    std::string patientName;
    if (dataSet.GetString(DicomTag::PatientName, patientName)) {
        std::cout << "Patient Name: " << patientName << std::endl;
    }
    
    std::string patientID;
    if (dataSet.GetString(DicomTag::PatientID, patientID)) {
        std::cout << "Patient ID: " << patientID << std::endl;
    }
    
    // Read image dimensions
    uint16_t rows, cols;
    if (dataSet.GetUInt16(DicomTag::Rows, rows) &&
        dataSet.GetUInt16(DicomTag::Columns, cols)) {
        std::cout << "Image Size: " << cols << "x" << rows << std::endl;
    }
    
    std::cout << "Transfer Syntax: " << reader.GetTransferSyntax() << std::endl;
    std::cout << "Total Elements: " << dataSet.GetElementCount() << std::endl;
    
    return 0;
}
```

### Writing a DICOM File

```cpp
#include "medvision/dicom/DicomWriter.h"
#include "medvision/dicom/DicomDataSet.h"
#include "medvision/dicom/DicomTag.h"
#include "medvision/dicom/VR.h"

using namespace medvision::dicom;

int main() {
    DicomDataSet dataSet;
    
    // Add meta information (required)
    dataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
    dataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
    
    // Add patient information
    dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
    dataSet.SetString(DicomTag::PatientID, VR::LO, "12345");
    dataSet.SetString(DicomTag::PatientSex, VR::CS, "M");
    
    // Add study information
    dataSet.SetString(DicomTag::StudyDate, VR::DA, "20240101");
    dataSet.SetString(DicomTag::Modality, VR::CS, "CT");
    
    // Write to file
    DicomWriter writer;
    if (!writer.WriteFile("output.dcm", dataSet)) {
        std::cerr << "Error: " << writer.GetLastError() << std::endl;
        return 1;
    }
    
    std::cout << "DICOM file created successfully!" << std::endl;
    return 0;
}
```

### Iterating Over Elements

```cpp
DicomDataSet dataSet;
// ... read file ...

for (const auto& pair : dataSet) {
    const DicomElement& element = pair.second;
    std::cout << element.GetTag().ToString() 
              << " = " << element.GetStringValue() 
              << std::endl;
}
```

## Building with Visual Studio

1. Open `MedVision.sln` (or create new solution)
2. Add `MedVision.Dicom.vcxproj` to solution
3. Build as static library (.lib)
4. Link against your application

### Include Paths
Add to your project:
```
MedVision.Dicom/include
```

### Linker Input
```
MedVision.Dicom.lib
```

## Compiler Requirements

- **C++14** or later
- **Visual Studio 2017+** (or any C++14 compliant compiler)
- **Windows 10+** (primary target)
- **x64 Platform** (recommended)

## API Reference

### Core Classes

| Class | Description |
|-------|-------------|
| `DicomTag` | Represents a DICOM tag (group, element) |
| `DicomElement` | Single data element with tag, VR, and value |
| `DicomDataSet` | Container for DICOM elements |
| `DicomReader` | Reads DICOM files |
| `DicomWriter` | Writes DICOM files |
| `VR` | Value Representation enum |
| `TransferSyntax` | Transfer syntax utilities |
| `DicomDictionary` | Tag name/VR lookup |

### Common DICOM Tags

Available as static constants in `DicomTag` class:

- `DicomTag::PatientName` - (0010,0010)
- `DicomTag::PatientID` - (0010,0020)
- `DicomTag::StudyDate` - (0008,0020)
- `DicomTag::Modality` - (0008,0060)
- `DicomTag::Rows` - (0028,0010)
- `DicomTag::Columns` - (0028,0011)
- `DicomTag::PixelData` - (7FE0,0010)

See `DicomTag.h` for complete list.

## Performance Notes

- File reading is sequential (no random access)
- Memory usage proportional to DICOM file size
- Pixel data is skipped by default (not parsed)
- Dictionary lookup is O(log n) using std::map

## Limitations

- Does not validate DICOM conformance
- No pixel data decompression
- No sequence element full support yet
- File-based only (no network DIMSE protocol)

## Testing

Sample DICOM files for testing can be obtained from:
- [DICOM Library](https://www.dicomlibrary.com/)
- [OsiriX Sample Data](https://www.osirix-viewer.com/resources/dicom-image-library/)

## Future Roadmap

1. ? Phase 1: Basic reading/writing (DONE)
2. ?? Phase 2: Sequence support
3. ?? Phase 3: Pixel data handling
4. ?? Phase 4: Compression support
5. ?? Phase 5: Network DICOM (separate module)

## License

Part of MedVision medical imaging platform.  
For educational and research purposes.

## Contributing

This is a learning project. Focus areas:
- Bug fixes
- Performance improvements
- Additional DICOM tags
- Better error handling
- Unit tests

---

**MedVision.Dicom** - Clean, simple, self-contained DICOM parsing for C++
