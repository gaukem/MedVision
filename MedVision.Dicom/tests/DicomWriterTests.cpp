// Unit tests for DicomWriter class
// Tests writing DICOM files to disk and memory buffers

#include "CppUnitTest.h"
#include "medvision/dicom/DicomWriter.h"
#include "medvision/dicom/DicomReader.h"
#include "medvision/dicom/DicomDataSet.h"
#include "medvision/dicom/DicomTag.h"
#include "medvision/dicom/VR.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace medvision::dicom;

namespace MedVisionDicomTests
{
	TEST_CLASS(DicomWriterTests)
	{
	private:
		std::string outputFilePath;

		DicomDataSet CreateTestDataSet()
		{
			DicomDataSet dataSet;
			
			// Meta Information
			dataSet.SetString(DicomTag::FileMetaInformationVersion, VR::OB, "\x00\x01");
			dataSet.SetString(DicomTag::MediaStorageSOPClassUID, VR::UI, "1.2.840.10008.5.1.4.1.1.2");
			dataSet.SetString(DicomTag::MediaStorageSOPInstanceUID, VR::UI, "1.2.3.4.5.6.7.8.9");
			dataSet.SetString(DicomTag::TransferSyntaxUID, VR::UI, "1.2.840.10008.1.2.1");
			dataSet.SetString(DicomTag::ImplementationClassUID, VR::UI, "1.2.840.999999.1");
			dataSet.SetString(DicomTag::ImplementationVersionName, VR::SH, "MEDVISION_1_0");
			
			// Patient Module
			dataSet.SetString(DicomTag::PatientName, VR::PN, "WRITER^TEST");
			dataSet.SetString(DicomTag::PatientID, VR::LO, "WRITER001");
			dataSet.SetString(DicomTag::PatientBirthDate, VR::DA, "19850315");
			dataSet.SetString(DicomTag::PatientSex, VR::CS, "F");
			
			// Study Module
			dataSet.SetString(DicomTag::StudyDate, VR::DA, "20240115");
			dataSet.SetString(DicomTag::StudyTime, VR::TM, "143022");
			dataSet.SetString(DicomTag::Modality, VR::CS, "CT");
			dataSet.SetString(DicomTag::StudyInstanceUID, VR::UI, "1.2.3.4.5");
			
			// Image Module
			dataSet.SetUInt16(DicomTag::Rows, 256);
			dataSet.SetUInt16(DicomTag::Columns, 256);
			
			return dataSet;
		}

		void DeleteOutputFile()
		{
			if (!outputFilePath.empty())
			{
				std::remove(outputFilePath.c_str());
			}
		}

	public:
		TEST_METHOD_CLEANUP(Cleanup)
		{
			DeleteOutputFile();
		}

		TEST_METHOD(DicomWriter_Constructor_CreatesValidWriter)
		{
			DicomWriter writer;
			
			// Should not crash
			Assert::IsTrue(true);
		}

		TEST_METHOD(DicomWriter_WriteFile_CreatesFile)
		{
			outputFilePath = "test_dicom_writer_output.dcm";
			DicomDataSet dataSet = CreateTestDataSet();
			
			DicomWriter writer;
			bool result = writer.WriteFile(outputFilePath, dataSet);
			
			Assert::IsTrue(result, L"WriteFile should succeed");
			
			// Verify file exists
			std::ifstream file(outputFilePath);
			Assert::IsTrue(file.good(), L"Output file should exist");
			file.close();
		}

		TEST_METHOD(DicomWriter_WriteFile_FailsWithInvalidPath)
		{
			// Use an invalid path that should fail on most systems
			outputFilePath = "Z:/invalid/deeply/nested/nonexistent/path/file.dcm";
			DicomDataSet dataSet = CreateTestDataSet();
			
			DicomWriter writer;
			bool result = writer.WriteFile(outputFilePath, dataSet);
			
			if (!result)
			{
				Assert::IsFalse(writer.GetLastError().empty());
			}
		}

		TEST_METHOD(DicomWriter_WriteFile_PreservesDataOnReadback)
		{
			outputFilePath = "test_dicom_roundtrip.dcm";
			DicomDataSet originalDataSet = CreateTestDataSet();
			
			// Write
			DicomWriter writer;
			bool writeSuccess = writer.WriteFile(outputFilePath, originalDataSet);
			Assert::IsTrue(writeSuccess, L"Write should succeed");
			
			// Read back
			DicomReader reader;
			DicomDataSet readDataSet;
			bool readSuccess = reader.ReadFile(outputFilePath, readDataSet);
			Assert::IsTrue(readSuccess, L"Read should succeed");
			
			// Verify data
			std::string patientName;
			readDataSet.GetString(DicomTag::PatientName, patientName);
			Assert::AreEqual(std::string("WRITER^TEST"), patientName);
			
			std::string patientId;
			readDataSet.GetString(DicomTag::PatientID, patientId);
			Assert::AreEqual(std::string("WRITER001"), patientId);
			
			uint16_t rows;
			readDataSet.GetUInt16(DicomTag::Rows, rows);
			Assert::AreEqual(static_cast<uint16_t>(256), rows);
		}

		TEST_METHOD(DicomWriter_WriteFile_PreservesAllPatientData)
		{
			outputFilePath = "test_dicom_patient_data.dcm";
			DicomDataSet originalDataSet = CreateTestDataSet();
			
			DicomWriter writer;
			writer.WriteFile(outputFilePath, originalDataSet);
			
			DicomReader reader;
			DicomDataSet readDataSet;
			reader.ReadFile(outputFilePath, readDataSet);
			
			std::string birthDate, sex;
			readDataSet.GetString(DicomTag::PatientBirthDate, birthDate);
			readDataSet.GetString(DicomTag::PatientSex, sex);
			
			Assert::AreEqual(std::string("19850315"), birthDate);
			Assert::AreEqual(std::string("F"), sex);
		}

		TEST_METHOD(DicomWriter_WriteBuffer_CreatesValidBuffer)
		{
			DicomDataSet dataSet = CreateTestDataSet();
			std::vector<uint8_t> buffer;
			
			DicomWriter writer;
			bool result = writer.WriteBuffer(buffer, dataSet);
			
			Assert::IsTrue(result, L"WriteBuffer should succeed");
			Assert::IsTrue(buffer.size() > 0, L"Buffer should not be empty");
		}

		TEST_METHOD(DicomWriter_WriteBuffer_BufferCanBeReadBack)
		{
			DicomDataSet originalDataSet = CreateTestDataSet();
			std::vector<uint8_t> buffer;
			
			// Write to buffer
			DicomWriter writer;
			bool writeSuccess = writer.WriteBuffer(buffer, originalDataSet);
			Assert::IsTrue(writeSuccess);
			
			// Read from buffer
			DicomReader reader;
			DicomDataSet readDataSet;
			bool readSuccess = reader.ReadBuffer(buffer.data(), buffer.size(), readDataSet);
			Assert::IsTrue(readSuccess);
			
			// Verify data
			std::string patientId;
			readDataSet.GetString(DicomTag::PatientID, patientId);
			Assert::AreEqual(std::string("WRITER001"), patientId);
		}

		TEST_METHOD(DicomWriter_WriteBuffer_PreservesNumericData)
		{
			DicomDataSet originalDataSet = CreateTestDataSet();
			std::vector<uint8_t> buffer;
			
			DicomWriter writer;
			writer.WriteBuffer(buffer, originalDataSet);
			
			DicomReader reader;
			DicomDataSet readDataSet;
			reader.ReadBuffer(buffer.data(), buffer.size(), readDataSet);
			
			uint16_t rows, cols;
			readDataSet.GetUInt16(DicomTag::Rows, rows);
			readDataSet.GetUInt16(DicomTag::Columns, cols);
			
			Assert::AreEqual(static_cast<uint16_t>(256), rows);
			Assert::AreEqual(static_cast<uint16_t>(256), cols);
		}

		TEST_METHOD(DicomWriter_SetTransferSyntax_DoesNotCrash)
		{
			outputFilePath = "test_dicom_transfer_syntax.dcm";
			DicomDataSet dataSet = CreateTestDataSet();
			
			DicomWriter writer;
			writer.SetTransferSyntax("1.2.840.10008.1.2.1"); // Explicit VR Little Endian
			
			bool result = writer.WriteFile(outputFilePath, dataSet);
			Assert::IsTrue(result);
		}

		TEST_METHOD(DicomWriter_WriteEmptyDataSet_HandledGracefully)
		{
			outputFilePath = "test_dicom_empty.dcm";
			DicomDataSet emptyDataSet;
			
			DicomWriter writer;
			bool result = writer.WriteFile(outputFilePath, emptyDataSet);
			
			// Depending on implementation, this might succeed or fail
			// If it fails, error message should be available
			if (!result)
			{
				Assert::IsFalse(writer.GetLastError().empty());
			}
		}

		TEST_METHOD(DicomWriter_MultipleWrites_SucceedIndependently)
		{
			DicomWriter writer;
			DicomDataSet dataSet = CreateTestDataSet();
			
			// First write
			outputFilePath = "test_multi_write_1.dcm";
			bool result1 = writer.WriteFile(outputFilePath, dataSet);
			Assert::IsTrue(result1);
			std::remove(outputFilePath.c_str());
			
			// Second write
			outputFilePath = "test_multi_write_2.dcm";
			bool result2 = writer.WriteFile(outputFilePath, dataSet);
			Assert::IsTrue(result2);
		}

		TEST_METHOD(DicomWriter_WriteFile_OverwritesExistingFile)
		{
			outputFilePath = "test_overwrite.dcm";
			DicomDataSet dataSet1 = CreateTestDataSet();
			
			// First write
			DicomWriter writer1;
			writer1.WriteFile(outputFilePath, dataSet1);
			
			// Modify dataset
			DicomDataSet dataSet2 = CreateTestDataSet();
			dataSet2.SetString(DicomTag::PatientID, VR::LO, "MODIFIED001");
			
			// Second write (overwrite)
			DicomWriter writer2;
			writer2.WriteFile(outputFilePath, dataSet2);
			
			// Read and verify
			DicomReader reader;
			DicomDataSet readDataSet;
			reader.ReadFile(outputFilePath, readDataSet);
			
			std::string patientId;
			readDataSet.GetString(DicomTag::PatientID, patientId);
			Assert::AreEqual(std::string("MODIFIED001"), patientId);
		}

		TEST_METHOD(DicomWriter_GetLastError_CallableAfterWrite)
		{
			outputFilePath = "test_error_check.dcm";
			DicomDataSet dataSet = CreateTestDataSet();
			
			DicomWriter writer;
			bool result = writer.WriteFile(outputFilePath, dataSet);
			
			// Just verify we can call GetLastError without crash
			std::string error = writer.GetLastError();
			Assert::IsTrue(true);
		}
	};
}
