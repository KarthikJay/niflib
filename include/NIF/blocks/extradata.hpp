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
		virtual ~ExtraData() {}

		std::string ToString() const override;
		std::string GetBlockTypeName() const override;
		uint32_t GetSizeInBytes() const override;

		friend BlockRegistrar<ExtraData>;
	protected:
		ExtraData(File& file) : Block(file) {}
		ExtraData(const ExtraData& copy) = delete;
		ExtraData& operator=(const ExtraData& copy) { return *this; }

		std::ostream& WriteBinary(std::ostream& out) const override;
		std::istream& ReadBinary(std::istream& in) override;
	};
}