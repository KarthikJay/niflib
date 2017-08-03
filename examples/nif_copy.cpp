#include <iostream>
#include <fstream>
#include <string>

#include <NIF/file.hpp>

using namespace std;
using namespace NIF;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cerr << "Usage: " << argv[0] << " <input filepath> <output filepath>" << endl;
		return EXIT_FAILURE;
	}

	File input(argv[1]);
	File copy(input);

	return EXIT_SUCCESS;
}