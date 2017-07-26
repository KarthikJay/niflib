#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>
#include <NIF/block_factory.hpp>

namespace NIF
{
	//! ExtraData block
	class NIF_API ExtraData : public virtual Block
	{
	public:
		ExtraData(File& file) : Block(file) {}
		virtual ~ExtraData() {}

		std::string ToString() const;
		std::string GetBlockTypeName() const;
		uint32_t GetSizeInBytes() const;
		ExtraData* Clone() const;
	protected:
		std::ostream& WriteBinary(std::ostream& out) const;
		std::istream& ReadBinary(std::istream& in);
	private:
		static BlockFactoryRegistrar<ExtraData> registrar;
	};
}