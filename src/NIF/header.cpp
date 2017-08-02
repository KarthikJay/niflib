#include <iomanip>
#include <sstream>

#include <NIF/header.hpp>
#include <NIF/utility.hpp>

using namespace std;

namespace NIF
{
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

	string ExportInfo::ToString()
	{
		stringstream ss;
		uint32_t width = 23;
		uint32_t num_info = use_extra ? info.max_size() : kOldInfoSize;

		ss << setw(width) << "Creator: " << creator << endl;
		for(uint32_t i = 0; i < num_info; ++i)
		{
			ss << setw(width) << "Export Info [" + to_string(i + 1) + "]: " << info[i] << endl;
		}

		return ss.str();
	}

	istream& operator>> (istream& in, Header& obj)
	{
		uint8_t test_byte;
		uint32_t vec_size;

		obj.header_line = ReadLine(in);
		ValidNIF(obj.header_line);

		if(obj.version <= NIFVersion::V3_1)
		{
			for(auto& itr : obj.copyright)
			{
				itr = ReadLine(in);
			}
		}

		if(obj.version >= Version(3,3,0,13))
		{
			in.read(reinterpret_cast<char*>(&obj.version), sizeof(obj.version));
		}

		if(obj.version >= NIFVersion::V20_0_0_4)
		{
			in.read(reinterpret_cast<char*>(&test_byte), sizeof(test_byte));
			obj.endian = static_cast<EndianType>(test_byte);
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			in.read(reinterpret_cast<char*>(&obj.user_version_1), sizeof(obj.user_version_1));
		}

		if(obj.version >= Version(3,3,0,13))
		{
			in.read(reinterpret_cast<char*>(&vec_size), sizeof(vec_size));
			obj.block_sizes.resize(vec_size);
			obj.block_type_index.resize(vec_size);
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			if(obj.user_version_1 >= 10 ||
				((obj.user_version_1 == 1) && obj.version != NIFVersion::V10_2_0_0))
			{
				in.read(reinterpret_cast<char*>(&obj.user_version_2), sizeof(obj.user_version_2));
			}
		}

		if(obj.version >= NIFVersion::V30_0_0_2)
		{
			in.read(reinterpret_cast<char*>(&obj.image_preview_size), sizeof(obj.image_preview_size));
		}

		if(obj.version >= NIFVersion::V10_0_1_0)
		{
			if(obj.version >= NIFVersion::V20_2_0_7 && obj.user_version_2 == 130)
			{
				obj.export_info.use_extra = true;
			}
			in >> obj.export_info;
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			in.read(reinterpret_cast<char*>(&vec_size), sizeof(uint16_t));
			obj.block_type_names.resize(vec_size);
			for(auto& itr : obj.block_type_names)
			{
				itr = ReadIntString(in);
			}
			for(auto& itr : obj.block_type_index)
			{
				in.read(reinterpret_cast<char*>(&itr), sizeof(itr));
			}
		}

		if(obj.version >= NIFVersion::V20_2_0_7)
		{
			for(auto& itr : obj.block_sizes)
			{
				in.read(reinterpret_cast<char*>(&itr), sizeof(itr));
			}
		}

		if(obj.version >= NIFVersion::V20_1_0_3)
		{
			in.read(reinterpret_cast<char*>(&vec_size), sizeof(vec_size));
			in.read(reinterpret_cast<char*>(&obj.max_name_length), sizeof(obj.max_name_length));
			obj.block_names.resize(vec_size);
			for(auto& itr : obj.block_names)
			{
				itr = ReadIntString(in);
			}
		}

		if(obj.version >= Version(5,0,0,6))
		{
			in.read(reinterpret_cast<char*>(&obj.num_groups), sizeof(obj.num_groups));
		}

		return in;
	}

	ostream& operator<<(ostream& out, const Header& obj)
	{
		WriteLine(out, obj.header_line);

		if(obj.version <= NIFVersion::V3_1)
		{
			for(const auto& itr : obj.copyright)
			{
				WriteLine(out, itr);
			}
		}
		
		if(obj.version >= Version(3,3,0,13))
		{
			WriteUnsignedIntegral(out, obj.version);
		}

		if(obj.version >= NIFVersion::V20_0_0_4)
		{
			WriteUnsignedIntegral(out, ToIntegral(obj.endian));
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			WriteUnsignedIntegral(out, obj.user_version_1);
		}

		if(obj.version >= Version(3,3,0,13))
		{
			WriteUnsignedIntegral(out, static_cast<uint32_t>(obj.block_type_index.size()));
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			if(obj.user_version_1 >= 10 ||
				((obj.user_version_1 == 1) && obj.version != NIFVersion::V10_2_0_0))
			{
				WriteUnsignedIntegral(out, obj.user_version_2);
			}
		}

		if(obj.version >= NIFVersion::V30_0_0_2)
		{
			WriteUnsignedIntegral(out, obj.image_preview_size);
		}

		if(obj.version >= NIFVersion::V10_0_1_0)
		{
			out << obj.export_info;
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			WriteUnsignedIntegral(out, static_cast<uint16_t>(obj.block_type_names.size()));
			for(const auto& itr : obj.block_type_names)
			{
				WriteIntString(out, itr);
			}
			for(const auto& itr : obj.block_type_index)
			{
				WriteUnsignedIntegral(out, itr);
			}
		}

		if(obj.version >= NIFVersion::V20_2_0_7)
		{
			for(const auto& itr : obj.block_sizes)
			{
				WriteUnsignedIntegral(out, itr);
			}
		}

		if(obj.version >= NIFVersion::V20_1_0_3)
		{
			WriteUnsignedIntegral(out, static_cast<uint32_t>(obj.block_names.size()));
			WriteUnsignedIntegral(out, obj.max_name_length);
			for(const auto& itr : obj.block_names)
			{
				WriteIntString(out, itr);
			}
		}

		if(obj.version >= Version(5,0,0,6))
		{
			WriteUnsignedIntegral(out, obj.num_groups);
		}

		return out;
	}

	string Header::ToString()
	{
		stringstream ss;
		uint32_t idx = 0;
		uint32_t width = 23;

		ss << header_line << endl;
		if(version <= NIFVersion::V3_1)
		{
			for(uint32_t i = 0; i < copyright.size(); ++i)
			{
				ss	<< setw(width) << "Copyright [" + to_string(i + 1) + "]: "
					<< copyright[i] << endl;
			}
		}
		ss << setw(width) << "Version: " << hex << version << dec << endl;
		ss << setw(width) << "Endian Type: " << endian << endl;
		ss << setw(width) << "User Version 1: " << user_version_1 << endl;
		ss << setw(width) << "Number of blocks: " << block_type_index.size() << endl;
		if(user_version_1 >= 10 ||
				((user_version_1 == 1) && version != NIFVersion::V10_2_0_0))
		{
			ss << setw(width) << "User Version 2: " << user_version_2 << endl;
		}
		if(version >= NIFVersion::V30_0_0_2)
		{
			ss << setw(width) << "Image Preview Size: " << image_preview_size << endl;
		}
		ss << export_info.ToString();
		ss << setw(width) << "Number of Block Types: " << block_type_names.size() << endl;
		for(uint32_t i = 0; i < block_type_names.size(); ++i)
		{
			ss	<< setw(width) << "Block Type Name[" + to_string(i) + "]: "
				<< block_type_names[i] << endl;
		}
		for(uint32_t i = 0; i < block_type_index.size(); ++i)
		{
			ss	<< setw(width) << "Block Index[" + to_string(i) + "]: "
				<< block_type_names[block_type_index[i]] << endl;
		}
		for(uint32_t i = 0; i < block_type_index.size(); ++i)
		{
			ss	<< setw(width) << "Block Size[" + to_string(i) + "]: "
				<< block_sizes[i] << " bytes" << endl;
		}
		ss << setw(width) << "Number of Block Names: " << block_names.size() << endl;
		ss << setw(width) << "Max Block Name Length: " << max_name_length << endl;
		for(const auto& itr : block_names)
		{
			ss	<< setw(width) << "Block Name[" + to_string(++idx) + "]: " << itr << endl;
		}
		if(version >= NIFVersion::V20_1_0_3)
		{
			ss << setw(width) << "Number of Groups: " << num_groups << endl;
		}

		return ss.str();
	}
}