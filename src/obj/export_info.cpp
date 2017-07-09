#include <iomanip>
#include <sstream>

#include "nif_utility.hpp"
#include "obj/export_info.hpp"

using namespace std;

namespace NIF
{
	ExportInfo::ExportInfo()
	{
		unknown = 3;
		use_extra = false;
	}

	istream& operator>>(istream& in, ExportInfo& obj)
	{
		uint32_t num_info = obj.use_extra ? obj.info.max_size() : obj.kOldInfoSize;

		obj.creator = ReadByteString(in);
		for(uint32_t i = 0; i < num_info; ++i)
		{
			obj.info[i] = ReadByteString(in);
		}

		return in;
	}

	ostream& operator<<(ostream& out, const ExportInfo& obj)
	{
		uint32_t num_info = obj.use_extra ? obj.info.max_size() : obj.kOldInfoSize;

		WriteByteString(out, obj.creator);
		for(uint32_t i = 0; i < num_info; ++i)
		{
			WriteByteString(out, obj.info[i]);
		}

		return out;
	}

	string ExportInfo::str()
	{
		stringstream ss;
		uint32_t width = 17;
		uint32_t num_info = use_extra ? info.max_size() : kOldInfoSize;

		ss << setw(width) << "Creator: " << creator << endl;
		for(uint32_t i = 0; i < num_info; ++i)
		{
			ss << setw(width) << "Export Info [" + to_string(i + 1) + "]: " << info[i] << endl;
		}

		return ss.str();
	}
}