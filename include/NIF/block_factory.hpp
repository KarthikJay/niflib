#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

namespace NIF
{
	class File;
	class Block;

	class BlockFactory
	{
	public:
		typedef std::unordered_map<std::string, std::function<Block*(File& owner)>> Registry;
		static std::unique_ptr<Block> CreateNIFBlock(const std::string& type_name, File& owner);
		static Registry& GetBlockTypeMapping();
	};

	template<typename T>
	struct BlockFactoryRegistrar
	{
		BlockFactoryRegistrar(std::string object_name)
		{
			BlockFactory::GetBlockTypeMapping()[object_name] = [](File& owner)
				{
					return new T(owner);
				};
		}
	};
}