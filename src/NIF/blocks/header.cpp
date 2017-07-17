#include <iomanip>
#include <sstream>

#include <NIF/blocks/header.hpp>
#include <NIF/utility.hpp>

using namespace std;

namespace NIF
{

	ExportInfo::ExportInfo()
	{
		unknown = 3;
		for(auto itr : info)
		{
			itr = "";
		}
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

	Header::Header()
	{
		header_line.reserve(45);
		this->version = ToIntegral(NIFVersion::V4_0_0_2);
		this->user_version_1 = 0;
		endian = EndianType::ENDIAN_LITTLE;
	}

	istream& operator>> (istream& in, Header& obj)
	{
		uint8_t test_byte;

		obj.header_line = ReadLine(in);
		ValidNIF(obj.header_line);

		if(obj.version <= NIFVersion::V3_1)
		{
			for(auto& itr : obj.copyright)
			{
				itr = ReadLine(in);
			}
		}

		if(obj.version >= NIFVersion::V3_3_0_13)
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

		if(obj.version >= NIFVersion::V20_0_0_4)
		{
			in.read(reinterpret_cast<char*>(&obj.num_blocks), sizeof(obj.num_blocks));
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
			in.read(reinterpret_cast<char*>(&obj.unknown), sizeof(obj.unknown));
		}

		if(obj.version >= NIFVersion::V10_0_1_0)
		{
			if((obj.user_version_1 == 10) ||
				((obj.user_version_1 == 1) && obj.version != NIFVersion::V10_2_0_0))
			{
				in.read(reinterpret_cast<char*>(&obj.export_info.unknown), sizeof(obj.export_info.unknown));
				in >> obj.export_info.unknown;
			}
			if(obj.version >= NIFVersion::V20_2_0_7 && obj.user_version_2 == 130)
			{
				obj.export_info.use_extra = true;
			}
			in >> obj.export_info;
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			in.read(reinterpret_cast<char*>(&obj.num_block_type), sizeof(obj.num_block_type));
			obj.block_type_names.resize(obj.num_block_type);
			for(auto& itr : obj.block_type_names)
			{
				itr = ReadIntString(in);
			}
			obj.block_index.resize(obj.num_blocks);
			for(auto& itr : obj.block_index)
			{
				in.read(reinterpret_cast<char*>(&itr), sizeof(itr));
			}
		}

		if(obj.version >= NIFVersion::V20_2_0_7)
		{
			obj.block_size.resize(obj.num_blocks);
			for(auto& itr : obj.block_size)
			{
				in.read(reinterpret_cast<char*>(&itr), sizeof(itr));
			}
		}

		if(obj.version >= NIFVersion::V20_1_0_3)
		{
			in.read(reinterpret_cast<char*>(&obj.num_block_names), sizeof(obj.num_block_names));
			in.read(reinterpret_cast<char*>(&obj.max_name_length), sizeof(obj.max_name_length));
			obj.block_names.reserve(obj.num_block_names);
			for(uint32_t i = 0; i < obj.num_block_names; ++i)
			{
				obj.block_names.push_back(ReadIntString(in));
			}
		}

		if(obj.version >= NIFVersion::V5_0_0_6)
		{
			in.read(reinterpret_cast<char*>(&obj.num_groups), sizeof(obj.num_groups));
		}
		return in;
	}

	void Header::UpdateNums()
	{
		num_block_names = block_names.size();
		num_block_type = block_type_names.size();
		num_blocks = block_index.size();
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
		
		if(obj.version >= NIFVersion::V3_3_0_13)
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

		if(obj.version >= NIFVersion::V3_3_0_13)
		{
			WriteUnsignedIntegral(out, obj.num_blocks);
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
			WriteUnsignedIntegral(out, obj.unknown);
		}

		if(obj.version >= NIFVersion::V10_0_1_0)
		{
			if(obj.user_version_1 == 10 ||
				(obj.user_version_1 == 1 && obj.version != NIFVersion::V10_2_0_0))
			{
				WriteUnsignedIntegral(out, obj.export_info.unknown);
			}
			out << obj.export_info;
		}

		if(obj.version >= NIFVersion::V10_1_0_0)
		{
			WriteUnsignedIntegral(out, obj.num_block_type);
			for(const auto& itr : obj.block_type_names)
			{
				WriteIntString(out, itr);
			}
			for(const auto& itr : obj.block_index)
			{
				WriteUnsignedIntegral(out, itr);
			}
		}

		if(obj.version >= NIFVersion::V20_2_0_7)
		{
			for(const auto& itr : obj.block_size)
			{
				WriteUnsignedIntegral(out, itr);
			}
		}

		if(obj.version >= NIFVersion::V20_1_0_3)
		{
			WriteUnsignedIntegral(out, obj.num_block_names);
			WriteUnsignedIntegral(out, obj.max_name_length);
			for(const auto& itr : obj.block_names)
			{
				WriteIntString(out, itr);
			}
		}

		if(obj.version >= NIFVersion::V5_0_0_6)
		{
			WriteUnsignedIntegral(out, obj.num_groups);
		}

		return out;
	}

	string Header::str()
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
		ss << setw(width) << "Number of blocks: " << num_blocks << endl;
		if(user_version_1 >= 10 ||
				((user_version_1 == 1) && version != NIFVersion::V10_2_0_0))
		{
			ss << setw(width) << "User Version 2: " << user_version_2 << endl;
		}
		ss << export_info.str();
		ss << setw(width) << "Number of Block Types: " << num_block_type << endl;
		for(uint32_t i = 0; i < num_block_type; ++i)
		{
			ss	<< setw(width) << "Block Type Name[" + to_string(i) + "]: "
				<< block_type_names[i] << endl;
		}
		for(uint32_t i = 0; i < num_blocks; ++i)
		{
			ss	<< setw(width) << "Block Index[" + to_string(i) + "]: "
				<< block_type_names[block_index[i]] << endl;
		}
		for(uint32_t i = 0; i < num_blocks; ++i)
		{
			ss	<< setw(width) << "Block Size[" + to_string(i) + "]: "
				<< block_size[i] << endl;
		}
		ss << setw(width) << "Number of Block Names: " << num_block_names << endl;
		ss << setw(width) << "Max Block Name Length: " << max_name_length << endl;
		for(const auto& itr : block_names)
		{
			ss	<< setw(width) << "Block Name[" + to_string(++idx) + "]: " << itr << endl;
		}
		if(version >= NIFVersion::V20_1_0_3)
		{
			ss << setw(width) << "Uknown Integer: " << unknown << endl;
		}

		return ss.str();
	}

	uint32_t Header::GetVersion()
	{
		return version;
	}
}