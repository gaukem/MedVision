#include "medvision/dicom/DicomDictionary.h"
#include <map>

namespace medvision
{
	namespace dicom
	{

		const std::map<uint32_t, DicomDictionary::Entry>& DicomDictionary::GetEntries()
		{
			static std::map<uint32_t, Entry> entries;

			if (entries.empty())
			{
				InitializeDictionary();
			}

			return entries;
		}

		void DicomDictionary::InitializeDictionary()
		{
			static std::map<uint32_t, Entry> entries;

			// File Meta Information
			entries[0x00020000] = { VR::UL, "File Meta Information Group Length", "FileMetaInformationGroupLength" };
			entries[0x00020001] = { VR::OB, "File Meta Information Version", "FileMetaInformationVersion" };
			entries[0x00020002] = { VR::UI, "Media Storage SOP Class UID", "MediaStorageSOPClassUID" };
			entries[0x00020003] = { VR::UI, "Media Storage SOP Instance UID", "MediaStorageSOPInstanceUID" };
			entries[0x00020010] = { VR::UI, "Transfer Syntax UID", "TransferSyntaxUID" };
			entries[0x00020012] = { VR::UI, "Implementation Class UID", "ImplementationClassUID" };
			entries[0x00020013] = { VR::SH, "Implementation Version Name", "ImplementationVersionName" };

			// Patient Module
			entries[0x00100010] = { VR::PN, "Patient's Name", "PatientName" };
			entries[0x00100020] = { VR::LO, "Patient ID", "PatientID" };
			entries[0x00100030] = { VR::DA, "Patient's Birth Date", "PatientBirthDate" };
			entries[0x00100040] = { VR::CS, "Patient's Sex", "PatientSex" };
			entries[0x00101010] = { VR::AS, "Patient's Age", "PatientAge" };
			entries[0x00101020] = { VR::DS, "Patient's Size", "PatientSize" };
			entries[0x00101030] = { VR::DS, "Patient's Weight", "PatientWeight" };

			// Study Module
			entries[0x00080020] = { VR::DA, "Study Date", "StudyDate" };
			entries[0x00080030] = { VR::TM, "Study Time", "StudyTime" };
			entries[0x00080050] = { VR::SH, "Accession Number", "AccessionNumber" };
			entries[0x00080060] = { VR::CS, "Modality", "Modality" };
			entries[0x00080070] = { VR::LO, "Manufacturer", "Manufacturer" };
			entries[0x00080080] = { VR::LO, "Institution Name", "InstitutionName" };
			entries[0x00080090] = { VR::PN, "Referring Physician's Name", "ReferringPhysicianName" };
			entries[0x00081030] = { VR::LO, "Study Description", "StudyDescription" };

			// Series Module
			entries[0x00200010] = { VR::SH, "Study ID", "StudyID" };
			entries[0x00200011] = { VR::IS, "Series Number", "SeriesNumber" };
			entries[0x00200013] = { VR::IS, "Instance Number", "InstanceNumber" };
			entries[0x0020000D] = { VR::UI, "Study Instance UID", "StudyInstanceUID" };
			entries[0x0020000E] = { VR::UI, "Series Instance UID", "SeriesInstanceUID" };
			entries[0x00080018] = { VR::UI, "SOP Instance UID", "SOPInstanceUID" };
			entries[0x00080016] = { VR::UI, "SOP Class UID", "SOPClassUID" };

			// Image Module
			entries[0x00280002] = { VR::US, "Samples per Pixel", "SamplesPerPixel" };
			entries[0x00280004] = { VR::CS, "Photometric Interpretation", "PhotometricInterpretation" };
			entries[0x00280010] = { VR::US, "Rows", "Rows" };
			entries[0x00280011] = { VR::US, "Columns", "Columns" };
			entries[0x00280030] = { VR::DS, "Pixel Spacing", "PixelSpacing" };
			entries[0x00280100] = { VR::US, "Bits Allocated", "BitsAllocated" };
			entries[0x00280101] = { VR::US, "Bits Stored", "BitsStored" };
			entries[0x00280102] = { VR::US, "High Bit", "HighBit" };
			entries[0x00280103] = { VR::US, "Pixel Representation", "PixelRepresentation" };
			entries[0x00281050] = { VR::DS, "Window Center", "WindowCenter" };
			entries[0x00281051] = { VR::DS, "Window Width", "WindowWidth" };
			entries[0x00281052] = { VR::DS, "Rescale Intercept", "RescaleIntercept" };
			entries[0x00281053] = { VR::DS, "Rescale Slope", "RescaleSlope" };

			// Pixel Data
			entries[0x7FE00010] = { VR::OW, "Pixel Data", "PixelData" };
		}

		VR DicomDictionary::GetVR(const DicomTag& tag)
		{
			const Entry* entry = GetEntry(tag);
			if (entry != nullptr)
			{
				return entry->vr;
			}
			return VR::UN;
		}

		std::string DicomDictionary::GetName(const DicomTag& tag)
		{
			const Entry* entry = GetEntry(tag);
			if (entry != nullptr)
			{
				return entry->name;
			}
			return "Unknown";
		}

		std::string DicomDictionary::GetKeyword(const DicomTag& tag)
		{
			const Entry* entry = GetEntry(tag);
			if (entry != nullptr)
			{
				return entry->keyword;
			}
			return "Unknown";
		}

		const DicomDictionary::Entry* DicomDictionary::GetEntry(const DicomTag& tag)
		{
			const auto& entries = GetEntries();
			auto it = entries.find(tag.GetTag());
			if (it != entries.end())
			{
				return &(it->second);
			}
			return nullptr;
		}

		bool DicomDictionary::Contains(const DicomTag& tag)
		{
			return GetEntry(tag) != nullptr;
		}

	} // namespace dicom
} // namespace medvision
