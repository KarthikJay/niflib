#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>
#include <NIF/block_factory.hpp>

namespace NIF
{
	//! Extra Data block that contains no information
	class NIF_API ExtraData : public virtual Block
	{
	public:
		virtual ~ExtraData() {}

		std::string ToString() const override;
		std::string GetBlockTypeName() const override;
		uint32_t GetSizeInBytes() const override;

		friend BlockFactoryRegistrar<ExtraData>;
	protected:
		ExtraData(File &owner) : Block(owner) {}
		// ExtraData(const ExtraData& copy) : Block(copy.owner) {}
		// ExtraData& operator=(const ExtraData& copy) { return *this; }

		void ReadBinary(std::istream& in) override;
		void WriteBinary(std::ostream& out) const override;
		void RemoveBlockLink(uint32_t block_index) override;
	private:
		static BlockFactoryRegistrar<ExtraData> registrar;
	};
}