#include <algorithm>
#include <sstream>
#include <iomanip>

#include <NIF/interfaces/named_block.hpp>
#include <NIF/enums.hpp>
#include <NIF/utility.hpp>
#include <NIF/file.hpp>

using namespace std;

namespace NIF
{
	string NamedBlock::GetBlockName() const
	{
		string name;
		bool use_old = owner.GetVersion() < NIFVersion::V20_1_0_3;
		name = use_old ? block_name : header.block_names[name_index];

		return name;
	}

	void NamedBlock::SetBlockName(const string& name)
	{
		uint32_t length = name.length();
		auto found = find(header.block_names.begin(), header.block_names.end(), name);

		block_name = name;
		if(found != header.block_names.end())
		{
			header.max_name_length	= (header.max_name_length > length)
								? header.max_name_length : length;
			name_index = header.block_names.size();
			header.block_names.push_back(name);
		}
		else
		{
			name_index = found - header.block_names.begin();
		}
	}

	string NamedBlock::ToString() const
	{
		stringstream ss;

		ss	<< setw(kMemberTypeWidth) << "Block Name: "
			<< setw(header.max_name_length) << block_name
			<< setw(kIndexWidth) << "[" + to_string(name_index) + "]" << endl;

		return ss.str();
	}

	uint32_t NamedBlock::GetSizeInBytes() const
	{
		bool use_old = owner.GetVersion() < NIFVersion::V20_1_0_3;
		uint32_t num_size = use_old ? block_name.length() : sizeof(name_index);

		return num_size;
	}

	ostream& NamedBlock::WriteBinary(ostream& out) const
	{
		bool use_old = owner.GetVersion() < NIFVersion::V20_1_0_3;

		if(use_old)
		{
			WriteIntString(out, block_name);
		}
		else
		{
			WriteUnsignedIntegral(out, name_index);
		}

		return out;
	}

	istream& NamedBlock::ReadBinary(istream& in)
	{
		bool use_old = owner.GetVersion() < NIFVersion::V20_1_0_3;

		if(use_old)
		{
			block_name = ReadIntString(in);
		}
		else
		{
			in.read(reinterpret_cast<char*>(&name_index), sizeof(name_index));
			block_name = header.block_names[name_index];
		}

		return in;
	}
}