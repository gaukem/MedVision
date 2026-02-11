#pragma once

#include <string>

namespace medvision
{
	namespace dicom
	{

		/// DICOM Value Representation types
		enum class VR
		{
			UNKNOWN,

			// String types
			AE,  // Application Entity
			AS,  // Age String
			CS,  // Code String
			DA,  // Date
			DS,  // Decimal String
			DT,  // Date Time
			IS,  // Integer String
			LO,  // Long String
			LT,  // Long Text
			PN,  // Person Name
			SH,  // Short String
			ST,  // Short Text
			TM,  // Time
			UC,  // Unlimited Characters
			UI,  // Unique Identifier
			UR,  // URI/URL
			UT,  // Unlimited Text

			// Binary types
			AT,  // Attribute Tag
			FL,  // Floating Point Single
			FD,  // Floating Point Double
			OB,  // Other Byte
			OD,  // Other Double
			OF,  // Other Float
			OL,  // Other Long
			OW,  // Other Word
			SL,  // Signed Long
			SS,  // Signed Short
			SV,  // Signed Very Long
			UL,  // Unsigned Long
			US,  // Unsigned Short
			UV,  // Unsigned Very Long

			// Special types
			SQ,  // Sequence of Items
			UN   // Unknown
		};

		/// VR utility functions
		class VRUtils
		{
		public:
			/// Convert VR enum to 2-character string
			static std::string ToString(VR vr);

			/// Convert 2-character string to VR enum
			static VR FromString(const std::string& vrStr);

			/// Check if VR is string type
			static bool IsStringVR(VR vr);

			/// Check if VR has explicit length encoding
			static bool HasExplicitLength(VR vr);

			/// Get expected value length (0 = variable)
			static uint32_t GetValueLength(VR vr);

			/// Check if VR requires even-length padding
			static bool RequiresPadding(VR vr);

			/// Get padding character for VR type
			static char GetPaddingChar(VR vr);
		};

	} // namespace dicom
} // namespace medvision
