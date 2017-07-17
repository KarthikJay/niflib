#include <iostream>
#include <sstream>
#include <string>

#include "nif_api.hpp"

using namespace std;
using namespace NIF;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cerr << "Usage: " << argv[0] << " filepath" << endl;
		return EXIT_FAILURE;
	}

	Header header = ReadHeaderInfo(argv[1]);
	cout << header.str();

	return EXIT_SUCCESS;
}