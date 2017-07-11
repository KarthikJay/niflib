#include "nif_object_factory.hpp"

using namespace std;

namespace NIF
{
	unordered_map<string, function<NIFObject*()>> NIFObjectFactory::type_map;

	void NIFObjectFactory::RegisterNIFObject(string type_name, function<NIFObject*()>create)
	{
		type_map[type_name] = create;
	}

	shared_ptr<NIFObject> NIFObjectFactory::CreateNIFObject(const string& type_name)
	{
		shared_ptr<NIFObject> nif_object = nullptr;
		auto itr = type_map.find(type_name);

		if(itr != type_map.end())
		{
			nif_object.reset(itr->second());
		}

		return nif_object;
	}
}