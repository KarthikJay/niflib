#pragma once

#include <string>
#include <cstdint>
#include <fstream>
#include <array>

#include "export_visibility.hpp"

namespace NIF
{
	//! Information about how the NIF was exported
	class NIF_API ExportInfo
	{
	public:
		//! Probably the number of strings that follow. 
		//! \deprecated Field only found in NIF version 10.0.1.2 and below 
		uint32_t unknown;
		//! Name of creator of the NIF
		std::string creator;
		//! Additional information strings about export tool that created the NIF
		std::array<std::string, 3> info;
		//! Declares if additional information strings are used
		bool use_extra;

		ExportInfo();
		//! Output ExportInfo as string
		std::string str();
	private:
		const uint32_t kOldInfoSize = 2;
		//! Write ExportInfo to NIF binary
		NIF_API friend std::ostream& operator<<(std::ostream& out, const ExportInfo& obj);
		//! Read ExportInfo from NIF binary
		NIF_API friend std::istream& operator>>(std::istream& in, ExportInfo& obj);
	};
}