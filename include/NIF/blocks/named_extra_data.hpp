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
		std::string ToString() const override;
		std::string GetBlockTypeName() const override;
		uint32_t GetSizeInBytes() const override;

		friend BlockFactoryRegistrar<NamedExtraData>;
	protected:
		NamedExtraData(File& file) : Block(file), ExtraData(file) {};
		NamedExtraData(const NamedExtraData& copy) = delete;
		NamedExtraData& operator=(const NamedExtraData& copy) { return *this; }

		std::ostream& WriteBinary(std::ostream& out) const override;
		std::istream& ReadBinary(std::istream& in) override;
	private:
		static BlockFactoryRegistrar<NamedExtraData> registrar;
	};
}