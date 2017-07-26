#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <NIF/interfaces/named_block.hpp>
#include <NIF/blocks/extra_data.hpp>

namespace NIF
{
	//! ExtraData block that contains a uint32_t string name field
	class NIF_API NamedExtraData : public ExtraData, public virtual NamedBlock
	{
	public:
		NamedExtraData(File& owner);
		std::string ToString() const;
		std::string GetBlockTypeName() const;
		uint32_t GetSizeInBytes() const;
		NamedExtraData* Clone() const;
	protected:
		std::ostream& WriteBinary(std::ostream& out) const;
		std::istream& ReadBinary(std::istream& in);
	private:
		static BlockFactoryRegistrar<NamedExtraData> registrar;
	};
}