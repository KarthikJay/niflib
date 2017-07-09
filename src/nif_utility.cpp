#include <cstring>

#include "nif_utility.hpp"

using namespace std;

namespace NIF
{
	//! ---NIF read utility function implementations---
	string ReadLine(istream& in)
	{
		char buffer[kLineBufferSize] = {};
		in.getline(buffer, kLineBufferSize);

		return string(buffer);
	}

	string ReadByteString(istream &in)
	{
		uint8_t length;
		in.read(reinterpret_cast<char*>(&length), sizeof(length));
		string buffer(length + 1, '\0');
		in.read(&buffer[0], length);

		return buffer;
	}

	string ReadIntString(istream& in)
	{
		uint32_t length;
		in.read(reinterpret_cast<char*>(&length), sizeof(length));
		string buffer(length + 1, '\0');
		in.read(&buffer[0], length);

		return buffer;
	}

	//! ---NIF write utility function implementations---
	void WriteLine(ostream& out, const string& line)
	{
		out.write(line.data(), line.length());
		out.put('\n');
	}

	void WriteByteString(ostream& out, const string& line)
	{
		uint8_t length = line.length() + 1;

		out.write(reinterpret_cast<char*>(length), sizeof(length));
		out.write(line.data(), line.length());
		out.put('\0');
	}

	void WriteIntString(ostream& out, const string& line)
	{
		uint32_t length = line.length() + 1;

		out.write(reinterpret_cast<char*>(length), sizeof(length));
		out.write(line.data(), line.length());
		out.put('\0');
	}

	//! --- NIF general utility function implementations---
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
		while(end != string::npos);

		return version;
	}

	string FormatVersionString(uint32_t version)
	{
		uint8_t* byte_version = reinterpret_cast<uint8_t*>(&version);
		uint32_t version_arr[4] = { byte_version[3], byte_version[2],
									byte_version[1], byte_version[0] };
		string version_string = to_string(version_arr[0]) + "." + to_string(version_arr[1]);

		if(version >= NIFVersion::V3_3_0_13)
		{
			version_string	+= "." + to_string(version_arr[2]) + "." + to_string(version_arr[3]);
		}
		else
		{
			if(version_arr[2])
			{
				version_string += "." + to_string(version_arr[2]);
			}
			if(version_arr[3])
			{
				version_string += "." + to_string(version_arr[3]);
			}
		}

		return version_string;
	}

	string GetNifHeaderLine(NIFVersion version)
	{
		string header_line;

		header_line.reserve(45);
		if(version <= NIFVersion::V10_0_1_0)
		{
			header_line = "NetImmerse File Format, Version ";
		}
		else
		{
			header_line = "Gamebryo File Format, Version ";
		}
		header_line += FormatVersionString(ToIntegral(version));
		
		return header_line;
	}
}