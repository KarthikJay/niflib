#pragma once

#include <string>
#include <cstddef>

#include "nif_enum.hpp"

namespace NIF
{
	struct NIFInfo
	{
		NIFVersion version;
		uint user_version_1;
		uint user_version_2;
		/*
		* Specifies which low-level number storage format to use.
		* Should match the processor type for the target system.
		*/
		EndianType endian;
		// The name of the creator of the NIF file
		std::string creator;
		// The name of tool used to create the NIF file.
		std::string exportInfo1;
		// Additional tool info
		std::string exportInfo2;
	};
}