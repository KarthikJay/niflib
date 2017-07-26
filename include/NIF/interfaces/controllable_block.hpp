#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	class NIF_API ControllableBlock : public virtual Block
	{
	public:
		GetControllerBlock();
	protected:
		uint32_t controller_index;

		std::ostream& WriteBinary(std::ostream& out) const;
		std::istream& ReadBinary(std::istream& in);
	}
}