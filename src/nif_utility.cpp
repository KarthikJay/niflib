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
}