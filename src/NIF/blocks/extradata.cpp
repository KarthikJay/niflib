#include <sstream>
#include <iomanip>

#include <NIF/blocks/extradata.hpp>

using namespace std;

namespace NIF
{
	const uint32_t kFormatWidth = 19;

	string ExtraData::ToString() const
	{
		stringstream ss;
		ss << setw(kFormatWidth) << "[BSExtraData Block]" << endl;

		return ss.str();
	}

	string ExtraData::GetBlockTypeName() const
	{
		return "BSExtraData";
	}

	uint32_t ExtraData::GetSizeInBytes() const
	{
		return 0;
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