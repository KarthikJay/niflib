#include "obj/nif_header.hpp"
#include "nif_enum.hpp"
#include "nif_utility.hpp"

using namespace std;

namespace NIF
{
	NIFHeader::NIFHeader(uint32_t version)
	{
		this->version = version;
		endian = EndianType::ENDIAN_LITTLE;
	}

	//! \todo Remove endianness checks
	ifstream& operator>> (ifstream& inf, NIFHeader& nh)
	{
		uint8_t test_byte;

		if(nh.version <= NIFVersion::V3_1)
		{
			for(auto itr : nh.copyright)
			{
				itr = ReadLine(inf);
			}
		}

		if(nh.version >= NIFVersion::V20_0_0_4)
		{
			inf >> test_byte;
			nh.endian = static_cast<EndianType>(test_byte);
		}

		if(nh.version >= NIFVersion::V10_1_0_0)
		{
			inf >> nh.user_version_1;
		}

		if(nh.version >= NIFVersion::V20_0_0_4)
		{
			inf >> nh.num_blocks;
		}

		if(nh.version >= NIFVersion::V10_1_0_0)
		{
			if(nh.user_version_1 >= 10 ||
				((nh.user_version_1 == 1) && nh.version != NIFVersion::V10_2_0_0))
			{
				inf >> nh.user_version_2;
			}
		}

		if(nh.version >= NIFVersion::V30_0_0_2)
		{
			inf >> nh.unknown_int_2;
		}

		if(nh.version >= NIFVersion::V10_0_1_0)
		{
			if((nh.user_version_1 = 10) ||
				((nh.user_version_1 = 1) && nh.version != NIFVersion::V10_2_0_0))
			{
				inf >> nh.export_info.unknown;
			}
			inf >> nh.export_info;
		}

		if(nh.version >= NIFVersion::V20_2_0_7 && nh.user_version_2 == 130)
		{
			nh.export_info_3 = ReadByteString(inf);
		}

		if(nh.version >= NIFVersion::V10_1_0_0)
		{
			inf >> nh.num_block_type;
			nh.block_type_names.resize(nh.num_block_type);
			for(auto itr : nh.block_type_names)
			{
				itr = ReadIntString(inf);
			}
			nh.block_index.resize(nh.num_blocks);
			for(auto itr : nh.block_index)
			{
				inf >> itr;
			}
		}

		if(nh.version >= NIFVersion::V20_2_0_7)
		{
			nh.block_size.resize(nh.num_blocks);
			for(auto itr : nh.block_size)
			{
				inf >> itr;
			}
		}

		if(nh.version >= NIFVersion::V20_1_0_3)
		{
			inf >> nh.num_strings;
			inf >> nh.max_string_length;
			nh.strings.resize(nh.num_strings);
			for(auto itr : nh.strings)
			{
				itr = ReadIntString(inf);
			}
		}

		if(nh.version >= NIFVersion::V20_1_0_3)
		{
			inf >> nh.unknown_int_2;
		}

		return inf;
	}

	void NIFHeader::UpdateNums()
	{
		num_strings = strings.size();
		num_block_type = block_type_names.size();
		num_blocks = block_index.size();
	}

	ofstream& operator<< (ofstream& outf, const NIFHeader& nh)
	{
		if(nh.version >= NIFVersion::V3_1)
		{
			for(auto itr : nh.copyright)
			{
				outf << itr << "/n";
			}
		}
		
		if(nh.version >= NIFVersion::V3_3_0_13)
		{
			WriteUnsignedIntegral(outf, nh.version);
		}

		if(nh.version >= NIFVersion::V20_0_0_4)
		{
			WriteUnsignedIntegral(outf, ToIntegral(nh.endian));
		}

		if(nh.version >= NIFVersion::V10_1_0_0)
		{
			WriteUnsignedIntegral(outf, nh.user_version_1);
		}

		if(nh.version >= NIFVersion::V3_3_0_13)
		{
			WriteUnsignedIntegral(outf, nh.num_blocks);
		}

		if(nh.version >= NIFVersion::V10_1_0_0)
		{
			if(nh.user_version_1 >= 10 ||
				((nh.user_version_1 == 1) && nh.version != NIFVersion::V10_2_0_0))
			{
				WriteUnsignedIntegral(outf, nh.user_version_2);
			}
		}

		if(nh.version >= NIFVersion::V30_0_0_2)
		{
			WriteUnsignedIntegral(outf, nh.unknown_int_2);
		}

		if(nh.version >= NIFVersion::V10_0_1_0)
		{
			if(nh.user_version_1 == 10 ||
				(nh.user_version_1 == 1 && nh.version != NIFVersion::V10_2_0_0))
			{
				WriteUnsignedIntegral(outf, nh.export_info.unknown);
			}
			outf << nh.export_info;
		}

		if(nh.version >= NIFVersion::V20_2_0_7 && nh.user_version_2 == 130)
		{
			WriteByteString(outf, nh.export_info_3);
		}

		if(nh.version >= NIFVersion::V10_1_0_0)
		{
			WriteUnsignedIntegral(outf, nh.num_block_type);
			for(auto itr : nh.block_type_names)
			{
				WriteIntString(outf, itr);
			}
			for(auto itr : nh.block_index)
			{
				WriteUnsignedIntegral(outf, itr);
			}
		}

		if(nh.version >= NIFVersion::V20_2_0_7)
		{
			for(auto itr : nh.block_size)
			{
				WriteUnsignedIntegral(outf, itr);
			}
		}

		if(nh.version >= NIFVersion::V20_1_0_3)
		{
			WriteUnsignedIntegral(outf, nh.num_strings);
			WriteUnsignedIntegral(outf, nh.max_string_length);
			for(auto itr : nh.strings)
			{
				WriteIntString(outf, itr);
			}
		}

		if(nh.version >= NIFVersion::V20_1_0_3)
		{
			WriteUnsignedIntegral(outf, nh.unknown_int_2);
		}

		return outf;
	}

	//! \todo Add fixed width formatting for pretty output
	stringstream& operator<< (stringstream& ss, const NIFHeader& nh)
	{
		ss << "Copyright: ";
		for(auto itr : nh.copyright)
		{
			ss << "  " << itr;
		}
		ss << "Version: " << nh.version << endl;

		return ss;
	}

	uint32_t NIFHeader::GetVersion()
	{
		return version;
	}
}