#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	class Controller;

	class NIF_API Controllable : public virtual Block
	{
	public:
		std::string ToString() const override;
		uint32_t GetSizeInBytes() const override;
	protected:
		uint32_t controller_index;

		Controllable() : controller_index(0xFFFFFFFF) {}

		std::istream& ReadBinary(std::istream& in) override;
		std::ostream& WriteBinary(std::ostream& out) const override;
	};
}