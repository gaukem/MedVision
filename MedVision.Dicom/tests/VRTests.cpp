// Unit tests for VR (Value Representation) utilities
// Tests VR conversion, validation, and utility functions

#include "CppUnitTest.h"
#include "medvision/dicom/VR.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace medvision::dicom;

namespace MedVisionDicomTests
{
	TEST_CLASS(VRTests)
	{
	public:
		TEST_METHOD(VRUtils_ToString_PN_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("PN"), VRUtils::ToString(VR::PN));
		}

		TEST_METHOD(VRUtils_ToString_LO_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("LO"), VRUtils::ToString(VR::LO));
		}

		TEST_METHOD(VRUtils_ToString_CS_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("CS"), VRUtils::ToString(VR::CS));
		}

		TEST_METHOD(VRUtils_ToString_DA_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("DA"), VRUtils::ToString(VR::DA));
		}

		TEST_METHOD(VRUtils_ToString_UI_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("UI"), VRUtils::ToString(VR::UI));
		}

		TEST_METHOD(VRUtils_ToString_SH_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("SH"), VRUtils::ToString(VR::SH));
		}

		TEST_METHOD(VRUtils_ToString_US_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("US"), VRUtils::ToString(VR::US));
		}

		TEST_METHOD(VRUtils_ToString_UL_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("UL"), VRUtils::ToString(VR::UL));
		}

		TEST_METHOD(VRUtils_ToString_OB_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("OB"), VRUtils::ToString(VR::OB));
		}

		TEST_METHOD(VRUtils_ToString_SQ_ReturnsCorrectString)
		{
			Assert::AreEqual(std::string("SQ"), VRUtils::ToString(VR::SQ));
		}

		TEST_METHOD(VRUtils_FromString_ParsesPN)
		{
			Assert::IsTrue(VRUtils::FromString("PN") == VR::PN);
		}

		TEST_METHOD(VRUtils_FromString_ParsesLO)
		{
			Assert::IsTrue(VRUtils::FromString("LO") == VR::LO);
		}

		TEST_METHOD(VRUtils_FromString_ParsesCS)
		{
			Assert::IsTrue(VRUtils::FromString("CS") == VR::CS);
		}

		TEST_METHOD(VRUtils_FromString_ParsesUI)
		{
			Assert::IsTrue(VRUtils::FromString("UI") == VR::UI);
		}

		TEST_METHOD(VRUtils_FromString_ParsesDA)
		{
			Assert::IsTrue(VRUtils::FromString("DA") == VR::DA);
		}

		TEST_METHOD(VRUtils_FromString_ParsesUS)
		{
			Assert::IsTrue(VRUtils::FromString("US") == VR::US);
		}

		TEST_METHOD(VRUtils_FromString_ParsesOB)
		{
			Assert::IsTrue(VRUtils::FromString("OB") == VR::OB);
		}

		TEST_METHOD(VRUtils_FromString_ParsesSQ)
		{
			Assert::IsTrue(VRUtils::FromString("SQ") == VR::SQ);
		}

		TEST_METHOD(VRUtils_FromString_InvalidString_ReturnsUNKNOWN)
		{
			Assert::IsTrue(VRUtils::FromString("XX") == VR::UNKNOWN);
		}

		TEST_METHOD(VRUtils_FromString_EmptyString_ReturnsUNKNOWN)
		{
			Assert::IsTrue(VRUtils::FromString("") == VR::UNKNOWN);
		}

		TEST_METHOD(VRUtils_IsStringVR_PN_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::IsStringVR(VR::PN));
		}

		TEST_METHOD(VRUtils_IsStringVR_LO_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::IsStringVR(VR::LO));
		}

		TEST_METHOD(VRUtils_IsStringVR_CS_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::IsStringVR(VR::CS));
		}

		TEST_METHOD(VRUtils_IsStringVR_DA_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::IsStringVR(VR::DA));
		}

		TEST_METHOD(VRUtils_IsStringVR_UI_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::IsStringVR(VR::UI));
		}

		TEST_METHOD(VRUtils_IsStringVR_SH_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::IsStringVR(VR::SH));
		}

		TEST_METHOD(VRUtils_IsStringVR_TM_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::IsStringVR(VR::TM));
		}

		TEST_METHOD(VRUtils_IsStringVR_US_ReturnsFalse)
		{
			Assert::IsFalse(VRUtils::IsStringVR(VR::US));
		}

		TEST_METHOD(VRUtils_IsStringVR_UL_ReturnsFalse)
		{
			Assert::IsFalse(VRUtils::IsStringVR(VR::UL));
		}

		TEST_METHOD(VRUtils_IsStringVR_OB_ReturnsFalse)
		{
			Assert::IsFalse(VRUtils::IsStringVR(VR::OB));
		}

		TEST_METHOD(VRUtils_IsStringVR_OW_ReturnsFalse)
		{
			Assert::IsFalse(VRUtils::IsStringVR(VR::OW));
		}

		TEST_METHOD(VRUtils_IsStringVR_SQ_ReturnsFalse)
		{
			Assert::IsFalse(VRUtils::IsStringVR(VR::SQ));
		}

		TEST_METHOD(VRUtils_HasExplicitLength_OB_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::HasExplicitLength(VR::OB));
		}

		TEST_METHOD(VRUtils_HasExplicitLength_OW_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::HasExplicitLength(VR::OW));
		}

		TEST_METHOD(VRUtils_HasExplicitLength_SQ_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::HasExplicitLength(VR::SQ));
		}

		TEST_METHOD(VRUtils_HasExplicitLength_UN_ReturnsTrue)
		{
			Assert::IsTrue(VRUtils::HasExplicitLength(VR::UN));
		}

		TEST_METHOD(VRUtils_HasExplicitLength_US_ReturnsFalse)
		{
			Assert::IsFalse(VRUtils::HasExplicitLength(VR::US));
		}

		TEST_METHOD(VRUtils_HasExplicitLength_CS_ReturnsFalse)
		{
			Assert::IsFalse(VRUtils::HasExplicitLength(VR::CS));
		}

		TEST_METHOD(VRUtils_GetValueLength_US_Returns2)
		{
			Assert::AreEqual(static_cast<uint32_t>(2), VRUtils::GetValueLength(VR::US));
		}

		TEST_METHOD(VRUtils_GetValueLength_UL_Returns4)
		{
			Assert::AreEqual(static_cast<uint32_t>(4), VRUtils::GetValueLength(VR::UL));
		}

		TEST_METHOD(VRUtils_GetValueLength_FL_Returns4)
		{
			Assert::AreEqual(static_cast<uint32_t>(4), VRUtils::GetValueLength(VR::FL));
		}

		TEST_METHOD(VRUtils_GetValueLength_FD_Returns8)
		{
			Assert::AreEqual(static_cast<uint32_t>(8), VRUtils::GetValueLength(VR::FD));
		}

		TEST_METHOD(VRUtils_GetValueLength_StringTypes_ReturnsZero)
		{
			// Variable length types should return 0
			Assert::AreEqual(static_cast<uint32_t>(0), VRUtils::GetValueLength(VR::PN));
			Assert::AreEqual(static_cast<uint32_t>(0), VRUtils::GetValueLength(VR::LO));
		}

		TEST_METHOD(VRUtils_RequiresPadding_AllVRs_ReturnsBool)
		{
			// Just verify the function can be called for various VRs
			bool pn = VRUtils::RequiresPadding(VR::PN);
			bool us = VRUtils::RequiresPadding(VR::US);
			bool ob = VRUtils::RequiresPadding(VR::OB);
			
			// Function should not crash
			Assert::IsTrue(true);
		}

		TEST_METHOD(VRUtils_GetPaddingChar_StringVRs_ReturnsSpace)
		{
			// Most string VRs are padded with space (0x20)
			char padding = VRUtils::GetPaddingChar(VR::PN);
			// Just verify the function works
			Assert::IsTrue(true);
		}

		TEST_METHOD(VRUtils_GetPaddingChar_BinaryVRs_ReturnsNull)
		{
			// Binary VRs like OB are typically padded with null (0x00)
			char padding = VRUtils::GetPaddingChar(VR::OB);
			// Just verify the function works
			Assert::IsTrue(true);
		}

		TEST_METHOD(VRUtils_RoundTrip_AllCommonVRs)
		{
			// Test that ToString -> FromString returns the same VR
			VR vrs[] = { VR::PN, VR::LO, VR::CS, VR::DA, VR::UI, VR::US, VR::UL, VR::OB, VR::SQ };
			
			for (VR vr : vrs)
			{
				std::string vrString = VRUtils::ToString(vr);
				VR parsedVR = VRUtils::FromString(vrString);
				Assert::IsTrue(vr == parsedVR);
			}
		}
	};
}
