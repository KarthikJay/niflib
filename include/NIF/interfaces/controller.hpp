#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	class NIF_API Controller : public virtual Block
	{
	public:
		ToString() const;
	protected:
		std::ostream& WriteBinary(std::ostream& out) const;
		std::istream& ReadBinary(std::istream& in);
	private:
		ControllerBlock* next;
	}
}