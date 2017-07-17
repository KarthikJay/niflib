#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <NIF/api.hpp>
#include <NIF/blocks/header.hpp>
#include <NIF/enums.hpp>
#include <NIF/utility.hpp>

using namespace std;

namespace NIF
{
	// ---API functions---
	uint32_t GetNifVersion(const string& file_name)
	{
		std::string header_line;
		uint32_t ver_str_offset;
		ifstream input(file_name, ifstream::binary);

		header_line = ReadLine(input);
		input.close();
		ver_str_offset = ValidNIF(header_line);
		header_line = header_line.substr(ver_str_offset);

		return ParseVersionString(header_line);
	}

	Header ReadHeaderInfo(const string &file_name)
	{
		Header header;
		ifstream input(file_name, ifstream::binary);

		input >> header;
		input.close();

		return header;
	}

	vector<shared_ptr<Object>> ReadNIFObjects(const string &file_name)
	{
		Header header;
		vector<shared_ptr<Object>> nif_objects;
		ifstream input(file_name, ifstream::binary);

		input >> header;
		nif_objects.resize(header.num_blocks);

		return nif_objects;
	}
}