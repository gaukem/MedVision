// Unit tests for DicomElement class
// Tests DICOM element data storage and retrieval

#include "CppUnitTest.h"
#include "medvision/dicom/DicomElement.h"
#include "medvision/dicom/DicomTag.h"
#include "medvision/dicom/VR.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace medvision::dicom;

namespace MedVisionDicomTests
{
	TEST_CLASS(DicomElementTests)
	{
	public:
		TEST_METHOD(DicomElement_DefaultConstructor_CreatesEmptyElement)
		{
			DicomElement element;
			
			Assert::IsTrue(element.IsEmpty());
			Assert::AreEqual(static_cast<uint32_t>(0), element.GetLength());
		}

		TEST_METHOD(DicomElement_Constructor_WithTagAndVR)
		{
			DicomTag tag(0x0010, 0x0010);
			DicomElement element(tag, VR::PN);
			
			Assert::IsTrue(element.GetTag() == tag);
			Assert::IsTrue(element.GetVR() == VR::PN);
		}

		TEST_METHOD(DicomElement_SetString_StoresStringValue)
		{
			DicomElement element(DicomTag::PatientName, VR::PN);
			bool result = element.SetString("DOE^JOHN");
			
			Assert::IsTrue(result);
			Assert::IsFalse(element.IsEmpty());
		}

		TEST_METHOD(DicomElement_GetString_RetrievesStringValue)
		{
			DicomElement element(DicomTag::PatientName, VR::PN);
			element.SetString("DOE^JOHN");
			
			std::string value;
			bool result = element.GetString(value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(std::string("DOE^JOHN"), value);
		}

		TEST_METHOD(DicomElement_GetStringValue_ReturnsStringDirectly)
		{
			DicomElement element(DicomTag::PatientID, VR::LO);
			element.SetString("PATIENT001");
			
			std::string value = element.GetStringValue();
			
			Assert::AreEqual(std::string("PATIENT001"), value);
		}

		TEST_METHOD(DicomElement_SetString_WithEmptyString)
		{
			DicomElement element(DicomTag::PatientName, VR::PN);
			bool result = element.SetString("");
			
			Assert::IsTrue(result);
			
			std::string value;
			element.GetString(value);
			Assert::AreEqual(std::string(""), value);
		}

		TEST_METHOD(DicomElement_SetUInt16_StoresUnsignedShort)
		{
			DicomElement element(DicomTag::Rows, VR::US);
			bool result = element.SetUInt16(512);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint32_t>(2), element.GetLength());
		}

		TEST_METHOD(DicomElement_GetUInt16_RetrievesUnsignedShort)
		{
			DicomElement element(DicomTag::Rows, VR::US);
			element.SetUInt16(512);
			
			uint16_t value;
			bool result = element.GetUInt16(value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint16_t>(512), value);
		}

		TEST_METHOD(DicomElement_SetUInt32_StoresUnsignedLong)
		{
			DicomElement element(DicomTag(0x0008, 0x0051), VR::UL);
			bool result = element.SetUInt32(4294967295U);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint32_t>(4), element.GetLength());
		}

		TEST_METHOD(DicomElement_GetUInt32_RetrievesUnsignedLong)
		{
			DicomElement element(DicomTag(0x0008, 0x0051), VR::UL);
			uint32_t expectedValue = 4294967295U;
			element.SetUInt32(expectedValue);
			
			uint32_t value;
			bool result = element.GetUInt32(value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(expectedValue, value);
		}

		TEST_METHOD(DicomElement_SetInt16_StoresSignedShort)
		{
			DicomElement element(DicomTag(0x0020, 0x0013), VR::SS);
			bool result = element.SetInt16(-100);
			
			Assert::IsTrue(result);
		}

		TEST_METHOD(DicomElement_GetInt16_RetrievesSignedShort)
		{
			DicomElement element(DicomTag(0x0020, 0x0013), VR::SS);
			element.SetInt16(-100);
			
			int16_t value;
			bool result = element.GetInt16(value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<int16_t>(-100), value);
		}

		TEST_METHOD(DicomElement_SetInt32_StoresSignedLong)
		{
			DicomElement element(DicomTag(0x0020, 0x0013), VR::SL);
			bool result = element.SetInt32(-1000000);
			
			Assert::IsTrue(result);
		}

		TEST_METHOD(DicomElement_GetInt32_RetrievesSignedLong)
		{
			DicomElement element(DicomTag(0x0020, 0x0013), VR::SL);
			element.SetInt32(-1000000);
			
			int32_t value;
			bool result = element.GetInt32(value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(-1000000, value);
		}

		TEST_METHOD(DicomElement_SetFloat_StoresFloatValue)
		{
			DicomElement element(DicomTag(0x0018, 0x0050), VR::FL);
			bool result = element.SetFloat(3.14159f);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint32_t>(4), element.GetLength());
		}

		TEST_METHOD(DicomElement_GetFloat_RetrievesFloatValue)
		{
			DicomElement element(DicomTag(0x0018, 0x0050), VR::FL);
			element.SetFloat(3.14159f);
			
			float value;
			bool result = element.GetFloat(value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(3.14159f, value, 0.00001f);
		}

		TEST_METHOD(DicomElement_SetDouble_StoresDoubleValue)
		{
			DicomElement element(DicomTag(0x0018, 0x0088), VR::FD);
			bool result = element.SetDouble(2.718281828);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint32_t>(8), element.GetLength());
		}

		TEST_METHOD(DicomElement_GetDouble_RetrievesDoubleValue)
		{
			DicomElement element(DicomTag(0x0018, 0x0088), VR::FD);
			element.SetDouble(2.718281828);
			
			double value;
			bool result = element.GetDouble(value);
			
			Assert::IsTrue(result);
			Assert::AreEqual(2.718281828, value, 0.000000001);
		}

		TEST_METHOD(DicomElement_SetData_WithByteArray)
		{
			DicomElement element(DicomTag::PixelData, VR::OB);
			uint8_t data[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
			
			bool result = element.SetData(data, 5);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint32_t>(5), element.GetLength());
		}

		TEST_METHOD(DicomElement_SetData_WithVector)
		{
			DicomElement element(DicomTag::PixelData, VR::OB);
			std::vector<uint8_t> data = { 0xAA, 0xBB, 0xCC, 0xDD };
			
			bool result = element.SetData(data);
			
			Assert::IsTrue(result);
			Assert::AreEqual(static_cast<uint32_t>(4), element.GetLength());
		}

		TEST_METHOD(DicomElement_GetData_ReturnsCorrectPointer)
		{
			DicomElement element(DicomTag::PixelData, VR::OB);
			uint8_t data[] = { 0x01, 0x02, 0x03 };
			element.SetData(data, 3);
			
			const uint8_t* retrievedData = element.GetData();
			
			Assert::IsNotNull(retrievedData);
			Assert::AreEqual(static_cast<uint8_t>(0x01), retrievedData[0]);
			Assert::AreEqual(static_cast<uint8_t>(0x02), retrievedData[1]);
			Assert::AreEqual(static_cast<uint8_t>(0x03), retrievedData[2]);
		}

		TEST_METHOD(DicomElement_GetDataVector_ReturnsVector)
		{
			DicomElement element(DicomTag::PixelData, VR::OB);
			std::vector<uint8_t> data = { 0xAA, 0xBB, 0xCC };
			element.SetData(data);
			
			const std::vector<uint8_t>& retrievedVector = element.GetDataVector();
			
			Assert::AreEqual(static_cast<size_t>(3), retrievedVector.size());
			Assert::AreEqual(static_cast<uint8_t>(0xAA), retrievedVector[0]);
			Assert::AreEqual(static_cast<uint8_t>(0xBB), retrievedVector[1]);
			Assert::AreEqual(static_cast<uint8_t>(0xCC), retrievedVector[2]);
		}

		TEST_METHOD(DicomElement_IsEmpty_ReturnsTrueForNewElement)
		{
			DicomElement element(DicomTag::PatientName, VR::PN);
			
			Assert::IsTrue(element.IsEmpty());
		}

		TEST_METHOD(DicomElement_IsEmpty_ReturnsFalseAfterSetData)
		{
			DicomElement element(DicomTag::PatientName, VR::PN);
			element.SetString("TEST");
			
			Assert::IsFalse(element.IsEmpty());
		}

		TEST_METHOD(DicomElement_GetLength_ReturnsCorrectLength)
		{
			DicomElement element(DicomTag::PatientID, VR::LO);
			element.SetString("PATIENT001");
			
			uint32_t length = element.GetLength();
			
			Assert::AreEqual(static_cast<uint32_t>(10), length);
		}

		TEST_METHOD(DicomElement_MultipleSetCalls_OverwritesData)
		{
			DicomElement element(DicomTag::PatientName, VR::PN);
			
			element.SetString("FIRST");
			element.SetString("SECOND");
			
			std::string value;
			element.GetString(value);
			
			Assert::AreEqual(std::string("SECOND"), value);
		}

		TEST_METHOD(DicomElement_ZeroValues_StoredCorrectly)
		{
			DicomElement element(DicomTag::Rows, VR::US);
			element.SetUInt16(0);
			
			uint16_t value;
			element.GetUInt16(value);
			
			Assert::AreEqual(static_cast<uint16_t>(0), value);
		}
	};
}
