#include <NIF/interfaces/block.hpp>
#include <NIF/file.hpp>

using namespace std;

namespace NIF
{
	Block::Block(File& file) : owner(file), header(file.header), blocks(file.blocks)
	{

	}

	Block& Block::operator=(const Block& copy)
	{
		return *this;
	}

	std::istream& operator>>(std::istream& in, Block& nib)
	{
		nib.ReadBinary(in);

		return in;
	}

	ostream& operator<<(std::ostream& out, const Block& nib)
	{
		nib.WriteBinary(out);

		return out;
	}
}