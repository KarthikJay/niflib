#pragma once

#include <string>
#include <iostream>
#include <vector>
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
		Header& GetHeader();
		std::vector<Block>& GetBlockList();
		Block* GetBlock(uint32_t block_id);
		Block* GetBlock(std::string block_name);

		void SetFileName(std::string file_name);

		uint32_t AddBlock(const Block& new_block);
		uint32_t CreateBlock(const std::string& block_type);

		/*
		void AddBlock(std::string block_type);
		void RemoveBlock(uint32_t block_id);
		*/

		NIF_API friend std::ostream& operator<<(std::ostream& out, const File& nif);
		NIF_API friend std::istream& operator>>(std::istream& in, File& nif);
	protected:
		//! Name of NIF without file extension
		std::string file_name;
		//! NIF header
		Header header;
		//! List of all blocks within this NIF
		std::vector<std::unique_ptr<Block>> blocks;
	private:
		void UpdateHeader(const Block& new_block);

		std::istream& ReadBinary(std::istream& nif);
		std::ostream& WriteBinary(std::istream& nif);
	};
}