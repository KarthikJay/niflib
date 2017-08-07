#pragma once

#include <vector>

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	class ExtraData;

	//! Interface for objects that can hold ExtraData blocks
	class NIF_API Extra : public virtual Block
	{
	public:
		void LinkExtraData(uint32_t block_index);
		void UnlinkExtraData(uint32_t block_index);
		void UnlinkAllExtraData();
		/*
		const std::vector<uint32_t>& GetExtraDataIndexList() const;
		void RemoveExtraData(uint32_t block_index)
		void RemoveAllExtraData()
		*/
		std::string ToString() const override;
		uint32_t GetSizeInBytes() const override;
	protected:
		std::ostream& WriteBinary(std::ostream& out) const override;
		std::istream& ReadBinary(std::istream& in) override;
	private:
		//! List of all ExtraData type block indices owned by this block.
		std::vector<uint32_t> extra_block_index;
	};
}