// Unit tests for DicomTag class
// Tests tag creation, comparison, and standard tag definitions

#include "CppUnitTest.h"
#include "medvision/dicom/DicomTag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace medvision::dicom;

namespace MedVisionDicomTests
{
	TEST_CLASS(DicomTagTests)
	{
	public:
		TEST_METHOD(DicomTag_DefaultConstructor_CreatesZeroTag)
		{
			DicomTag tag;
			
			Assert::AreEqual(static_cast<uint16_t>(0), tag.GetGroup());
			Assert::AreEqual(static_cast<uint16_t>(0), tag.GetElement());
		}

		TEST_METHOD(DicomTag_Constructor_CreatesValidTag)
		{
			DicomTag tag(0x0010, 0x0010);
			
			Assert::AreEqual(static_cast<uint16_t>(0x0010), tag.GetGroup());
			Assert::AreEqual(static_cast<uint16_t>(0x0010), tag.GetElement());
		}

		TEST_METHOD(DicomTag_ConstructorFromUInt32_CreatesValidTag)
		{
			uint32_t tagValue = (0x0010 << 16) | 0x0020;
			DicomTag tag(tagValue);
			
			Assert::AreEqual(static_cast<uint16_t>(0x0010), tag.GetGroup());
			Assert::AreEqual(static_cast<uint16_t>(0x0020), tag.GetElement());
		}

		TEST_METHOD(DicomTag_GetTag_ReturnsCorrectValue)
		{
			DicomTag tag(0x0010, 0x0020);
			uint32_t expected = (0x0010 << 16) | 0x0020;
			
			Assert::AreEqual(expected, tag.GetTag());
		}

		TEST_METHOD(DicomTag_ToString_ReturnsFormattedString)
		{
			DicomTag tag(0x0010, 0x0020);
			std::string result = tag.ToString();
			
			Assert::AreEqual(std::string("(0010,0020)"), result);
		}

		TEST_METHOD(DicomTag_ToString_WithLeadingZeros)
		{
			DicomTag tag(0x0008, 0x0005);
			std::string result = tag.ToString();
			
			Assert::AreEqual(std::string("(0008,0005)"), result);
		}

		TEST_METHOD(DicomTag_StandardTag_PatientName_HasCorrectValue)
		{
			Assert::AreEqual(static_cast<uint16_t>(0x0010), DicomTag::PatientName.GetGroup());
			Assert::AreEqual(static_cast<uint16_t>(0x0010), DicomTag::PatientName.GetElement());
		}

		TEST_METHOD(DicomTag_StandardTag_PatientID_HasCorrectValue)
		{
			Assert::AreEqual(static_cast<uint16_t>(0x0010), DicomTag::PatientID.GetGroup());
			Assert::AreEqual(static_cast<uint16_t>(0x0020), DicomTag::PatientID.GetElement());
		}

		TEST_METHOD(DicomTag_StandardTag_StudyInstanceUID_HasCorrectValue)
		{
			Assert::AreEqual(static_cast<uint16_t>(0x0020), DicomTag::StudyInstanceUID.GetGroup());
			Assert::AreEqual(static_cast<uint16_t>(0x000D), DicomTag::StudyInstanceUID.GetElement());
		}

		TEST_METHOD(DicomTag_StandardTag_Rows_HasCorrectValue)
		{
			Assert::AreEqual(static_cast<uint16_t>(0x0028), DicomTag::Rows.GetGroup());
			Assert::AreEqual(static_cast<uint16_t>(0x0010), DicomTag::Rows.GetElement());
		}

		TEST_METHOD(DicomTag_EqualityOperator_ReturnsTrueForSameTags)
		{
			DicomTag tag1(0x0010, 0x0010);
			DicomTag tag2(0x0010, 0x0010);
			
			Assert::IsTrue(tag1 == tag2);
		}

		TEST_METHOD(DicomTag_EqualityOperator_ReturnsFalseForDifferentTags)
		{
			DicomTag tag1(0x0010, 0x0010);
			DicomTag tag2(0x0010, 0x0020);
			
			Assert::IsFalse(tag1 == tag2);
		}

		TEST_METHOD(DicomTag_InequalityOperator_ReturnsTrueForDifferentTags)
		{
			DicomTag tag1(0x0010, 0x0010);
			DicomTag tag2(0x0010, 0x0020);
			
			Assert::IsTrue(tag1 != tag2);
		}

		TEST_METHOD(DicomTag_InequalityOperator_ReturnsFalseForSameTags)
		{
			DicomTag tag1(0x0010, 0x0010);
			DicomTag tag2(0x0010, 0x0010);
			
			Assert::IsFalse(tag1 != tag2);
		}

		TEST_METHOD(DicomTag_LessThanOperator_ComparesCorrectly)
		{
			DicomTag tag1(0x0010, 0x0010);
			DicomTag tag2(0x0010, 0x0020);
			
			Assert::IsTrue(tag1 < tag2);
			Assert::IsFalse(tag2 < tag1);
		}

		TEST_METHOD(DicomTag_LessThanOperator_GroupTakesPrecedence)
		{
			DicomTag tag1(0x0008, 0x0020);
			DicomTag tag2(0x0010, 0x0010);
			
			Assert::IsTrue(tag1 < tag2);
		}
	};
}
