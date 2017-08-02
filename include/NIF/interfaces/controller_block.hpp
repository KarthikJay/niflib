#pragma once

#include <string>

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	class NIF_API ControllerBlock : public virtual Block
	{
	public:
		void GetNextController() const;
		void SetNextController();
		std::string ToString() const;
		uint32_t GetSizeInBytes() const;
	protected:
		void WriteBinary(std::ostream& out) const override;
		void ReadBinary(std::istream& in) override;
	private:
		ControllerBlock* next;
	};
}