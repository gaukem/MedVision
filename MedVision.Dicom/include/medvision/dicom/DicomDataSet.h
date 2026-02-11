#pragma once

#include "DicomElement.h"
#include "DicomTag.h"
#include <map>
#include <vector>
#include <memory>
#include <string>

namespace medvision
{
	namespace dicom
	{

		/// Container for DICOM data elements
		class DicomDataSet
		{
		public:
			DicomDataSet();
			~DicomDataSet();

			// Element management
			bool AddElement(const DicomElement& element);
			bool RemoveElement(const DicomTag& tag);
			bool HasElement(const DicomTag& tag) const;
			const DicomElement* GetElement(const DicomTag& tag) const;
			DicomElement* GetElement(const DicomTag& tag);

			// Convenience methods for common operations
			bool GetString(const DicomTag& tag, std::string& value) const;
			bool GetInt32(const DicomTag& tag, int32_t& value) const;
			bool GetUInt16(const DicomTag& tag, uint16_t& value) const;
			bool GetUInt32(const DicomTag& tag, uint32_t& value) const;
			bool GetFloat(const DicomTag& tag, float& value) const;
			bool GetDouble(const DicomTag& tag, double& value) const;

			bool SetString(const DicomTag& tag, VR vr, const std::string& value);
			bool SetInt32(const DicomTag& tag, int32_t value);
			bool SetUInt16(const DicomTag& tag, uint16_t value);
			bool SetUInt32(const DicomTag& tag, uint32_t value);

			// Dataset properties
			size_t GetElementCount() const { return elements_.size(); }
			void Clear();

			// Iteration support
			using ElementMap = std::map<uint32_t, DicomElement>;
			ElementMap::const_iterator begin() const { return elements_.begin(); }
			ElementMap::const_iterator end() const { return elements_.end(); }

		private:
			ElementMap elements_;  // Keyed by tag value (group << 16 | element)
		};

	} // namespace dicom
} // namespace medvision
