#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/blocks/extradata.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	//! Interface for objects that can hold ExtraData blocks
	class NIF_API ExtraBlock : public virtual Block
	{
	public:
		void LinkExtraData(uint32_t block_index);
		void UnlinkExtraData(uint32_t block_index);
		void UnlinkAllExtraData();

		std::string ToString() const override;
		uint32_t GetSizeInBytes() const override;
	protected:
		void WriteBinary(std::ostream& out) const override;
		void ReadBinary(std::istream& in) override;
		void RemoveBlockLink(uint32_t block_index) override;
	private:
		//! List of all ExtraData type block indices owned by this block.
		std::vector<uint32_t> extra_block_index;
	};
}