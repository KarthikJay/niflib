#include <string>
#include <fstream>

#include "gtest/gtest.h"
#include "nif_api.hpp"

using namespace std;

namespace NIF_TEST
{
	class NIFHeaderTest : public testing::Test
	{
	protected:
		std::string file_name;

		SkyrimPCReadTest() {}

		virtual ~SkyrimPCReadTest() {}

		void SetUp(const std::string file_name)
		{
			this->file_name = file_name;
		}

		virtual void TearDown()
		{
			file_name = "";
		}
	};
}