#pragma once

#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>

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
		//! Name of export tool to create NIF
		std::string export_info_1;
		//! Additional information on the export tool that created the NIF
		std::string export_info_2;

		ExportInfo();
	private:
		//! Output ExportInfo as string
		friend std::stringstream& operator<< (std::stringstream& ss, const ExportInfo& nh);
		//! Write ExportInfo to NIF binary
		friend std::ofstream& operator<< (std::ofstream& outf, const ExportInfo& nh);
		//! Read ExportInfo from NIF binary
		friend std::ifstream& operator>> (std::ifstream& inf, ExportInfo& nh);
	};
}