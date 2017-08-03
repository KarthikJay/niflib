#include <iomanip>
#include <sstream>

#include <NIF/header.hpp>
#include <NIF/utility.hpp>

using namespace std;

namespace NIF
{
	void ExportInfo::ReadBinary(istream& in)
	{
		uint32_t num_info = use_extra ? info.max_size() : kOldInfoSize;

		creator = ReadByteString(in);
		for(uint32_t i = 0; i < num_info; ++i)
		{
			info[i] = ReadByteString(in);
		}
	}

	void ExportInfo::WriteBinary(ostream& out) const
	{
		uint32_t num_info = use_extra ? info.max_size() : kOldInfoSize;

		WriteByteString(out, creator);
		for(uint32_t i = 0; i < num_info; ++i)
		{
			WriteByteString(out, info[i]);
		}
	}

	istream& operator>>(istream& in, ExportInfo& obj)
	{
		obj.ReadBinary(in);

		return in;
	}

	ostream& operator<<(ostream& out, const ExportInfo& obj)
	{
		obj.WriteBinary(out);

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

	void Header::ReadBinary(istream& in)
	{
		uint8_t test_byte;
		uint32_t vec_size;

		header_line = ReadLine(in);
		ValidNIF(header_line);

		if(version <= NIFVersion::V3_1)
		{
			for(auto& itr : copyright)
			{
				itr = ReadLine(in);
			}
		}

		if(version >= Version(3,3,0,13))
		{
			in.read(reinterpret_cast<char*>(&version), sizeof(version));
		}

		if(version >= NIFVersion::V20_0_0_4)
		{
			in.read(reinterpret_cast<char*>(&test_byte), sizeof(test_byte));
			endian = static_cast<EndianType>(test_byte);
		}

		if(version >= NIFVersion::V10_1_0_0)
		{
			in.read(reinterpret_cast<char*>(&user_version_1), sizeof(user_version_1));
		}

		if(version >= Version(3,3,0,13))
		{
			in.read(reinterpret_cast<char*>(&vec_size), sizeof(vec_size));
			block_sizes.resize(vec_size);
			block_type_index.resize(vec_size);
		}

		if(version >= NIFVersion::V10_1_0_0)
		{
			if(user_version_1 >= 10 ||
				((user_version_1 == 1) && version != NIFVersion::V10_2_0_0))
			{
				in.read(reinterpret_cast<char*>(&user_version_2), sizeof(user_version_2));
			}
		}

		if(version >= NIFVersion::V30_0_0_2)
		{
			in.read(reinterpret_cast<char*>(&image_preview_size), sizeof(image_preview_size));
		}

		if(version >= NIFVersion::V10_0_1_0)
		{
			if(version >= NIFVersion::V20_2_0_7 && user_version_2 == 130)
			{
				export_info.use_extra = true;
			}
			in >> export_info;
		}

		if(version >= NIFVersion::V10_1_0_0)
		{
			in.read(reinterpret_cast<char*>(&vec_size), sizeof(uint16_t));
			block_type_names.resize(vec_size);
			for(auto& itr : block_type_names)
			{
				itr = ReadIntString(in);
			}
			for(auto& itr : block_type_index)
			{
				in.read(reinterpret_cast<char*>(&itr), sizeof(itr));
			}
		}

		if(version >= NIFVersion::V20_2_0_7)
		{
			for(auto& itr : block_sizes)
			{
				in.read(reinterpret_cast<char*>(&itr), sizeof(itr));
			}
		}

		if(version >= NIFVersion::V20_1_0_3)
		{
			in.read(reinterpret_cast<char*>(&vec_size), sizeof(vec_size));
			in.read(reinterpret_cast<char*>(&max_name_length), sizeof(max_name_length));
			block_names.resize(vec_size);
			for(auto& itr : block_names)
			{
				itr = ReadIntString(in);
			}
		}

		if(version >= Version(5,0,0,6))
		{
			in.read(reinterpret_cast<char*>(&num_groups), sizeof(num_groups));
		}
	}

	void Header::WriteBinary(ostream& out) const
	{
		WriteLine(out, header_line);

		if(version <= NIFVersion::V3_1)
		{
			for(const auto& itr : copyright)
			{
				WriteLine(out, itr);
			}
		}
		
		if(version >= Version(3,3,0,13))
		{
			WriteUnsignedIntegral(out, version);
		}

		if(version >= NIFVersion::V20_0_0_4)
		{
			WriteUnsignedIntegral(out, ToIntegral(endian));
		}

		if(version >= NIFVersion::V10_1_0_0)
		{
			WriteUnsignedIntegral(out, user_version_1);
		}

		if(version >= Version(3,3,0,13))
		{
			WriteUnsignedIntegral(out, static_cast<uint32_t>(block_type_index.size()));
		}

		if(version >= NIFVersion::V10_1_0_0)
		{
			if(user_version_1 >= 10 ||
				((user_version_1 == 1) && version != NIFVersion::V10_2_0_0))
			{
				WriteUnsignedIntegral(out, user_version_2);
			}
		}

		if(version >= NIFVersion::V30_0_0_2)
		{
			WriteUnsignedIntegral(out, image_preview_size);
		}

		if(version >= NIFVersion::V10_0_1_0)
		{
			out << export_info;
		}

		if(version >= NIFVersion::V10_1_0_0)
		{
			WriteUnsignedIntegral(out, static_cast<uint16_t>(block_type_names.size()));
			for(const auto& itr : block_type_names)
			{
				WriteIntString(out, itr);
			}
			for(const auto& itr : block_type_index)
			{
				WriteUnsignedIntegral(out, itr);
			}
		}

		if(version >= NIFVersion::V20_2_0_7)
		{
			for(const auto& itr : block_sizes)
			{
				WriteUnsignedIntegral(out, itr);
			}
		}

		if(version >= NIFVersion::V20_1_0_3)
		{
			WriteUnsignedIntegral(out, static_cast<uint32_t>(block_names.size()));
			WriteUnsignedIntegral(out, max_name_length);
			for(const auto& itr : block_names)
			{
				WriteIntString(out, itr);
			}
		}

		if(version >= Version(5,0,0,6))
		{
			WriteUnsignedIntegral(out, num_groups);
		}
	}

	istream& operator>> (istream& in, Header& obj)
	{
		obj.ReadBinary(in);

		return in;
	}

	ostream& operator<<(ostream& out, const Header& obj)
	{
		obj.WriteBinary(out);

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