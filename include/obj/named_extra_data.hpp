#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "export_info.hpp"
#include "obj/extra_data.hpp"
#include "interfaces/block_name.hpp"
#include "object_factory.hpp"

namespace NIF
{
	//! ExtraData block that contains a uint string name field
	class NIF_API NamedExtraData : public ExtraData, public virtual BlockName
	{
	public:
		NamedExtraData(std::shared_ptr<Header> header, uint32_t block_id);
		std::string str() const;
	protected:
		std::ostream& write(std::ostream& out) const;
		std::istream& read(std::istream& in);
	private:
		static ObjectFactoryRegister<NamedExtraData> registrar;
	};
}