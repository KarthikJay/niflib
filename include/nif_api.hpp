#pragma once

#include <string>
#include <cstdint>

#include "export_visibility.hpp"
#include "nif_header.hpp"

namespace NIF
{
	//! Reads the header of the given NIF by file name and returns the NIF version
	//! if it is a valid NIF. Call this function prior to calling ReadNifList
	//! or ReadNifTree, if you want to make sure that its NIF version is supported
	//! before trying to read it.
	//! \param file_name The name of the file to load, or the absolute path if it is not in the working directory.
	//! \return The version of the NIF, in 32-bit hexadecimal format. If the file is not a NIF, it returns VER_INVALID.
	//! \throws RuntimeError If the file is not a valid NIF.
	NIF_API uint32_t GetNifVersion(const std::string& file_name);

	//! Returns the nif info without reading the entire file which includes the nif version,
	//! the nif user version1 and the nif user version2
	//! \param The absolute path to the NIF which includes the file name and the location of the NIF
	//! \return The nif info structure which contains the nif header info
	NIF_API NIFHeader ReadHeaderInfo(const std::string &file_name);

}