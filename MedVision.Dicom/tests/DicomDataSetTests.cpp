// Unit tests for DicomDataSet class
// Tests dataset management, element operations, and data retrieval

#include "CppUnitTest.h"
#include "medvision/dicom/DicomDataSet.h"
#include "medvision/dicom/DicomTag.h"
#include "medvision/dicom/VR.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace medvision::dicom;

namespace MedVisionDicomTests
{
	TEST_CLASS(DicomDataSetTests)
	{
	public:
		TEST_METHOD(DicomDataSet_Constructor_CreatesEmptyDataSet)
		{
			DicomDataSet dataSet;
			
			Assert::AreEqual(static_cast<size_t>(0), dataSet.GetElementCount());
		}

		TEST_METHOD(DicomDataSet_SetString_AddsStringElement)
		{
			DicomDataSet dataSet;
			bool result = dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<size_t>(1), dataSet.GetElementCount());
		}

		TEST_METHOD(DicomDataSet_GetString_RetrievesStringElement)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			
			std::string value;
			bool result = dataSet.GetString(DicomTag::PatientName, value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(std::string("DOE^JOHN"), value);
		}

		TEST_METHOD(DicomDataSet_GetString_ReturnsFalseForNonexistentElement)
		{
			DicomDataSet dataSet;
			std::string value;
			
			bool result = dataSet.GetString(DicomTag::PatientName, value);
			
			Assert::IsFalse(result);
		}

		TEST_METHOD(DicomDataSet_SetString_UpdatesExistingElement)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			dataSet.SetString(DicomTag::PatientName, VR::PN, "SMITH^JANE");
			
			std::string value;
			dataSet.GetString(DicomTag::PatientName, value);
			
			Assert::AreEqual(std::string("SMITH^JANE"), value);
			Assert::AreEqual(static_cast<size_t>(1), dataSet.GetElementCount());
		}

		TEST_METHOD(DicomDataSet_SetUInt16_AddsNumericElement)
		{
			DicomDataSet dataSet;
			bool result = dataSet.SetUInt16(DicomTag::Rows, 512);
			
			Assert::IsTrue(result);
			
			uint16_t value;
			dataSet.GetUInt16(DicomTag::Rows, value);
			Assert::AreEqual(static_cast<uint16_t>(512), value);
		}

		TEST_METHOD(DicomDataSet_SetUInt16_WithZeroValue)
		{
			DicomDataSet dataSet;
			dataSet.SetUInt16(DicomTag::Rows, 0);
			
			uint16_t value;
			bool result = dataSet.GetUInt16(DicomTag::Rows, value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint16_t>(0), value);
		}

		TEST_METHOD(DicomDataSet_SetInt32_AddsSignedIntegerElement)
		{
			DicomDataSet dataSet;
			bool result = dataSet.SetInt32(DicomTag(0x0020, 0x0013), -100);
			
			Assert::IsTrue(result);
			
			int32_t value;
			dataSet.GetInt32(DicomTag(0x0020, 0x0013), value);
			Assert::AreEqual(-100, value);
		}

		TEST_METHOD(DicomDataSet_SetUInt32_AddsLargeNumericElement)
		{
			DicomDataSet dataSet;
			uint32_t expectedValue = 4294967295U;
			bool result = dataSet.SetUInt32(DicomTag(0x0008, 0x0051), expectedValue);
			
			Assert::IsTrue(result);
			
			uint32_t value;
			dataSet.GetUInt32(DicomTag(0x0008, 0x0051), value);
			Assert::AreEqual(expectedValue, value);
		}

		TEST_METHOD(DicomDataSet_HasElement_ReturnsTrueForExistingElement)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientID, VR::LO, "PATIENT001");
			
			Assert::IsTrue(dataSet.HasElement(DicomTag::PatientID));
		}

		TEST_METHOD(DicomDataSet_HasElement_ReturnsFalseForNonexistentElement)
		{
			DicomDataSet dataSet;
			
			Assert::IsFalse(dataSet.HasElement(DicomTag::PatientID));
		}

		TEST_METHOD(DicomDataSet_RemoveElement_RemovesExistingElement)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientID, VR::LO, "PATIENT001");
			
			bool removed = dataSet.RemoveElement(DicomTag::PatientID);
			
			Assert::IsTrue(removed);
			Assert::IsFalse(dataSet.HasElement(DicomTag::PatientID));
			Assert::AreEqual(static_cast<size_t>(0), dataSet.GetElementCount());
		}

		TEST_METHOD(DicomDataSet_RemoveElement_ReturnsFalseForNonexistentElement)
		{
			DicomDataSet dataSet;
			
			bool removed = dataSet.RemoveElement(DicomTag::PatientID);
			
			Assert::IsFalse(removed);
		}

		TEST_METHOD(DicomDataSet_Clear_RemovesAllElements)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			dataSet.SetString(DicomTag::PatientID, VR::LO, "PATIENT001");
			dataSet.SetUInt16(DicomTag::Rows, 512);
			
			Assert::AreEqual(static_cast<size_t>(3), dataSet.GetElementCount());
			
			dataSet.Clear();
			
			Assert::AreEqual(static_cast<size_t>(0), dataSet.GetElementCount());
		}

		TEST_METHOD(DicomDataSet_Iteration_IteratesAllElements)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			dataSet.SetString(DicomTag::PatientID, VR::LO, "PATIENT001");
			dataSet.SetString(DicomTag::PatientSex, VR::CS, "M");
			
			size_t count = 0;
			for (const auto& pair : dataSet)
			{
				count++;
			}
			
			Assert::AreEqual(static_cast<size_t>(3), count);
		}

		TEST_METHOD(DicomDataSet_GetElement_ReturnsNullForNonexistentElement)
		{
			DicomDataSet dataSet;
			
			const DicomElement* element = dataSet.GetElement(DicomTag::PatientName);
			
			Assert::IsNull(element);
		}

		TEST_METHOD(DicomDataSet_GetElement_ReturnsValidElementPointer)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			
			const DicomElement* element = dataSet.GetElement(DicomTag::PatientName);
			
			Assert::IsNotNull(element);
		}

		TEST_METHOD(DicomDataSet_MultipleElements_MaintainsAllData)
		{
			DicomDataSet dataSet;
			
			dataSet.SetString(DicomTag::PatientName, VR::PN, "DOE^JOHN");
			dataSet.SetString(DicomTag::PatientID, VR::LO, "PAT001");
			dataSet.SetString(DicomTag::PatientBirthDate, VR::DA, "19800115");
			dataSet.SetString(DicomTag::PatientSex, VR::CS, "M");
			dataSet.SetUInt16(DicomTag::Rows, 512);
			dataSet.SetUInt16(DicomTag::Columns, 512);
			
			Assert::AreEqual(static_cast<size_t>(6), dataSet.GetElementCount());
			
			std::string strValue;
			uint16_t intValue;
			
			Assert::IsTrue(dataSet.GetString(DicomTag::PatientName, strValue));
			Assert::AreEqual(std::string("DOE^JOHN"), strValue);
			
			Assert::IsTrue(dataSet.GetString(DicomTag::PatientID, strValue));
			Assert::AreEqual(std::string("PAT001"), strValue);
			
			Assert::IsTrue(dataSet.GetUInt16(DicomTag::Rows, intValue));
			Assert::AreEqual(static_cast<uint16_t>(512), intValue);
		}

		TEST_METHOD(DicomDataSet_EmptyString_StoresCorrectly)
		{
			DicomDataSet dataSet;
			dataSet.SetString(DicomTag::PatientName, VR::PN, "");
			
			std::string value;
			bool result = dataSet.GetString(DicomTag::PatientName, value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(std::string(""), value);
		}

		TEST_METHOD(DicomDataSet_GetFloat_RetrievesFloatValue)
		{
			DicomDataSet dataSet;
			DicomTag testTag(0x0018, 0x0050); // Slice Thickness
			
			// First add an element manually (if SetFloat doesn't exist, this tests GetFloat)
			DicomElement element(testTag, VR::FL);
			element.SetFloat(3.5f);
			dataSet.AddElement(element);
			
			float value;
			bool result = dataSet.GetFloat(testTag, value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(3.5f, value, 0.001f);
		}

		TEST_METHOD(DicomDataSet_GetDouble_RetrievesDoubleValue)
		{
			DicomDataSet dataSet;
			DicomTag testTag(0x0018, 0x0088); // Spacing Between Slices
			
			DicomElement element(testTag, VR::FD);
			element.SetDouble(2.5);
			dataSet.AddElement(element);
			
			double value;
			bool result = dataSet.GetDouble(testTag, value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(2.5, value, 0.0001);
		}
	};
}
