#include "medvision/dicom/DicomElement.h"
#include <cstring>
#include <algorithm>

namespace medvision
{
	namespace dicom
	{

		DicomElement::DicomElement()
			: tag_(0, 0), vr_(VR::UNKNOWN), length_(0)
		{
		}

		DicomElement::DicomElement(const DicomTag& tag, VR vr)
			: tag_(tag), vr_(vr), length_(0)
		{
		}

		DicomElement::~DicomElement()
		{
		}

		bool DicomElement::SetString(const std::string& value)
		{
			if (!VRUtils::IsStringVR(vr_))
			{
				return false;
			}

			data_.assign(value.begin(), value.end());

			// Pad to even length if required
			if (VRUtils::RequiresPadding(vr_) && (data_.size() % 2) != 0)
			{
				data_.push_back(static_cast<uint8_t>(VRUtils::GetPaddingChar(vr_)));
			}

			length_ = static_cast<uint32_t>(data_.size());
			return true;
		}

		bool DicomElement::GetString(std::string& value) const
		{
			if (!VRUtils::IsStringVR(vr_))
			{
				return false;
			}

			value.assign(data_.begin(), data_.end());

			// Trim trailing padding
			while (!value.empty() && (value.back() == ' ' || value.back() == '\0'))
			{
				value.pop_back();
			}

			return true;
		}

		std::string DicomElement::GetStringValue() const
		{
			std::string value;
			GetString(value);
			return value;
		}

		bool DicomElement::SetInt16(int16_t value)
		{
			if (vr_ != VR::SS)
			{
				return false;
			}

			data_.resize(sizeof(int16_t));
			std::memcpy(data_.data(), &value, sizeof(int16_t));
			length_ = sizeof(int16_t);
			return true;
		}

		bool DicomElement::SetInt32(int32_t value)
		{
			if (vr_ != VR::SL)
			{
				return false;
			}

			data_.resize(sizeof(int32_t));
			std::memcpy(data_.data(), &value, sizeof(int32_t));
			length_ = sizeof(int32_t);
			return true;
		}

		bool DicomElement::GetInt16(int16_t& value) const
		{
			if (vr_ != VR::SS || length_ < sizeof(int16_t))
			{
				return false;
			}

			std::memcpy(&value, data_.data(), sizeof(int16_t));
			return true;
		}

		bool DicomElement::GetInt32(int32_t& value) const
		{
			if (vr_ != VR::SL || length_ < sizeof(int32_t))
			{
				return false;
			}

			std::memcpy(&value, data_.data(), sizeof(int32_t));
			return true;
		}

		bool DicomElement::SetUInt16(uint16_t value)
		{
			if (vr_ != VR::US && vr_ != VR::AT)
			{
				return false;
			}

			data_.resize(sizeof(uint16_t));
			std::memcpy(data_.data(), &value, sizeof(uint16_t));
			length_ = sizeof(uint16_t);
			return true;
		}

		bool DicomElement::SetUInt32(uint32_t value)
		{
			if (vr_ != VR::UL)
			{
				return false;
			}

			data_.resize(sizeof(uint32_t));
			std::memcpy(data_.data(), &value, sizeof(uint32_t));
			length_ = sizeof(uint32_t);
			return true;
		}

		bool DicomElement::GetUInt16(uint16_t& value) const
		{
			if ((vr_ != VR::US && vr_ != VR::AT) || length_ < sizeof(uint16_t))
			{
				return false;
			}

			std::memcpy(&value, data_.data(), sizeof(uint16_t));
			return true;
		}

		bool DicomElement::GetUInt32(uint32_t& value) const
		{
			if (vr_ != VR::UL || length_ < sizeof(uint32_t))
			{
				return false;
			}

			std::memcpy(&value, data_.data(), sizeof(uint32_t));
			return true;
		}

		bool DicomElement::SetFloat(float value)
		{
			if (vr_ != VR::FL)
			{
				return false;
			}

			data_.resize(sizeof(float));
			std::memcpy(data_.data(), &value, sizeof(float));
			length_ = sizeof(float);
			return true;
		}

		bool DicomElement::SetDouble(double value)
		{
			if (vr_ != VR::FD)
			{
				return false;
			}

			data_.resize(sizeof(double));
			std::memcpy(data_.data(), &value, sizeof(double));
			length_ = sizeof(double);
			return true;
		}

		bool DicomElement::GetFloat(float& value) const
		{
			if (vr_ != VR::FL || length_ < sizeof(float))
			{
				return false;
			}

			std::memcpy(&value, data_.data(), sizeof(float));
			return true;
		}

		bool DicomElement::GetDouble(double& value) const
		{
			if (vr_ != VR::FD || length_ < sizeof(double))
			{
				return false;
			}

			std::memcpy(&value, data_.data(), sizeof(double));
			return true;
		}

		bool DicomElement::SetData(const uint8_t* data, uint32_t length)
		{
			if (data == nullptr && length > 0)
			{
				return false;
			}

			data_.assign(data, data + length);
			length_ = length;
			return true;
		}

		bool DicomElement::SetData(const std::vector<uint8_t>& data)
		{
			data_ = data;
			length_ = static_cast<uint32_t>(data_.size());
			return true;
		}

	} // namespace dicom
} // namespace medvision
