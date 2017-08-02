#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <NIF/export_visibility.hpp>

namespace NIF
{
	class File;
	class Header;

	//! Abstract NIF Block class
	//! This class and all derived classes can only be created by #BlockFactory
	class NIF_API Block
	{
	public:
		virtual ~Block() {}

		virtual std::string ToString() const = 0;
		virtual std::string GetBlockTypeName() const = 0;
		virtual uint32_t GetSizeInBytes() const = 0;
	
		NIF_API friend std::ostream& operator<<(std::ostream& out, const Block& nib)
		{
			return nib.WriteBinary(out);
		}
		NIF_API friend std::istream& operator>>(std::istream& in, Block& nib)
		{
			return nib.ReadBinary(in);
		}
	protected:
		File& owner;

		Block(File& file) : owner(file) {}
		Block(const Block& copy) = delete;
		Block& operator=(const Block& copy) { return *this; }

		Block& GetBlock(uint32_t block_index);
		Header& GetHeader();

		virtual std::ostream& WriteBinary(std::ostream& out) const = 0;
		virtual std::istream& ReadBinary(std::istream& in) = 0;
	};
}