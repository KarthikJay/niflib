#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

#include "interfaces/object.hpp"
#include "header.hpp"

namespace NIF
{
	class ObjectFactory
	{
	public:
		typedef std::unordered_map<std::string, std::function<Object*(std::shared_ptr<Header>, uint32_t)>> Registry;
		static std::shared_ptr<Object> CreateNIFObject(const std::string& type_name,
										std::shared_ptr<Header> header, uint32_t block_id);
		static Registry& GetMap();
	};

	template<typename T>
	struct ObjectFactoryRegister
	{
		ObjectFactoryRegister(std::string object_name)
		{
			ObjectFactory::GetMap()[object_name] = [](std::shared_ptr<Header> header, uint32_t block_id)
													{
														return new T(header, block_id);
													};
		}
	};
}