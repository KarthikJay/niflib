#include <algorithm>

#include <NIF/file.hpp>
#include <NIF/interfaces/block.hpp>

using namespace std;

namespace NIF
{
	std::string File::GetFileName() const
	{
		return file_name;
	}

	Header& File::GetHeader()
	{
		return header;
	}

	uint32_t File::AddBlock(const Block& new_block)
	{
		blocks.emplace_back(new_block.Clone());
		
		return blocks.size() - 1;
	}

	void File::UpdateHeader(const Block& new_block)
	{
		auto name_found = find(	header.block_type_names.begin(),
								header.block_type_names.end(),
								new_block.GetBlockTypeName());
		if(name_found != header.block_type_names.end())
		{
			header.block_type_names.push_back(new_block.GetBlockTypeName());
		}
	}
}