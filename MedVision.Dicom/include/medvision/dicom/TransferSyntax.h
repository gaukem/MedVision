#pragma once

#include <string>

namespace medvision
{
	namespace dicom
	{

		/// DICOM Transfer Syntax identifiers and utilities
		class TransferSyntax
		{
		public:
			// Implicit VR Little Endian (default)
			static const std::string ImplicitVRLittleEndian;  // 1.2.840.10008.1.2

			// Explicit VR
			static const std::string ExplicitVRLittleEndian;  // 1.2.840.10008.1.2.1
			static const std::string ExplicitVRBigEndian;     // 1.2.840.10008.1.2.2 (retired)

			// Compressed (not implemented initially)
			static const std::string JPEGBaseline;            // 1.2.840.10008.1.2.4.50
			static const std::string JPEGLossless;            // 1.2.840.10008.1.2.4.57
			static const std::string JPEG2000Lossless;        // 1.2.840.10008.1.2.4.90
			static const std::string RLELossless;             // 1.2.840.10008.1.2.5

			/// Check if transfer syntax uses explicit VR
			static bool IsExplicitVR(const std::string& uid);

			/// Check if transfer syntax uses big endian byte order
			static bool IsBigEndian(const std::string& uid);

			/// Check if transfer syntax uses compression
			static bool IsCompressed(const std::string& uid);

			/// Get human-readable name for transfer syntax
			static std::string GetName(const std::string& uid);
		};

	} // namespace dicom
} // namespace medvision
