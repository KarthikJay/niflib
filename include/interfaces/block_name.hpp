#pragma once

#include <string>

#include "interfaces/object.hpp"
#include "export_info.hpp"

namespace NIF
{
	class NIF_API BlockName : public virtual Object
	{
	public:
		std::string GetBlockName() const;
		void SetBlockName(const std::string&);
	protected:
		//! Index into #Header::block_names containing the name for this block.
		uint32_t name_id;
		//! \note Used for versions lower than #NIFVersion::V20_1_0_3
		std::string block_name;

		std::ostream& write(std::ostream& out) const;
		std::istream& read(std::istream& in);
	};
}