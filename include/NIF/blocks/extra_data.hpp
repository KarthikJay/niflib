#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <NIF/interfaces/object.hpp>
#include <NIF/export_visibility.hpp>
#include <NIF/object_factory.hpp>

namespace NIF
{
	//! Unnamed ExtraData block
	class NIF_API ExtraData : public virtual Object
	{
	public:
		ExtraData(std::shared_ptr<Header> header, uint32_t block_id);
		std::string str() const;
	protected:
		std::ostream& write(std::ostream& out) const;
		std::istream& read(std::istream& in);
	private:
		static ObjectFactoryRegister<ExtraData> registrar;
	};
}