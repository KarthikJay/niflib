#include <algorithm>
#include <iterator>
#include <fstream>

#include <NIF/file.hpp>
#include <NIF/block_factory.hpp>
#include <NIF/interfaces/block.hpp>

using namespace std;

namespace NIF
{
	File::File(string& file_path)
	{
		SetFileName(file_path);
		ifstream input(file_path, ifstream::binary);


	}

	string File::GetFileName() const
	{
		return file_name;
	}

	void File::SetFileName(string& new_name)
	{
		size_t extension = new_name.find_last_of(".");
		size_t folder = new_name.find_last_of("/\\");

		extension = (new_name.length() - extension <= 3) ? extension : string::npos;
		folder = (folder == string::npos) ? 0 : folder;

		file_name = new_name.substr(folder, extension);
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

	uint32_t File::CreateBlock(const string& block_type)
	{
		uint32_t block_index = blocks.size();

		blocks.emplace_back(BlockFactory::CreateNIFBlock(block_type, *this));

		return block_index;
	}

	istream& operator>>(istream& in, File& nif)
	{
		nif.ReadBinary(in);

		return in;
	}

	ostream& operator<<(ostream& out, const File& nif)
	{
		nif.WriteBinary(out);

		return out;
	}
}