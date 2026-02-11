#include "medvision/dicom/VR.h"
#include <map>

namespace medvision
{
	namespace dicom
	{

		std::string VRUtils::ToString(VR vr)
		{
			static const std::map<VR, std::string> vrToString = {
				{VR::UNKNOWN, "UN"},
				{VR::AE, "AE"}, {VR::AS, "AS"}, {VR::AT, "AT"},
				{VR::CS, "CS"}, {VR::DA, "DA"}, {VR::DS, "DS"}, {VR::DT, "DT"},
				{VR::FL, "FL"}, {VR::FD, "FD"},
				{VR::IS, "IS"},
				{VR::LO, "LO"}, {VR::LT, "LT"},
				{VR::OB, "OB"}, {VR::OD, "OD"}, {VR::OF, "OF"}, {VR::OL, "OL"}, {VR::OW, "OW"},
				{VR::PN, "PN"},
				{VR::SH, "SH"}, {VR::SL, "SL"}, {VR::SQ, "SQ"}, {VR::SS, "SS"}, {VR::ST, "ST"}, {VR::SV, "SV"},
				{VR::TM, "TM"},
				{VR::UC, "UC"}, {VR::UI, "UI"}, {VR::UL, "UL"}, {VR::UN, "UN"}, {VR::UR, "UR"}, {VR::US, "US"}, {VR::UT, "UT"}, {VR::UV, "UV"}
			};

			auto it = vrToString.find(vr);
			if (it != vrToString.end())
			{
				return it->second;
			}
			return "UN";
		}

		VR VRUtils::FromString(const std::string& vrStr)
		{
			static const std::map<std::string, VR> stringToVR = {
				{"AE", VR::AE}, {"AS", VR::AS}, {"AT", VR::AT},
				{"CS", VR::CS}, {"DA", VR::DA}, {"DS", VR::DS}, {"DT", VR::DT},
				{"FL", VR::FL}, {"FD", VR::FD},
				{"IS", VR::IS},
				{"LO", VR::LO}, {"LT", VR::LT},
				{"OB", VR::OB}, {"OD", VR::OD}, {"OF", VR::OF}, {"OL", VR::OL}, {"OW", VR::OW},
				{"PN", VR::PN},
				{"SH", VR::SH}, {"SL", VR::SL}, {"SQ", VR::SQ}, {"SS", VR::SS}, {"ST", VR::ST}, {"SV", VR::SV},
				{"TM", VR::TM},
				{"UC", VR::UC}, {"UI", VR::UI}, {"UL", VR::UL}, {"UN", VR::UN}, {"UR", VR::UR}, {"US", VR::US}, {"UT", VR::UT}, {"UV", VR::UV}
			};

			auto it = stringToVR.find(vrStr);
			if (it != stringToVR.end())
			{
				return it->second;
			}
			return VR::UNKNOWN;
		}

		bool VRUtils::IsStringVR(VR vr)
		{
			switch (vr)
			{
			case VR::AE: case VR::AS: case VR::CS: case VR::DA: case VR::DS:
			case VR::DT: case VR::IS: case VR::LO: case VR::LT: case VR::PN:
			case VR::SH: case VR::ST: case VR::TM: case VR::UC: case VR::UI:
			case VR::UR: case VR::UT:
				return true;
			default:
				return false;
			}
		}

		bool VRUtils::HasExplicitLength(VR vr)
		{
			switch (vr)
			{
			case VR::OB: case VR::OD: case VR::OF: case VR::OL: case VR::OW:
			case VR::SQ: case VR::UC: case VR::UR: case VR::UT: case VR::UN:
				return true;
			default:
				return false;
			}
		}

		uint32_t VRUtils::GetValueLength(VR vr)
		{
			switch (vr)
			{
			case VR::AT: return 4;
			case VR::FL: return 4;
			case VR::FD: return 8;
			case VR::SL: return 4;
			case VR::SS: return 2;
			case VR::UL: return 4;
			case VR::US: return 2;
			default: return 0; // Variable length
			}
		}

		bool VRUtils::RequiresPadding(VR vr)
		{
			return IsStringVR(vr) || vr == VR::OB;
		}

		char VRUtils::GetPaddingChar(VR vr)
		{
			if (vr == VR::OB)
			{
				return '\0';
			}
			if (IsStringVR(vr))
			{
				return ' ';
			}
			return '\0';
		}

	} // namespace dicom
} // namespace medvision
