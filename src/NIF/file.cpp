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

	void File::SetFileName(string& new_name)
	{
		uint32_t num_extension = 0;
		auto end_folder = new_name.find_last_of("/\\");

		end_folder = (end_folder == string::npos) ? 0 : end_folder;
		for(auto rit = new_name.rbegin(); rit != new_name.rbegin() + 4; ++rit)
		{
			num_extension = (*rit == '.') ? num_extension + 1 : num_extension;
		}
		file_name = new_name.substr(end_folder, new_name.length() - num_extension);
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
		header.block_sizes.push_back(new_block.GetSizeInBytes());
	}
}