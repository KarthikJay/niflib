#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <NIF/blocks/header.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	//! Abstract NIF Object class
	class NIF_API Object
	{
	public:
		Object(std::shared_ptr<Header> header, uint32_t block_index)
		{
			this->header = header;
			this->block_index = block_index;
		}
		virtual ~Object() {};
		virtual std::string str() const = 0;
		NIF_API friend std::ostream& operator<<(std::ostream& out, const Object& nio)
		{
			return nio.write(out);
		}
		NIF_API friend std::istream& operator>>(std::istream& in, Object& nio)
		{
			return nio.read(in);
		}
	protected:
		uint32_t block_index;
		std::shared_ptr<Header> header;

		virtual std::ostream& write(std::ostream& out) const = 0;
		virtual std::istream& read(std::istream& in) = 0;
	};
}