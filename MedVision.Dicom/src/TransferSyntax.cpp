#include "medvision/dicom/TransferSyntax.h"

namespace medvision
{
	namespace dicom
	{

		const std::string TransferSyntax::ImplicitVRLittleEndian = "1.2.840.10008.1.2";
		const std::string TransferSyntax::ExplicitVRLittleEndian = "1.2.840.10008.1.2.1";
		const std::string TransferSyntax::ExplicitVRBigEndian = "1.2.840.10008.1.2.2";
		const std::string TransferSyntax::JPEGBaseline = "1.2.840.10008.1.2.4.50";
		const std::string TransferSyntax::JPEGLossless = "1.2.840.10008.1.2.4.57";
		const std::string TransferSyntax::JPEG2000Lossless = "1.2.840.10008.1.2.4.90";
		const std::string TransferSyntax::RLELossless = "1.2.840.10008.1.2.5";

		bool TransferSyntax::IsExplicitVR(const std::string& uid)
		{
			if (uid == ImplicitVRLittleEndian)
			{
				return false;
			}
			if (uid == ExplicitVRLittleEndian || uid == ExplicitVRBigEndian)
			{
				return true;
			}
			// Most compressed transfer syntaxes use explicit VR
			if (IsCompressed(uid))
			{
				return true;
			}
			// Default to explicit VR
			return true;
		}

		bool TransferSyntax::IsBigEndian(const std::string& uid)
		{
			return uid == ExplicitVRBigEndian;
		}

		bool TransferSyntax::IsCompressed(const std::string& uid)
		{
			// Check for JPEG
			if (uid.find("1.2.840.10008.1.2.4") == 0)
			{
				return true;
			}
			// Check for RLE
			if (uid == RLELossless)
			{
				return true;
			}
			return false;
		}

		std::string TransferSyntax::GetName(const std::string& uid)
		{
			if (uid == ImplicitVRLittleEndian)
			{
				return "Implicit VR Little Endian";
			}
			if (uid == ExplicitVRLittleEndian)
			{
				return "Explicit VR Little Endian";
			}
			if (uid == ExplicitVRBigEndian)
			{
				return "Explicit VR Big Endian (Retired)";
			}
			if (uid == JPEGBaseline)
			{
				return "JPEG Baseline (Process 1)";
			}
			if (uid == JPEGLossless)
			{
				return "JPEG Lossless";
			}
			if (uid == JPEG2000Lossless)
			{
				return "JPEG 2000 Lossless";
			}
			if (uid == RLELossless)
			{
				return "RLE Lossless";
			}
			return "Unknown Transfer Syntax";
		}

	} // namespace dicom
} // namespace medvision
