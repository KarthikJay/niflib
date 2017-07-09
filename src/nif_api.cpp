#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <string_view>

#include "nif_api.hpp"
#include "nif_enum.hpp"
#include "nif_utility.hpp"

using namespace std;

namespace NIF
{
	// ---API functions---
	uint32_t GetNifVersion(const string& file_name)
	{
		std::string header_line;
		uint32_t ver_str_offset = 0;
		ifstream input(file_name, ifstream::binary);

		//! \todo: Refactor checks into new function & increase performance
		header_line = ReadLine(input);
		if(header_line.substr(0,22) == "NetImmerse File Format")
		{
			ver_str_offset = 32;
		}
		else if(header_line.substr(0, 20) == "Gamebryo File Format" ||
				header_line.substr(0, 6) == "NDSNIF")
		{
			ver_str_offset = 30;
		}
		else
		{
			throw runtime_error("Not a valid NIF");
		}
		input.close();

		return ParseVersionString(header_line.substr(ver_str_offset));
	}

	NIFHeader ReadHeaderInfo(const std::string &file_name)
	{
		NIFHeader header;
		ifstream input(file_name, ifstream::binary);

		input >> header;
		input.close();

		return header;
	}
}