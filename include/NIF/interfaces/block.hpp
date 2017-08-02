#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include <NIF/export_visibility.hpp>

namespace NIF
{
	class File;

	//! Abstract NIF Block class, contains common functions across all block types
	class NIF_API Block
	{
	public:
		Block(const Block& copy) = delete;
		virtual ~Block() {}

		virtual std::string ToString() const = 0;
		virtual std::string GetBlockTypeName() const = 0;
		virtual uint32_t GetSizeInBytes() const = 0;

		NIF_API friend std::istream& operator>>(std::istream& in, Block& nib)
		{
			nib.ReadBinary(in);

			return in;
		}

		NIF_API friend std::ostream& operator<<(std::ostream& out, const Block& nib)
		{
			nib.WriteBinary(out);

			return out;
		}
	protected:
		File& owner;

		Block(File& new_owner) : owner(new_owner) {}

		std::vector<std::unique_ptr<Block>>& ModifyBlocks();
		std::vector<std::string>& GetBlockNames() const;

		virtual void ReadBinary(std::istream& in) = 0;
		virtual void WriteBinary(std::ostream& out) const = 0;
		virtual void RemoveBlockLink(uint32_t block_index) = 0;
	};
}