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

	void ExtraData::WriteBinary(ostream& out) const
	{

	}

	void ExtraData::ReadBinary(istream& in)
	{

	}

	void ExtraData::RemoveBlockLink(uint32_t block_index)
	{

	}

	BlockFactoryRegistrar<ExtraData> ExtraData::registrar("BSExtraData");
}