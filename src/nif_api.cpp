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
	// ---Internal Helper functions---
	uint32_t ParseVersionString(string version_string)
	{
		uint32_t version = 0, num, offset = 24;
		string::size_type start = 0, end, len;
		string_view ver(version_string.data(), kMaxVersionStringLength);

		do
		{
			end = ver.find_first_of(".", start);
			len = end - start;
			//! \todo: Use from_chars when available
			num = atoi(ver.substr(start, len).data());
			version |= num << offset;
			offset -= 8;
			start += len + 1;
		}
		while(end != string::npos && offset >= 0);

		return version;
	}

	std::string FormatVersionString(uint32_t version)
	{
		uint8_t* byte_version = reinterpret_cast<uint8_t*>(&version);
		uint32_t version_arr[4] = { byte_version[3], byte_version[2], byte_version[1], byte_version[0] };
		stringstream out;

		if(version >= NIFVersion::V3_3_0_13)
		{
			out << version_arr[0] << "." << version_arr[1] << "." << version_arr[2] << "." << version_arr[3];
		}
		else
		{
			out << version_arr[0] << "." << version_arr[1];
			if(version_arr[2])
			{
				out << version_arr[2];
			}
			if(version_arr[3])
			{
				out << version_arr[3];
			}
		}

		return out.str();
	}

	void SetNifVersion(ofstream& outf, NIFVersion version)
	{
		stringstream header_line;

		if(version <= NIFVersion::V10_0_1_0)
		{
			header_line << "NetImmerse File Format, Version ";
		}
		else
		{
			header_line << "Gamebryo File Format, Version ";
		}
		header_line << FormatVersionString(ToIntegral(version));
		WriteLine(outf, header_line.str());
	}

	// ---External API functions---
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
		uint32_t version = GetNifVersion(file_name);
		NIFHeader header(version);
		ifstream input(file_name, ifstream::binary);

		input >> header;

		return header;
	}
}