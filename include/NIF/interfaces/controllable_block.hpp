#pragma once

#include <stdint.h>

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>
#include <NIF/interfaces/controller_block.hpp>

namespace NIF
{
	class NIF_API ControllableBlock : public virtual Block
	{
	public:
		ControllableBlock() : controller_index(UINT32_MAX) {}
		virtual ~ControllableBlock();

		uint32_t GetControllerBlockIndex() const;
		ControllerBlock* GetControllerBlock();
		void SetControllerBlock(const ControllerBlock& block);
		std::string ToString() const override;
		uint32_t GetSizeInBytes() const override;
	protected:
		uint32_t controller_index;

		void WriteBinary(std::ostream& out) const override;
		void ReadBinary(std::istream& in) override;
	};
}