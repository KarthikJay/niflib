#include <sstream>

#include <NIF/interfaces/controllable.hpp>
#include <NIF/file.hpp>
#include <NIF/enums.hpp>
#include <NIF/utility.hpp>

using namespace std;

namespace NIF
{
	string Controllable::ToString() const
	{
		stringstream ss;

		return ss.str();
	}

	uint32_t Controllable::GetSizeInBytes() const
	{
		return sizeof(controller_index);
	}

	istream& Controllable::ReadBinary(istream& in)
	{
		bool version_check = header.version >= Version(3,3,0,13);
		if(version_check)
		{
			in.read(reinterpret_cast<char*>(&controller_index), sizeof(controller_index));
		}

		return in;
	}

	ostream& Controllable::WriteBinary(ostream& out) const
	{
		bool version_check = header.version >= Version(3,3,0,13);
		if(version_check)
		{
			WriteUnsignedIntegral(out, controller_index);
		}
		
		return out;
	}
}