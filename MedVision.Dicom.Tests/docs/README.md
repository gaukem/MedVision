# MedVision.Dicom Unit Tests

This directory contains comprehensive unit tests for the MedVision.Dicom library using the Microsoft Visual Studio C++ Unit Test Framework.

## Test Files

### Unit Tests

1. **DicomTagTests.cpp**
   - Tests DicomTag construction, comparison, and formatting
   - Tests standard tag definitions
   - Tests tag operations (equality, less-than comparison)

2. **DicomElementTests.cpp**
   - Tests DicomElement data storage and retrieval
   - Tests string, integer, and binary data handling
   - Tests various Value Representations (VR)

3. **DicomDataSetTests.cpp**
   - Tests DicomDataSet element management
   - Tests data retrieval and storage operations
   - Tests dataset iteration and clearing

4. **DicomReaderTests.cpp**
   - Tests reading DICOM files from disk
   - Tests reading DICOM data from memory buffers
   - Tests error handling and validation

5. **DicomWriterTests.cpp**
   - Tests writing DICOM files to disk
   - Tests writing DICOM data to memory buffers
   - Tests data persistence through write/read cycles

6. **VRTests.cpp**
   - Tests Value Representation utilities
   - Tests VR string conversion
   - Tests VR type identification

### Integration Tests

7. **IntegrationTests.cpp**
   - Tests complete workflows (write then read)
   - Tests buffer round-trips
   - Tests data preservation across multiple operations
   - Tests complex patient and image data

## Running the Tests

### In Visual Studio 2022

1. Build the test project
2. Open **Test Explorer** (Test ¡æ Test Explorer)
3. Click **Run All** to execute all tests
4. View results in the Test Explorer window

### From Command Line

```bash
vstest.console.exe MedVision.Dicom.Tests.dll
```

## Test Coverage

The test suite covers:

- ? Tag creation and manipulation
- ? Element data storage (strings, integers, floats, binary)
- ? Dataset management and iteration
- ? File I/O operations
- ? Buffer I/O operations
- ? Value Representation utilities
- ? Error handling
- ? Data preservation and integrity
- ? Edge cases (empty strings, zero values, etc.)

## Test Framework

These tests use the **Microsoft Visual Studio C++ Unit Test Framework**, which provides:

- `TEST_CLASS` - Defines a test class
- `TEST_METHOD` - Defines a test method
- `TEST_METHOD_INITIALIZE` - Setup before each test
- `TEST_METHOD_CLEANUP` - Cleanup after each test
- `Assert` methods for validation

## Example Test

```cpp
TEST_METHOD(DicomTag_Constructor_CreatesValidTag)
{
    DicomTag tag(0x0010, 0x0010);
    
    Assert::AreEqual(static_cast<uint16_t>(0x0010), tag.GetGroup());
    Assert::AreEqual(static_cast<uint16_t>(0x0010), tag.GetElement());
}
```

## Notes

- Tests create temporary DICOM files for I/O testing
- All temporary files are cleaned up in `TEST_METHOD_CLEANUP`
- Tests are designed to be independent and can run in any order
- Compatible with C++14 standard

## Adding New Tests

To add new tests:

1. Add a new `TEST_METHOD` to an existing test class, or
2. Create a new test file with a new `TEST_CLASS`
3. Include necessary headers from `medvision/dicom/`
4. Build and run tests to verify

## Contributing

When adding new functionality to MedVision.Dicom:

1. Write tests first (TDD approach recommended)
2. Ensure all existing tests still pass
3. Add new tests for new features
4. Maintain test coverage above 80%
