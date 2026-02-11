#include "medvision/dicom/DicomDataSet.h"

namespace medvision
{
	namespace dicom
	{

		DicomDataSet::DicomDataSet()
		{
		}

		DicomDataSet::~DicomDataSet()
		{
		}

		bool DicomDataSet::AddElement(const DicomElement& element)
		{
			uint32_t key = element.GetTag().GetTag();
			elements_[key] = element;
			return true;
		}

		bool DicomDataSet::RemoveElement(const DicomTag& tag)
		{
			uint32_t key = tag.GetTag();
			auto it = elements_.find(key);
			if (it != elements_.end())
			{
				elements_.erase(it);
				return true;
			}
			return false;
		}

		bool DicomDataSet::HasElement(const DicomTag& tag) const
		{
			uint32_t key = tag.GetTag();
			return elements_.find(key) != elements_.end();
		}

		const DicomElement* DicomDataSet::GetElement(const DicomTag& tag) const
		{
			uint32_t key = tag.GetTag();
			auto it = elements_.find(key);
			if (it != elements_.end())
			{
				return &(it->second);
			}
			return nullptr;
		}

		DicomElement* DicomDataSet::GetElement(const DicomTag& tag)
		{
			uint32_t key = tag.GetTag();
			auto it = elements_.find(key);
			if (it != elements_.end())
			{
				return &(it->second);
			}
			return nullptr;
		}

		bool DicomDataSet::GetString(const DicomTag& tag, std::string& value) const
		{
			const DicomElement* element = GetElement(tag);
			if (element == nullptr)
			{
				return false;
			}
			return element->GetString(value);
		}

		bool DicomDataSet::GetInt32(const DicomTag& tag, int32_t& value) const
		{
			const DicomElement* element = GetElement(tag);
			if (element == nullptr)
			{
				return false;
			}
			return element->GetInt32(value);
		}

		bool DicomDataSet::GetUInt16(const DicomTag& tag, uint16_t& value) const
		{
			const DicomElement* element = GetElement(tag);
			if (element == nullptr)
			{
				return false;
			}
			return element->GetUInt16(value);
		}

		bool DicomDataSet::GetUInt32(const DicomTag& tag, uint32_t& value) const
		{
			const DicomElement* element = GetElement(tag);
			if (element == nullptr)
			{
				return false;
			}
			return element->GetUInt32(value);
		}

		bool DicomDataSet::GetFloat(const DicomTag& tag, float& value) const
		{
			const DicomElement* element = GetElement(tag);
			if (element == nullptr)
			{
				return false;
			}
			return element->GetFloat(value);
		}

		bool DicomDataSet::GetDouble(const DicomTag& tag, double& value) const
		{
			const DicomElement* element = GetElement(tag);
			if (element == nullptr)
			{
				return false;
			}
			return element->GetDouble(value);
		}

		bool DicomDataSet::SetString(const DicomTag& tag, VR vr, const std::string& value)
		{
			DicomElement element(tag, vr);
			if (!element.SetString(value))
			{
				return false;
			}
			return AddElement(element);
		}

		bool DicomDataSet::SetInt32(const DicomTag& tag, int32_t value)
		{
			DicomElement element(tag, VR::SL);
			if (!element.SetInt32(value))
			{
				return false;
			}
			return AddElement(element);
		}

		bool DicomDataSet::SetUInt16(const DicomTag& tag, uint16_t value)
		{
			DicomElement element(tag, VR::US);
			if (!element.SetUInt16(value))
			{
				return false;
			}
			return AddElement(element);
		}

		bool DicomDataSet::SetUInt32(const DicomTag& tag, uint32_t value)
		{
			DicomElement element(tag, VR::UL);
			if (!element.SetUInt32(value))
			{
				return false;
			}
			return AddElement(element);
		}

		void DicomDataSet::Clear()
		{
			elements_.clear();
		}

	} // namespace dicom
} // namespace medvision
