#include "nif_utility.hpp"

#include "gen/export_info.hpp"

using namespace std;

namespace NIF
{
	ExportInfo::ExportInfo()
	{
		unknown = 3;
	}

	ifstream& operator>> (ifstream& inf, ExportInfo& nh)
	{
		nh.creator			= ReadByteString(inf);
		nh.export_info_1	= ReadByteString(inf);
		nh.export_info_2	= ReadByteString(inf);

		return inf;
	}

	ofstream& operator<< (ofstream& outf, const ExportInfo& nh)
	{
		WriteByteString(outf, nh.creator);
		WriteByteString(outf, nh.export_info_1);
		WriteByteString(outf, nh.export_info_2);

		return outf;
	}
}