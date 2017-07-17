#include <NIF/blocks/named_extra_data.hpp>
#include <NIF/enums.hpp>

using namespace std;

namespace NIF
{
	NamedExtraData::NamedExtraData(std::shared_ptr<Header> header, uint32_t block_id)
	: Object(header, block_id), ExtraData(header, block_id) {}

	string NamedExtraData::str() const
	{
		return "Block #: " + block_index;
	}

	ostream& NamedExtraData::write(ostream& out) const
	{
		if(header->version >= NIFVersion::V10_1_0_0)
		{
			BlockName::write(out);
		}

		return out;
	}

	istream& NamedExtraData::read(istream& in)
	{
		if(header->version >= NIFVersion::V10_1_0_0)
		{
			BlockName::read(in);
		}

		return in;
	}

	ObjectFactoryRegister<NamedExtraData> NamedExtraData::registrar("NiExtraData");
}