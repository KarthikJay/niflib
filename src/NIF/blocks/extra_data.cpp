#include <NIF/blocks/extra_data.hpp>

using namespace std;

namespace NIF
{
	string ExtraData::ToString() const
	{
		return "BSExtraData Block";
	}

	string ExtraData::GetBlockTypeName() const
	{
		return "BSExtraData";
	}

	uint32_t ExtraData::GetSizeInBytes() const
	{
		return 0;
	}

	ExtraData* ExtraData::Clone() const
	{
		return new ExtraData(*this);
	}

	ostream& ExtraData::WriteBinary(ostream& out) const
	{
		return out;
	}

	istream& ExtraData::ReadBinary(istream& in)
	{
		return in;
	}

	BlockFactoryRegistrar<ExtraData> ExtraData::registrar("BSExtraData");
}