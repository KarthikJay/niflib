#include <algorithm>

#include "interfaces/block_name.hpp"
#include "nif_enum.hpp"
#include "nif_utility.hpp"

using namespace std;

namespace NIF
{
	string BlockName::GetBlockName() const
	{
		return header->block_names[name_id];
	}

	void BlockName::SetBlockName(const string& name)
	{
		uint32_t length = name.length();
		auto itr = find(header->block_names.begin(), header->block_names.end(), name);

		if(itr == header->block_names.end())
		{
			header->max_name_length	= (header->max_name_length > length)
								? header->max_name_length : length;
			name_id = header->block_names.size();
			header->block_names.push_back(name);
		}
		else
		{
			name_id = itr - header->block_names.begin();
		}
	}

	ostream& BlockName::write(ostream& out) const
	{
		bool use_old = header->version < ToIntegral(NIFVersion::V20_1_0_3);

		if(use_old)
		{
			WriteIntString(out, block_name);
		}
		else
		{
			WriteUnsignedIntegral(out, name_id);
		}

		return out;
	}

	istream& BlockName::read(istream& in)
	{
		bool use_old = header->version < ToIntegral(NIFVersion::V20_1_0_3);

		if(use_old)
		{
			ReadIntString(in);
		}
		else
		{
			in.read(reinterpret_cast<char*>(&name_id), sizeof(name_id));
		}

		return in;
	}
}