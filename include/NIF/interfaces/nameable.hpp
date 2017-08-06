#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	class NIF_API Nameable : public virtual Block
	{
	public:
		std::string GetBlockName() const;
		void SetBlockName(const std::string&);
		std::string ToString() const;
		uint32_t GetSizeInBytes() const;
	protected:
		std::ostream& WriteBinary(std::ostream& out) const;
		std::istream& ReadBinary(std::istream& in);
	private:
		//! Index into #Header::block_names containing the name for this block.
		uint32_t name_index;
		//! \note Used for versions lower than #NIFVersion::V20_1_0_3
		std::string block_name;
	};
}