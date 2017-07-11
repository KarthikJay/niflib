#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

#include "nif_object.hpp"

namespace NIF
{
	class NIFObjectFactory
	{
	public:
		static void RegisterNIFObject(std::string type_name, std::function<NIFObject*()>create);
		static std::shared_ptr<NIFObject> CreateNIFObject(const std::string& type_name);
	protected:
		static std::unordered_map<std::string, std::function<NIFObject*()>> type_map;
	};

	template<typename T> struct NIFObjectFactoryRegister
	{
		NIFObjectFactoryRegister(std::string type_name)
		{
			NIFObjectFactory::RegisterNIFObject(type_name, []() { return new T; });
		}
	};
}