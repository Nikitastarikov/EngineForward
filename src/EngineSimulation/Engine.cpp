#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "InternalCombustionEngine.h"
#include "TestStand.h"
#include "Com.h"

using namespace std;
using namespace Stands;

int main(int argc, char* argv[])
{
	// default
	string nameInputFile = "../../../../testfile/engine.cfg";

	// checking args
	switch (argc) {
	case 1:
		break;
	case 2:
		nameInputFile = argv[1];
		break;
	default:
		com::err("Too many arguments.\nThis program requires only one as path to engine configuration");
		return 1;
	}

	// trying to read config file
	ifstream configStream(nameInputFile, ifstream::in);

	// checking the correctness of opening a file
	if (!configStream) {
		com::err("Can't open config file");
		return 1;
	}

	// memory allocation and test run
	try {
		unique_ptr<ICE> engine(new ICE(&configStream));
		engine->ShowParam();
		configStream.close();

		if (!engine->is_valid) {
			com::err("Engine config loaded unsuccessfully");

			return 1;
		}

		auto stand = new TestStand<ICE>(move(engine), com::input());
		com::output(stand->RunTest());
	}
	catch (exception ex) {
		com::err("Wrong input");

		return 1;
	}

	return 0;
}