#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	class NIF_API Controller : public virtual Block
	{
	public:
		ToString() const override;
		GetSizeInBytes() const override;
	protected:
		//! Block index of next #Controller
		uint32_t next_controller;
		uint16_t flags;
		float frequency;
		float phase;
		float time_start;
		float time_end;
		//! Block index of target object
		uint32_t target;

		std::ostream& WriteBinary(std::ostream& out) const;
		std::istream& ReadBinary(std::istream& in);
	}
}