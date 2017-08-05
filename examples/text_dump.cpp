#include <iostream>
#include <sstream>
#include <string>

#include <NIF/file.hpp>
#include <NIF/block_factory.hpp>

using namespace std;
using namespace NIF;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cerr << "Usage: " << argv[0] << " filepath" << endl;
		return EXIT_FAILURE;
	}

	File file(argv[1]);
	cout << file.ToString();

	return EXIT_SUCCESS;
}