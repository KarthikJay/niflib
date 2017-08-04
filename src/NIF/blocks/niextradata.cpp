#include <sstream>
#include <iomanip>

#include <NIF/blocks/niextradata.hpp>
#include <NIF/enums.hpp>
#include <NIF/file.hpp>

using namespace std;

namespace NIF
{

	static BlockRegistrar<NamedExtraData> registrar("NiExtraData");

	string NamedExtraData::ToString() const
	{
		stringstream ss;
		ss << setw(kBlockTypeWidth) << "[NiExtraData Block]" << endl;
		ss << NamedBlock::ToString();

		return ss.str();
	}

	string NamedExtraData::GetBlockTypeName() const
	{
		return "NiExtraData";
	}

	uint32_t NamedExtraData::GetSizeInBytes() const
	{
		return ExtraData::GetSizeInBytes() + NamedBlock::GetSizeInBytes();
	}

	ostream& NamedExtraData::WriteBinary(ostream& out) const
	{
		auto current_version = owner.GetVersion();
		if(current_version >= NIFVersion::V10_1_0_0)
		{
			NamedBlock::WriteBinary(out);
		}

		return out;
	}

	istream& NamedExtraData::ReadBinary(istream& in)
	{
		auto current_version = owner.GetVersion();
		if(current_version >= NIFVersion::V10_1_0_0)
		{
			NamedBlock::ReadBinary(in);
		}

		return in;
	}
}