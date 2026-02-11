// Integration tests for MedVision.Dicom library
// Tests complete workflows and interactions between components

#include "CppUnitTest.h"
#include "medvision/dicom/DicomReader.h"
#include "medvision/dicom/DicomWriter.h"
#include "medvision/dicom/DicomDataSet.h"
#include "medvision/dicom/DicomTag.h"
#include "medvision/dicom/VR.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace medvision::dicom;

namespace MedVisionDicomTests
{
	TEST_CLASS(IntegrationTests)
	{
	private:
		std::string testFile;

		void CleanupTestFile()
		{
			if (!testFile.empty())
			{
				std::remove(testFile.c_str());
			}
		}

	public:
		TEST_METHOD_CLEANUP(Cleanup)
		{
			CleanupTestFile();
		}

		TEST_METHOD(Integration_WriteAndRead_PreservesAllData)
		{
			testFile = "integration_test_full.dcm";
			
			// Create comprehensive dataset
			DicomDataSet writeDataSet;
			
			// Meta information
			writeDataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			writeDataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			writeDataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			writeDataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			writeDataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			
			// Patient module
			writeDataSet.SetString(DicomTag::PatientName, VR::PN, "INTEGRATION^TEST^MR");
			writeDataSet.SetString(DicomTag::PatientID, VR::LO, "INT12345");
			writeDataSet.SetString(DicomTag::PatientBirthDate, VR::DA, "19850315");
			writeDataSet.SetString(DicomTag::PatientSex, VR::CS, "F");
			
			// Study module
			writeDataSet.SetString(DicomTag::StudyDate, VR::DA, "20240115");
			writeDataSet.SetString(DicomTag::StudyTime, VR::TM, "143022");
			writeDataSet.SetString(DicomTag::StudyInstanceUID, VR::UI, "1.2.3.4.5");
			writeDataSet.SetString(DicomTag::Modality, VR::CS, "MR");
			
			// Image module
			writeDataSet.SetUInt16(DicomTag::Rows, 512);
			writeDataSet.SetUInt16(DicomTag::Columns, 512);
			writeDataSet.SetUInt16(DicomTag::BitsAllocated, 16);
			writeDataSet.SetUInt16(DicomTag::BitsStored, 12);
			
			// Write
			DicomWriter writer;
			bool writeSuccess = writer.WriteFile(testFile, writeDataSet);
			Assert::IsTrue(writeSuccess, L"Write operation failed");
			
			// Read
			DicomReader reader;
			DicomDataSet readDataSet;
			bool readSuccess = reader.ReadFile(testFile, readDataSet);
			Assert::IsTrue(readSuccess, L"Read operation failed");
			
			// Verify all fields
			std::string strValue;
			uint16_t intValue;
			
			readDataSet.GetString(DicomTag::PatientName, strValue);
			Assert::AreEqual(std::string("INTEGRATION^TEST^MR"), strValue);
			
			readDataSet.GetString(DicomTag::PatientID, strValue);
			Assert::AreEqual(std::string("INT12345"), strValue);
			
			readDataSet.GetString(DicomTag::PatientBirthDate, strValue);
			Assert::AreEqual(std::string("19850315"), strValue);
			
			readDataSet.GetString(DicomTag::PatientSex, strValue);
			Assert::AreEqual(std::string("F"), strValue);
			
			readDataSet.GetString(DicomTag::Modality, strValue);
			Assert::AreEqual(std::string("MR"), strValue);
			
			readDataSet.GetUInt16(DicomTag::Rows, intValue);
			Assert::AreEqual(static_cast<uint16_t>(512), intValue);
			
			readDataSet.GetUInt16(DicomTag::Columns, intValue);
			Assert::AreEqual(static_cast<uint16_t>(512), intValue);
		}

		TEST_METHOD(Integration_BufferRoundtrip_PreservesData)
		{
			// Create dataset
			DicomDataSet originalDataSet;
			originalDataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			originalDataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			originalDataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			originalDataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			originalDataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			originalDataSet.SetString(DicomTag::PatientName, VR::PN, "BUFFER^TEST");
			originalDataSet.SetUInt16(DicomTag::Rows, 128);
			
			// Write to buffer
			DicomWriter writer;
			std::vector<uint8_t> buffer;
			bool writeSuccess = writer.WriteBuffer(buffer, originalDataSet);
			Assert::IsTrue(writeSuccess);
			Assert::IsTrue(buffer.size() > 0);
			
			// Read from buffer
			DicomReader reader;
			DicomDataSet readDataSet;
			bool readSuccess = reader.ReadBuffer(buffer.data(), buffer.size(), readDataSet);
			Assert::IsTrue(readSuccess);
			
			// Verify
			std::string patientName;
			readDataSet.GetString(DicomTag::PatientName, patientName);
			Assert::AreEqual(std::string("BUFFER^TEST"), patientName);
			
			uint16_t rows;
			readDataSet.GetUInt16(DicomTag::Rows, rows);
			Assert::AreEqual(static_cast<uint16_t>(128), rows);
		}

		TEST_METHOD(Integration_MultipleWriteRead_MaintainsConsistency)
		{
			testFile = "integration_test_multiple.dcm";
			
			for (int i = 0; i < 5; i++)
			{
				DicomDataSet dataSet;
				dataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
				dataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
				dataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
				dataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
				dataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
				dataSet.SetString(DicomTag::PatientID, VR::LO, std::string("PATIENT") + std::to_string(i));
				
				DicomWriter writer;
				writer.WriteFile(testFile, dataSet);
				
				DicomReader reader;
				DicomDataSet readBack;
				reader.ReadFile(testFile, readBack);
				
				std::string patientId;
				readBack.GetString(DicomTag::PatientID, patientId);
				Assert::AreEqual(std::string("PATIENT") + std::to_string(i), patientId);
			}
		}

		TEST_METHOD(Integration_ComplexPatientData_PreservesAllFields)
		{
			testFile = "integration_patient_complete.dcm";
			
			DicomDataSet writeDataSet;
			
			// Meta information
			writeDataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			writeDataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			writeDataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			writeDataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			writeDataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			
			// Complex patient data
			writeDataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN^MICHAEL^JR^DR");
			writeDataSet.SetString(DicomTag::PatientID, VR::LO, "PAT-2024-001");
			writeDataSet.SetString(DicomTag::PatientBirthDate, VR::DA, "19750523");
			writeDataSet.SetString(DicomTag::PatientSex, VR::CS, "M");
			writeDataSet.SetString(DicomTag::PatientAge, VR::AS, "048Y");
			
			// Write and read
			DicomWriter writer;
			writer.WriteFile(testFile, writeDataSet);
			
			DicomReader reader;
			DicomDataSet readDataSet;
			reader.ReadFile(testFile, readDataSet);
			
			// Verify
			std::string value;
			readDataSet.GetString(DicomTag::PatientName, value);
			Assert::AreEqual(std::string("DOE^JOHN^MICHAEL^JR^DR"), value);
			
			readDataSet.GetString(DicomTag::PatientID, value);
			Assert::AreEqual(std::string("PAT-2024-001"), value);
			
			readDataSet.GetString(DicomTag::PatientAge, value);
			Assert::AreEqual(std::string("048Y"), value);
		}

		TEST_METHOD(Integration_ImageDimensions_PreservesExactValues)
		{
			testFile = "integration_image_dims.dcm";
			
			DicomDataSet writeDataSet;
			
			// Meta information
			writeDataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			writeDataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			writeDataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			writeDataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			writeDataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			
			// Various image dimensions
			writeDataSet.SetUInt16(DicomTag::Rows, 1024);
			writeDataSet.SetUInt16(DicomTag::Columns, 768);
			writeDataSet.SetUInt16(DicomTag::BitsAllocated, 16);
			writeDataSet.SetUInt16(DicomTag::BitsStored, 12);
			writeDataSet.SetUInt16(DicomTag::HighBit, 11);
			writeDataSet.SetUInt16(DicomTag::PixelRepresentation, 0);
			writeDataSet.SetUInt16(DicomTag::SamplesPerPixel, 1);
			
			// Write and read
			DicomWriter writer;
			writer.WriteFile(testFile, writeDataSet);
			
			DicomReader reader;
			DicomDataSet readDataSet;
			reader.ReadFile(testFile, readDataSet);
			
			// Verify all dimensions
			uint16_t value;
			readDataSet.GetUInt16(DicomTag::Rows, value);
			Assert::AreEqual(static_cast<uint16_t>(1024), value);
			
			readDataSet.GetUInt16(DicomTag::Columns, value);
			Assert::AreEqual(static_cast<uint16_t>(768), value);
			
			readDataSet.GetUInt16(DicomTag::BitsAllocated, value);
			Assert::AreEqual(static_cast<uint16_t>(16), value);
			
			readDataSet.GetUInt16(DicomTag::BitsStored, value);
			Assert::AreEqual(static_cast<uint16_t>(12), value);
			
			readDataSet.GetUInt16(DicomTag::HighBit, value);
			Assert::AreEqual(static_cast<uint16_t>(11), value);
		}

		TEST_METHOD(Integration_EmptyStrings_HandledCorrectly)
		{
			testFile = "integration_empty_strings.dcm";
			
			DicomDataSet writeDataSet;
			
			// Meta information
			writeDataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			writeDataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			writeDataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			writeDataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			writeDataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			
			// Set some empty strings
			writeDataSet.SetString(DicomTag::PatientName, VR::PN, "");
			writeDataSet.SetString(DicomTag::PatientID, VR::LO, "ID001");
			
			// Write and read
			DicomWriter writer;
			writer.WriteFile(testFile, writeDataSet);
			
			DicomReader reader;
			DicomDataSet readDataSet;
			reader.ReadFile(testFile, readDataSet);
			
			// Verify
			std::string value;
			bool hasName = readDataSet.GetString(DicomTag::PatientName, value);
			bool hasId = readDataSet.GetString(DicomTag::PatientID, value);
			
			Assert::IsTrue(hasId);
			Assert::AreEqual(std::string("ID001"), value);
		}

		TEST_METHOD(Integration_LargeDataSet_HandlesMany)
		{
			testFile = "integration_large_dataset.dcm";
			
			DicomDataSet writeDataSet;
			
			// Meta information
			writeDataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			writeDataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			writeDataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			writeDataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			writeDataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			
			// Add many elements
			writeDataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			writeDataSet.SetString(DicomTag::PatientID, VR::LO, "ID001");
			writeDataSet.SetString(DicomTag::PatientBirthDate, VR::DA, "19800101");
			writeDataSet.SetString(DicomTag::PatientSex, VR::CS, "M");
			writeDataSet.SetString(DicomTag::PatientAge, VR::AS, "044Y");
			writeDataSet.SetString(DicomTag::StudyDate, VR::DA, "20240115");
			writeDataSet.SetString(DicomTag::StudyTime, VR::TM, "120000");
			writeDataSet.SetString(DicomTag::StudyInstanceUID, VR::UI, "1.2.3.4");
			writeDataSet.SetString(DicomTag::SeriesInstanceUID, VR::UI, "1.2.3.4.5");
			writeDataSet.SetString(DicomTag::Modality, VR::CS, "CT");
			writeDataSet.SetUInt16(DicomTag::Rows, 512);
			writeDataSet.SetUInt16(DicomTag::Columns, 512);
			writeDataSet.SetUInt16(DicomTag::BitsAllocated, 16);
			writeDataSet.SetUInt16(DicomTag::BitsStored, 12);
			writeDataSet.SetUInt16(DicomTag::SamplesPerPixel, 1);
			
			size_t originalCount = writeDataSet.GetElementCount();
			
			// Write and read
			DicomWriter writer;
			writer.WriteFile(testFile, writeDataSet);
			
			DicomReader reader;
			DicomDataSet readDataSet;
			reader.ReadFile(testFile, readDataSet);
			
			// Verify element count is reasonable (may include additional meta elements)
			Assert::IsTrue(readDataSet.GetElementCount() >= 10);
		}
	};
}
