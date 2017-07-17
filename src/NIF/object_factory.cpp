#include <stdexcept>

#include <NIF/object_factory.hpp>

using namespace std;

namespace NIF
{
	ObjectFactory::Registry& ObjectFactory::GetMap()
	{
		static ObjectFactory::Registry object_map;

		return object_map;
	}

	shared_ptr<Object> ObjectFactory::CreateNIFObject(const string& type_name,
						shared_ptr<Header> header, uint32_t block_id)
	{
		shared_ptr<Object> nif_object = nullptr;
		auto itr = GetMap().find(type_name);

		if(itr != GetMap().end())
		{
			nif_object.reset(itr->second(header, block_id));
		}
		else
		{
			throw runtime_error("Cannot find NIF object: " + type_name);
		}

		return nif_object;
	}
}