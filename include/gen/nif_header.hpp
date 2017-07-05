#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <array>

#include "nif_enum.hpp"
#include "gen/export_info.hpp"

namespace NIF
{
	//! \note NIFHeader is always in Little Endian.
	class NIF_API NIFHeader
	{
	public:
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
		ExportInfo export_info;
		//! Additional export info
		std::string export_info_3;
		//! Number of object types in this NIF
		mutable uint16_t num_block_type;
		//! Vector of all object type names used in this NIF
		std::vector<std::string> block_type_names;
		//! Vector of block index in alignment with corresponding block type names
		std::vector<uint16_t> block_index;
		//! Vector of block sizes in alignment with block_type_index
		std::vector<uint32_t> block_size;
		//! Number of strings
		mutable uint32_t num_strings;
		//! Max string length
		uint32_t max_string_length;
		//! Vector of strings
		std::vector<std::string> strings;
		//! /note Unknown.
		uint32_t unknown_int_2;

		NIFHeader(uint32_t version);
		//! Get the NIF version
		//! \return The NIF version in 32-bit hexadecimal notation
		uint32_t GetVersion();
	private:
		//! Update num member variables from their vectors
		void UpdateNums();
		//! Output NIFHeader as string
		friend std::stringstream& operator<< (std::stringstream& ss, const NIFHeader& nh);
		//! Write NIFHeader to NIF binary
		friend std::ofstream& operator<< (std::ofstream& outf, const NIFHeader& nh);
		//! Read NIFHeader from NIF binary
		friend std::ifstream& operator>> (std::ifstream& inf, NIFHeader& nh);
	};
}