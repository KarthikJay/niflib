#include <stdexcept>
#include <iostream>

#include <NIF/export_visibility.hpp>
#include <NIF/block_factory.hpp>
#include <NIF/interfaces/block.hpp>

using namespace std;

namespace NIF
{
	BlockFactory& BlockFactory::Instance()
	{
		static BlockFactory factory;

		return factory;
	}

	unique_ptr<Block> BlockFactory::CreateBlock(const string& type_name, File& owner)
	{
		unique_ptr<Block> nif_block = nullptr;
		auto itr = block_types.find(type_name);

		if(itr == block_types.end())
		{
			throw runtime_error("[NIFLib] Unsupported block type: " + type_name);
		}
		nif_block.reset(itr->second(owner));

		return nif_block;
	}

	void BlockFactory::RegisterBlock(const string& type_name, function<Block*(File& owner)> create)
	{
		//! Check uniqueness
		if(block_types.find(type_name) != block_types.end())
		{
			throw logic_error("[NIFLib] Multiple instances of: " + type_name);
		}
		block_types[type_name] = create;
	}

	void BlockFactory::PrintSupportedBlocks()
	{
		cout << "Supported Block Types:" << endl;
		for(auto const& itr : block_types)
		{
			cout << itr.first << endl;
		}
	}
}