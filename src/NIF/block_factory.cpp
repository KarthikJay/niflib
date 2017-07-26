#include <stdexcept>

#include <NIF/block_factory.hpp>
#include <NIF/interfaces/block.hpp>

using namespace std;

namespace NIF
{
	BlockFactory::Registry& BlockFactory::GetBlockTypeMapping()
	{
		static BlockFactory::Registry block_type_map;

		return block_type_map;
	}

	unique_ptr<Block> BlockFactory::CreateNIFBlock(const string& type_name, File& owner)
	{
		unique_ptr<Block> nif_block = nullptr;
		auto itr = GetBlockTypeMapping().find(type_name);

		if(itr == GetBlockTypeMapping().end())
		{
			throw runtime_error("NIF Block: " + type_name + " is not currently supported.");
		}
		nif_block.reset(itr->second(owner));

		return nif_block;
	}
}