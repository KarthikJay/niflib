#include <NIF/interfaces/block.hpp>
#include <NIF/file.hpp>

using namespace std;

namespace NIF
{
	std::vector<std::unique_ptr<Block>>& Block::ModifyBlocks()
	{
		return owner.blocks;
	}

	std::vector<std::string>& Block::GetBlockNames() const
	{
		return owner.header.block_names;
	}
}