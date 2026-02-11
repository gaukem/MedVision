#pragma once

#include "DicomTag.h"
#include "VR.h"
#include <string>
#include <map>

namespace medvision
{
	namespace dicom
	{

		/// DICOM data dictionary - maps tags to VR and names
		class DicomDictionary
		{
		public:
			struct Entry
			{
				VR vr;
				std::string name;
				std::string keyword;
			};

			/// Get VR for a given tag
			static VR GetVR(const DicomTag& tag);

			/// Get name for a given tag
			static std::string GetName(const DicomTag& tag);

			/// Get keyword for a given tag
			static std::string GetKeyword(const DicomTag& tag);

			/// Get full entry for a given tag
			static const Entry* GetEntry(const DicomTag& tag);

			/// Check if tag exists in dictionary
			static bool Contains(const DicomTag& tag);

		private:
			static const std::map<uint32_t, Entry>& GetEntries();
			static void InitializeDictionary();
		};

	} // namespace dicom
} // namespace medvision
