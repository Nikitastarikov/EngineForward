#include "InternalCombustionEngine.h"
//#include "TestStand.h"

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <utility>
#include <memory>

TEST(tests_in, one_test)
{
	ifstream configStream("../../../../tests/gtest/enginetest/engineone.cfg", ios::in);

	if (!configStream) {
		std::cerr << "Can't open config file" << std::endl;
	}

	unique_ptr<ICE> engine(new ICE(&configStream));
	configStream.close();
	
	ASSERT_EQ(engine->is_valid, true);
}

TEST(tests_in, two_test)
{
	ifstream configStream("../../../../tests/gtest/enginetest/enginetwo.cfg", ios::in);

	if (!configStream) {
		std::cerr << "Can't open config file" << std::endl;
	}

	unique_ptr<ICE> engine(new ICE(&configStream));
	configStream.close();

	ASSERT_EQ(engine->is_valid, false);
}

TEST(tests_in, three_test)
{
	ifstream configStream("../../../../tests/gtest/enginetest/enginethree.cfg", ios::in);

	if (!configStream) {
		std::cerr << "Can't open config file" << std::endl;
	}

	unique_ptr<ICE> engine(new ICE(&configStream));
	configStream.close();

	ASSERT_EQ(engine->is_valid, false);
}

TEST(tests_in, four_test)
{
	ifstream configStream("../../../../tests/gtest/enginetest/enginefour.cfg", ios::in);

	if (!configStream) {
		std::cerr << "Can't open config file" << std::endl;
	}

	unique_ptr<ICE> engine(new ICE(&configStream));
	configStream.close();

	ASSERT_EQ(engine->is_valid, false);
}