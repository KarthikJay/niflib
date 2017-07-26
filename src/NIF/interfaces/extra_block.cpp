#include <algorithm>
#include <sstream>
#include <iomanip>

#include <NIF/interfaces/extra_block.hpp>
#include <NIF/utility.hpp>

using namespace std;

namespace NIF
{
	uint32_t ExtraBlock::AddExtraData(const ExtraData& block)
	{
		uint32_t block_index = owner.AddBlock(block);

		extra_block_index.push_back(block_index);

		return block_index;
	}

	void ExtraBlock::LinkExtraData(uint32_t block_index)
	{
		extra_block_index.push_back(block_index);
	}

	void ExtraBlock::UnlinkExtraData(uint32_t block_index)
	{
		auto found = find(extra_block_index.begin(), extra_block_index.end(), block_index);

		if(found != extra_block_index.end())
		{
			extra_block_index.erase(found);
		}
	}

	void ExtraBlock::UnlinkAllExtraData()
	{
		extra_block_index.clear();
	}

	string ExtraBlock::ToString() const
	{
		stringstream ss;
		uint32_t width = 26;
		uint32_t count = 0;

		ss << setw(width) << "Extra Data Block Indices: " << endl;
		for (auto& itr : extra_block_index)
		{
			ss << setw(width) << "[" + to_string(count++) + "]: ";
			ss << itr << endl;
		}

		return ss.str();
	}

	uint32_t ExtraBlock::GetSizeInBytes() const
	{
		return sizeof(uint32_t) * extra_block_index.size();
	}

	ostream& ExtraBlock::WriteBinary(ostream& out) const
	{
		WriteUnsignedIntegral(out, extra_block_index.size());
		for(const auto& itr : extra_block_index)
		{
			WriteUnsignedIntegral(out, itr);
		}

		return out;
	}

	std::istream& ExtraBlock::ReadBinary(std::istream& in)
	{
		uint32_t list_size;

		in.read(reinterpret_cast<char*>(&list_size), sizeof(list_size));
		extra_block_index.resize(list_size);
		for(auto& itr : extra_block_index)
		{
			in.read(reinterpret_cast<char*>(&itr), sizeof(itr));
		}

		return in;
	}
}