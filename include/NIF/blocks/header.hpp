#pragma once

#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>

#include <NIF/enums.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	//! Information about how the NIF was exported, part of the NIF header block.
	class NIF_API ExportInfo
	{
	public:
		//! Name of the creator of the NIF
		std::string creator;
		//! Additional information strings about export tool that created the NIF
		std::array<std::string, 3> info;
		//! Declares if additional information strings are used
		bool use_extra;

		ExportInfo();
		//! Output export information as string
		std::string str();
	private:
		const uint32_t kOldInfoSize = 2;
		//! Write export information to NIF binary
		NIF_API friend std::ostream& operator<<(std::ostream& out, const ExportInfo& obj);
		//! Read export information from NIF binary
		NIF_API friend std::istream& operator>>(std::istream& in, ExportInfo& obj);
	};


	//! \note NIF header is always in little endian.
	class NIF_API Header
	{
	public:
		//! Header version string
		std::string header_line;
		//! \deprecated Only found in V3.1 and older
		//! Copyright information
		std::array<std::string, 3> copyright;
		//! The NIF version in 32-bit hexadecimal notation
		uint32_t version;
		//! An extra version number for companies that decide to modify the file format.
		uint32_t user_version_1;
		//! Number of file objects
		mutable uint32_t num_blocks;
		//! An extra version number.
		//! Possibly used by Bethesda to denote Havok version
		uint32_t user_version_2;
		//! \note Started in NIF Version 30.0.0.2
		//! An optional PNG image preview size (inlcudes number of images in first 8 bytes)
		uint32_t image_preview_size;
		//! The endianness of the data in the file.
		EndianType endian;
		//! Contains additional export tool information.
		ExportInfo export_info;
		//! Number of object types in this NIF
		mutable uint16_t num_block_type;
		//! Vector of all object type names used in this NIF
		std::vector<std::string> block_type_names;
		//! Vector of block index in alignment with corresponding block type names
		std::vector<uint16_t> block_index;
		//! Vector of block sizes in alignment with block_type_index
		std::vector<uint32_t> block_size;
		//! Number of block names
		mutable uint32_t num_block_names;
		//! Max length of block names
		uint32_t max_name_length;
		//! Vector of block names
		std::vector<std::string> block_names;
		//! Number of groups
		uint32_t num_groups;

		Header();
		//! Get the NIF version
		//! \return The NIF version in 32-bit hexadecimal notation
		uint32_t GetVersion();
		//! Output NIFHeader as string
		std::string str();
	private:
		//! Update num member variables from their vectors
		void UpdateNums();
		//! Write NIFHeader to NIF binary
		NIF_API friend std::ostream& operator<<(std::ostream& out, const Header& obj);
		//! Read NIFHeader from NIF binary
		NIF_API friend std::istream& operator>>(std::istream& in, Header& obj);
	};
}