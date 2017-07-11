#pragma once

#include <string>
#include <iostream>

#include "export_info.hpp"

namespace NIF
{
	//! Abstract NIF Object type
	class NIF_API NIFObject
	{
	public:
		virtual ~NIFObject(){};
		virtual std::string str() const = 0;
		NIF_API friend std::ostream& operator<<(std::ostream& out, const NIFObject& nio)
		{
			nio.write(out);
			return out;
		}
		NIF_API friend std::istream& operator>>(std::istream& in, NIFObject& nio)
		{
			nio.read(in);
			return in;
		}
	private:
		virtual void write(std::ostream& out) const = 0;
		virtual void read(std::istream& in) const = 0;
	};
}