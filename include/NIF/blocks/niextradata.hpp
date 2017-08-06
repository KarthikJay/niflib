#pragma once

#include <NIF/interfaces/nameable.hpp>
#include <NIF/blocks/extradata.hpp>

namespace NIF
{
	//! ExtraData block that contains a uint32_t string name field
	class NIF_API NiExtraData : public ExtraData, public virtual Nameable
	{
	public:
		std::string ToString() const override;
		std::string GetBlockTypeName() const override;
		uint32_t GetSizeInBytes() const override;

		friend BlockRegistrar<NiExtraData>;
	protected:
		NiExtraData(File& file) : Block(file), ExtraData(file) {};
		NiExtraData(const NiExtraData& copy) = delete;
		NiExtraData& operator=(const NiExtraData& copy) { return *this; }

		std::ostream& WriteBinary(std::ostream& out) const override;
		std::istream& ReadBinary(std::istream& in) override;
	};
}