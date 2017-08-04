#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

namespace NIF
{
	class File;
	class Block;

	class NIF_API BlockFactory
	{
	public:
		BlockFactory(const BlockFactory& other) = delete;
		BlockFactory& operator=(const BlockFactory& other) = delete;

		typedef std::unordered_map<std::string, std::function<Block*(File& owner)>> BlockRegistry;

		static BlockFactory& Instance();
		std::unique_ptr<Block> CreateBlock(const std::string& type_name, File& owner);
		void RegisterBlock(const std::string& type_name,
			std::function<Block*(File& owner)> create);
		void PrintSupportedBlocks();
	private:
		BlockRegistry block_types;

		BlockFactory() {};
	};

	template<typename T>
	struct BlockRegistrar
	{
		BlockRegistrar(const std::string& block_type)
		{
			BlockFactory::Instance().RegisterBlock(block_type, [](File& owner)
				{
					return new T(owner);
				});
		}
	};
}