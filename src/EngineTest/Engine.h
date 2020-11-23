#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Base class for engines
class Engine
{
protected:

	Engine() { is_valid = false; };

public:

	bool is_valid;
	virtual void Update() {};
};