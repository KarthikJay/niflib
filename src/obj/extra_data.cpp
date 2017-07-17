#include "obj/extra_data.hpp"

using namespace std;

namespace NIF
{
	ExtraData::ExtraData(std::shared_ptr<Header> header, uint32_t block_id)
	: Object(header, block_id) {}

	string ExtraData::str() const
	{
		return "Block #: " + block_index;
	}

	ostream& ExtraData::write(ostream& out) const
	{
		return out;
	}

	istream& ExtraData::read(istream& in)
	{
		return in;
	}

	ObjectFactoryRegister<ExtraData> ExtraData::registrar("ExtraData");
}