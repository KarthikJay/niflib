#pragma once

#include <vector>

#include <NIF/interfaces/block.hpp>
#include <NIF/blocks/extra_data.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	//! Interface for objects that can hold ExtraData blocks
	class NIF_API ExtraBlock : public virtual Block
	{
	public:
		uint32_t AddExtraData(const ExtraData& block);
		void LinkExtraData(uint32_t block_index);
		void UnlinkExtraData(uint32_t block_index);
		void UnlinkAllExtraData();
		/*
		const std::vector<uint32_t>& GetExtraDataIndexList() const;
		void RemoveExtraData(uint32_t block_index)
		void RemoveAllExtraData()
		*/
		std::string ToString() const;
	protected:
		std::ostream& WriteBinary(std::ostream& out) const;
		std::istream& ReadBinary(std::istream& in);
	private:
		//! List of all ExtraData type block indices owned by this block.
		std::vector<uint32_t> extra_block_index;
	};
}