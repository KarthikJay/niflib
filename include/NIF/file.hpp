#pragma once

#include <memory>

#include <NIF/export_visibility.hpp>
#include <NIF/header.hpp>

namespace NIF
{
	class Block;

	class NIF_API File
	{
	public:
		File();
		File(std::string filepath);

		std::string GetFileName() const;
		void SetFileName(std::string& file_name);
		constexpr uint32_t GetVersion() { return header.version; }
		constexpr uint32_t GetUserVersion1() { return header.user_version_1; }
		constexpr uint32_t GetUserVersion2() { return header.user_version_2; }
		Header GetHeader() const { return header; }
		Block* GetBlock(uint32_t block_id);
		Block* GetBlock(std::string block_name);

		uint32_t CreateBlock(const std::string& block_type);

		NIF_API friend std::istream& operator>>(std::istream& in, File& nif);
		NIF_API friend std::ostream& operator<<(std::ostream& out, const File& nif);
		friend Block;
	protected:
		//! Name of NIF without file extension
		std::string file_name;
		//! NIF header
		Header header;
		//! List of all blocks within this NIF
		std::vector<std::unique_ptr<Block>> blocks;
	private:
		void UpdateHeader(const Block& new_block);

		void ReadBinary(std::istream& nif);
		void WriteBinary(std::istream& nif);
	};
}