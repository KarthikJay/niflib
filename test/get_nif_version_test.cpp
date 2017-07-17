#include <cstdint>
#include <cassert>
#include <string>
#include <iostream>

#include <gtest/gtest.h>
#include <NIF/api.hpp>
#include <NIF/utility.hpp>

using namespace NIF;
using namespace std;

string data_path = "";

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	assert(argc == 2);
	data_path = string(argv[1]);

	return RUN_ALL_TESTS();
}

TEST(GetNifVersion, SkyrimPC)
{
	uint32_t val = GetNifVersion(data_path + "skyrim_pc.nif");
	NIFVersion version = static_cast<NIFVersion>(val);
	EXPECT_EQ(NIFVersion::V20_2_0_7, version);
}