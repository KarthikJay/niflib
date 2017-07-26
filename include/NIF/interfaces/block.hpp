#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <NIF/file.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	//! Abstract NIF Block class
	class NIF_API Block
	{
	public:
		Block(File& file) : owner(file) {}
		virtual ~Block() {}

		virtual std::string ToString() const = 0;
		virtual std::string GetBlockTypeName() const = 0;
		virtual uint32_t GetSizeInBytes() const = 0;
		virtual Block* Clone() const = 0;
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

		virtual std::ostream& WriteBinary(std::ostream& out) const = 0;
		virtual std::istream& ReadBinary(std::istream& in) = 0;
	};
}