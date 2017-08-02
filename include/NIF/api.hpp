#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>

#include <NIF/export_visibility.hpp>

namespace NIF
{
	//! Forward declarations
	class Object;
	class Header;

	//! Reads the header of the given NIF by file name and returns the NIF version
	//! if it is a valid NIF. Call this function prior to calling ReadNifList
	//! or ReadNifTree, if you want to make sure that its NIF version is supported
	//! before trying to read it.
	//! \param[in] file_name - The absolute path to the NIF which includes the file name and the location of the NIF.
	//! \return The version of the NIF, in 32-bit hexadecimal format. If the file is not a NIF, it returns VER_INVALID.
	//! \throws RuntimeError If the file is not a valid NIF.
	NIF_API uint32_t GetNifVersion(const std::string& file_name);

	//! Returns the nif info without reading the entire file which includes the nif version,
	//! the nif user version1 and the nif user version2
	//! \param[in] file_name - The absolute path to the NIF which includes the file name and the location of the NIF.
	//! \return The nif info structure which contains the nif header info
	NIF_API Header ReadHeaderInfo(const std::string &file_name);

	NIF_API std::vector<std::shared_ptr<Object>> ReadNIFObjects(const std::string &file_name);

	NIF_API std::shared_ptr<Object> ReadNIFTree(const std::string &filename);
}