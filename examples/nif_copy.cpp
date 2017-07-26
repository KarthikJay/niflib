#include <iostream>
#include <fstream>
#include <string>

#include <NIF/api.hpp>
#include <NIF/header.hpp>

using namespace std;
using namespace NIF;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cerr << "Usage: " << argv[0] << " <input filepath> <output filepath>" << endl;
		return EXIT_FAILURE;
	}

	ofstream output(argv[2], ofstream::binary);
	Header header = ReadHeaderInfo(argv[1]);
	output << header;
	output.close();

	return EXIT_SUCCESS;
}