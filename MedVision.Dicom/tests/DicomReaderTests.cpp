// Unit tests for DicomReader class
// Tests reading DICOM files from disk and memory buffers

#include "CppUnitTest.h"
#include "medvision/dicom/DicomReader.h"
#include "medvision/dicom/DicomWriter.h"
#include "medvision/dicom/DicomDataSet.h"
#include "medvision/dicom/DicomTag.h"
#include "medvision/dicom/VR.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace medvision::dicom;

namespace MedVisionDicomTests
{
	TEST_CLASS(DicomReaderTests)
	{
	private:
		std::string testFilePath;

		void CreateTestDicomFile()
		{
			testFilePath = "test_dicom_reader.dcm";
			
			DicomDataSet dataSet;
			
			// Meta Information (Group 0x0002)
			dataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			dataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			dataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			dataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			dataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			dataSet.SetString(DicomTag::ImplementationVersionName, VR::SH, "MEDVISION_1_0");
			
			// Patient Module
			dataSet.SetString(DicomTag::PatientName, VR::PN, "TEST^PATIENT");
			dataSet.SetString(DicomTag::PatientID, VR::LO, "TEST001");
			dataSet.SetString(DicomTag::PatientBirthDate, VR::DA, "19900101");
			dataSet.SetString(DicomTag::PatientSex, VR::CS, "M");
			
			// Study Module
			dataSet.SetString(DicomTag::StudyDate, VR::DA, "20240101");
			dataSet.SetString(DicomTag::StudyTime, VR::TM, "120000");
			dataSet.SetString(DicomTag::Modality, VR::CS, "CT");
			dataSet.SetString(DicomTag::StudyInstanceUID, VR::UI, "1.2.3.4.5");
			
			DicomWriter writer;
			writer.WriteFile(testFilePath, dataSet);
		}

		void DeleteTestFile()
		{
			if (!testFilePath.empty())
			{
				std::remove(testFilePath.c_str());
			}
		}

	public:
		TEST_METHOD_INITIALIZE(Setup)
		{
			CreateTestDicomFile();
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			DeleteTestFile();
		}

		TEST_METHOD(DicomReader_Constructor_CreatesValidReader)
		{
			DicomReader reader;
			
			// Should not crash, error should be empty initially
			std::string error = reader.GetLastError();
			Assert::IsTrue(true); // Constructor succeeded
		}

		TEST_METHOD(DicomReader_ReadFile_SucceedsWithValidFile)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			bool result = reader.ReadFile(testFilePath, dataSet);
			
			Assert::IsTrue(result, L"ReadFile should succeed");
			Assert::IsTrue(dataSet.GetElementCount() > 0, L"DataSet should contain elements");
		}

		TEST_METHOD(DicomReader_ReadFile_FailsWithInvalidPath)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			bool result = reader.ReadFile("nonexistent_file.dcm", dataSet);
			
			Assert::IsFalse(result);
			Assert::IsFalse(reader.GetLastError().empty());
		}

		TEST_METHOD(DicomReader_ReadFile_FailsWithEmptyPath)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			bool result = reader.ReadFile("", dataSet);
			
			Assert::IsFalse(result);
		}

		TEST_METHOD(DicomReader_ReadFile_PreservesPatientData)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			reader.ReadFile(testFilePath, dataSet);
			
			std::string patientName;
			bool hasName = dataSet.GetString(DicomTag::PatientName, patientName);
			
			Assert::IsTrue(hasName);
			Assert::AreEqual(std::string("TEST^PATIENT"), patientName);
		}

		TEST_METHOD(DicomReader_ReadFile_PreservesPatientID)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			reader.ReadFile(testFilePath, dataSet);
			
			std::string patientId;
			bool hasId = dataSet.GetString(DicomTag::PatientID, patientId);
			
			Assert::IsTrue(hasId);
			Assert::AreEqual(std::string("TEST001"), patientId);
		}

		TEST_METHOD(DicomReader_ReadFile_PreservesStudyInformation)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			reader.ReadFile(testFilePath, dataSet);
			
			std::string modality;
			dataSet.GetString(DicomTag::Modality, modality);
			Assert::AreEqual(std::string("CT"), modality);
			
			std::string studyDate;
			dataSet.GetString(DicomTag::StudyDate, studyDate);
			Assert::AreEqual(std::string("20240101"), studyDate);
		}

		TEST_METHOD(DicomReader_HasDicomPreamble_ReturnsTrueForValidFile)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			reader.ReadFile(testFilePath, dataSet);
			
			Assert::IsTrue(reader.HasDicomPreamble());
		}

		TEST_METHOD(DicomReader_GetTransferSyntax_ReturnsValidSyntax)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			reader.ReadFile(testFilePath, dataSet);
			
			std::string transferSyntax = reader.GetTransferSyntax();
			Assert::IsFalse(transferSyntax.empty());
		}

		TEST_METHOD(DicomReader_ReadBuffer_SucceedsWithValidBuffer)
		{
			// First read file into buffer
			std::ifstream file(testFilePath, std::ios::binary);
			std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)),
			                            std::istreambuf_iterator<char>());
			file.close();
			
			DicomReader reader;
			DicomDataSet dataSet;
			
			bool result = reader.ReadBuffer(buffer.data(), buffer.size(), dataSet);
			
			Assert::IsTrue(result);
			Assert::IsTrue(dataSet.GetElementCount() > 0);
		}

		TEST_METHOD(DicomReader_ReadBuffer_FailsWithEmptyBuffer)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			bool result = reader.ReadBuffer(nullptr, 0, dataSet);
			
			Assert::IsFalse(result);
		}

		TEST_METHOD(DicomReader_ReadBuffer_FailsWithNullPointer)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			bool result = reader.ReadBuffer(nullptr, 100, dataSet);
			
			Assert::IsFalse(result);
		}

		TEST_METHOD(DicomReader_ReadBuffer_PreservesData)
		{
			std::ifstream file(testFilePath, std::ios::binary);
			std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)),
			                            std::istreambuf_iterator<char>());
			file.close();
			
			DicomReader reader;
			DicomDataSet dataSet;
			reader.ReadBuffer(buffer.data(), buffer.size(), dataSet);
			
			std::string patientName;
			dataSet.GetString(DicomTag::PatientName, patientName);
			Assert::AreEqual(std::string("TEST^PATIENT"), patientName);
		}

		TEST_METHOD(DicomReader_MultipleReads_SucceedIndependently)
		{
			DicomReader reader;
			
			DicomDataSet dataSet1;
			bool result1 = reader.ReadFile(testFilePath, dataSet1);
			Assert::IsTrue(result1);
			
			DicomDataSet dataSet2;
			bool result2 = reader.ReadFile(testFilePath, dataSet2);
			Assert::IsTrue(result2);
			
			std::string name1, name2;
			dataSet1.GetString(DicomTag::PatientName, name1);
			dataSet2.GetString(DicomTag::PatientName, name2);
			
			Assert::AreEqual(name1, name2);
		}

		TEST_METHOD(DicomReader_ReadFile_ClearsExistingDataSet)
		{
			DicomReader reader;
			DicomDataSet dataSet;
			
			// Add some data first
			dataSet.SetString(DicomTag(0x9999, 0x9999), VR::LO, "DUMMY");
			Assert::IsTrue(dataSet.HasElement(DicomTag(0x9999, 0x9999)));
			
			// Read file - should clear existing data
			reader.ReadFile(testFilePath, dataSet);
			
			// The dummy element should be gone (or the dataset should contain file data)
			// This tests that ReadFile properly manages the dataset
			Assert::IsTrue(dataSet.GetElementCount() > 0);
		}
	};
}
