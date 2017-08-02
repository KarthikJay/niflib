#include <sstream>
#include <iomanip>

#include <NIF/interfaces/controllable_block.hpp>
#include <NIF/file.hpp>
#include <NIF/enums.hpp>
#include <NIF/utility.hpp>

using namespace std;

namespace NIF
{
	const uint32_t kFormatWidth = 18;

	string ControllableBlock::ToString() const
	{
		stringstream ss;

		ss << setw(kFormatWidth) << "Controller Block: ";
		if(controller_index == UINT32_MAX)
		{
			ss << "N/A";
		}
		else
		{
			ss << controller_index;
		}
		ss << endl;

		return ss.str();
	}

	uint32_t ControllableBlock::GetSizeInBytes() const
	{
		return sizeof(controller_index);
	}

	uint32_t ControllableBlock::GetControllerBlockIndex() const
	{
		return controller_index;
	}

	ControllerBlock* ControllableBlock::GetControllerBlock()
	{
		return dynamic_cast<ControllerBlock*>(GetBlocks()[controller_index].get());
	}

	void ControllableBlock::WriteBinary(ostream& out) const
	{
		bool version_check = owner.GetVersion() >= NIFVersion::V3_0;
		if(version_check)
		{
			WriteUnsignedIntegral(out, controller_index);
		}
	}

	void ControllableBlock::ReadBinary(istream& in)
	{
		bool version_check = owner.GetVersion() >= NIFVersion::V3_0;
		if(version_check)
		{
			in.read(reinterpret_cast<char*>(&controller_index), sizeof(controller_index));
		}
	}
}