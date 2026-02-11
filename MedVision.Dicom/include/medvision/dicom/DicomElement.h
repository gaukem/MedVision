#pragma once

#include "DicomTag.h"
#include "VR.h"
#include <cstdint>
#include <vector>
#include <string>
#include <memory>

namespace medvision
{
	namespace dicom
	{

		/// Represents a single DICOM data element
		class DicomElement
		{
		public:
			DicomElement();
			DicomElement(const DicomTag& tag, VR vr);
			~DicomElement();

			const DicomTag& GetTag() const { return tag_; }
			VR GetVR() const { return vr_; }
			uint32_t GetLength() const { return length_; }

			// Data access methods
			bool IsEmpty() const { return length_ == 0; }
			const uint8_t* GetData() const { return data_.data(); }
			const std::vector<uint8_t>& GetDataVector() const { return data_; }

			// String value methods
			bool SetString(const std::string& value);
			bool GetString(std::string& value) const;
			std::string GetStringValue() const;

			// Integer value methods
			bool SetInt16(int16_t value);
			bool SetInt32(int32_t value);
			bool GetInt16(int16_t& value) const;
			bool GetInt32(int32_t& value) const;

			// Unsigned integer methods
			bool SetUInt16(uint16_t value);
			bool SetUInt32(uint32_t value);
			bool GetUInt16(uint16_t& value) const;
			bool GetUInt32(uint32_t& value) const;

			// Float value methods
			bool SetFloat(float value);
			bool SetDouble(double value);
			bool GetFloat(float& value) const;
			bool GetDouble(double& value) const;

			// Raw data methods
			bool SetData(const uint8_t* data, uint32_t length);
			bool SetData(const std::vector<uint8_t>& data);

		private:
			DicomTag tag_;
			VR vr_;
			uint32_t length_;
			std::vector<uint8_t> data_;
		};

	} // namespace dicom
} // namespace medvision
