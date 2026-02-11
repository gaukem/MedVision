// Example: Simple DICOM file reader
// This example demonstrates basic usage of MedVision.Dicom library

#include "medvision/dicom/DicomReader.h"
#include "medvision/dicom/DicomWriter.h"
#include "medvision/dicom/DicomDataSet.h"
#include "medvision/dicom/DicomTag.h"
#include "medvision/dicom/VR.h"
#include <iostream>
#include <iomanip>

using namespace medvision::dicom;

void PrintDicomInfo(const DicomDataSet& dataSet)
{
	std::cout << "\n=== DICOM File Information ===" << std::endl;
	std::cout << "Total Elements: " << dataSet.GetElementCount() << std::endl;

	// Patient Information
	std::cout << "\n--- Patient Information ---" << std::endl;
	std::string value;
	if (dataSet.GetString(DicomTag::PatientName, value))
	{
		std::cout << "Patient Name: " << value << std::endl;
	}
	if (dataSet.GetString(DicomTag::PatientID, value))
	{
		std::cout << "Patient ID: " << value << std::endl;
	}
	if (dataSet.GetString(DicomTag::PatientBirthDate, value))
	{
		std::cout << "Birth Date: " << value << std::endl;
	}
	if (dataSet.GetString(DicomTag::PatientSex, value))
	{
		std::cout << "Sex: " << value << std::endl;
	}

	// Study Information
	std::cout << "\n--- Study Information ---" << std::endl;
	if (dataSet.GetString(DicomTag::StudyDate, value))
	{
		std::cout << "Study Date: " << value << std::endl;
	}
	if (dataSet.GetString(DicomTag::StudyTime, value))
	{
		std::cout << "Study Time: " << value << std::endl;
	}
	if (dataSet.GetString(DicomTag::Modality, value))
	{
		std::cout << "Modality: " << value << std::endl;
	}
	if (dataSet.GetString(DicomTag::StudyInstanceUID, value))
	{
		std::cout << "Study UID: " << value << std::endl;
	}

	// Image Information
	std::cout << "\n--- Image Information ---" << std::endl;
	uint16_t rows, cols;
	if (dataSet.GetUInt16(DicomTag::Rows, rows))
	{
		std::cout << "Rows: " << rows << std::endl;
	}
	if (dataSet.GetUInt16(DicomTag::Columns, cols))
	{
		std::cout << "Columns: " << cols << std::endl;
	}
	uint16_t bitsAllocated, bitsStored;
	if (dataSet.GetUInt16(DicomTag::BitsAllocated, bitsAllocated))
	{
		std::cout << "Bits Allocated: " << bitsAllocated << std::endl;
	}
	if (dataSet.GetUInt16(DicomTag::BitsStored, bitsStored))
	{
		std::cout << "Bits Stored: " << bitsStored << std::endl;
	}
	if (dataSet.GetString(DicomTag::PhotometricInterpretation, value))
	{
		std::cout << "Photometric: " << value << std::endl;
	}
}

int ExampleReadDicom(const char* filename)
{
	std::cout << "\n=== Reading DICOM File ===" << std::endl;
	std::cout << "File: " << filename << std::endl;

	DicomReader reader;
	DicomDataSet dataSet;

	if (!reader.ReadFile(filename, dataSet))
	{
		std::cerr << "Error reading file: " << reader.GetLastError() << std::endl;
		return 1;
	}

	std::cout << "Transfer Syntax: " << reader.GetTransferSyntax() << std::endl;
	std::cout << "Has Preamble: " << (reader.HasDicomPreamble() ? "Yes" : "No") << std::endl;

	PrintDicomInfo(dataSet);

	return 0;
}

int ExampleWriteDicom(const char* filename)
{
	std::cout << "\n=== Creating DICOM File ===" << std::endl;
	std::cout << "Output: " << filename << std::endl;

	DicomDataSet dataSet;

	// Meta Information (Group 0x0002)
	dataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
	dataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
	dataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
	dataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
	dataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
	dataSet.SetString(DicomTag::ImplementationVersionName, VR::SH, "MEDVISION_1_0");

	// Patient Module
	dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
	dataSet.SetString(DicomTag::PatientID, VR::LO, "PATIENT001");
	dataSet.SetString(DicomTag::PatientBirthDate, VR::DA, "19800115");
	dataSet.SetString(DicomTag::PatientSex, VR::CS, "M");

	// Study Module
	dataSet.SetString(DicomTag::StudyDate, VR::DA, "20240101");
	dataSet.SetString(DicomTag::StudyTime, VR::TM, "120000");
	dataSet.SetString(DicomTag::Modality, VR::CS, "CT");
	dataSet.SetString(DicomTag::StudyInstanceUID, VR::UI, "1.2.3.4.5");
	dataSet.SetString(DicomTag::SeriesInstanceUID, VR::UI, "1.2.3.4.5.6");

	// Image Module
	dataSet.SetUInt16(DicomTag::Rows, 512);
	dataSet.SetUInt16(DicomTag::Columns, 512);
	dataSet.SetUInt16(DicomTag::BitsAllocated, 16);
	dataSet.SetUInt16(DicomTag::BitsStored, 12);
	dataSet.SetUInt16(DicomTag::HighBit, 11);
	dataSet.SetUInt16(DicomTag::PixelRepresentation, 0);
	dataSet.SetUInt16(DicomTag::SamplesPerPixel, 1);
	dataSet.SetString(DicomTag::PhotometricInterpretation, VR::CS, "MONOCHROME2");

	// Write file
	DicomWriter writer;
	if (!writer.WriteFile(filename, dataSet))
	{
		std::cerr << "Error writing file: " << writer.GetLastError() << std::endl;
		return 1;
	}

	std::cout << "DICOM file created successfully!" << std::endl;

	// Verify by reading back
	std::cout << "\n--- Verifying written file ---" << std::endl;
	DicomReader reader;
	DicomDataSet readBack;
	if (reader.ReadFile(filename, readBack))
	{
		PrintDicomInfo(readBack);
	}

	return 0;
}

int ExampleIterateElements(const char* filename)
{
	std::cout << "\n=== Iterating DICOM Elements ===" << std::endl;

	DicomReader reader;
	DicomDataSet dataSet;

	if (!reader.ReadFile(filename, dataSet))
	{
		std::cerr << "Error: " << reader.GetLastError() << std::endl;
		return 1;
	}

	std::cout << "\nAll DICOM Elements:" << std::endl;
	std::cout << std::string(80, '-') << std::endl;
	std::cout << std::left << std::setw(15) << "Tag"
		<< std::setw(10) << "VR"
		<< std::setw(10) << "Length"
		<< "Value (first 50 chars)" << std::endl;
	std::cout << std::string(80, '-') << std::endl;

	for (const auto& pair : dataSet)
	{
		const DicomElement& element = pair.second;

		std::string value = element.GetStringValue();
		if (value.length() > 50)
		{
			value = value.substr(0, 47) + "...";
		}

		std::cout << std::left
			<< std::setw(15) << element.GetTag().ToString()
			<< std::setw(10) << VRUtils::ToString(element.GetVR())
			<< std::setw(10) << element.GetLength()
			<< value << std::endl;
	}

	return 0;
}

// Main entry point with example usage
int main(int argc, char* argv[])
{
	std::cout << "MedVision.Dicom - Example Usage" << std::endl;
	std::cout << "================================" << std::endl;

	if (argc < 2)
	{
		std::cout << "\nUsage Examples:" << std::endl;
		std::cout << "  " << argv[0] << " read <filename.dcm>     - Read and display DICOM info" << std::endl;
		std::cout << "  " << argv[0] << " write <filename.dcm>    - Create a sample DICOM file" << std::endl;
		std::cout << "  " << argv[0] << " iterate <filename.dcm>  - Show all elements" << std::endl;
		return 0;
	}

	std::string command = argv[1];

	if (command == "read" && argc >= 3)
	{
		return ExampleReadDicom(argv[2]);
	}
	else if (command == "write" && argc >= 3)
	{
		return ExampleWriteDicom(argv[2]);
	}
	else if (command == "iterate" && argc >= 3)
	{
		return ExampleIterateElements(argv[2]);
	}
	else
	{
		std::cerr << "Invalid command or missing arguments" << std::endl;
		return 1;
	}

	return 0;
}
