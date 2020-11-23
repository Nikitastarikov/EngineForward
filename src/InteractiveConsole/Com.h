#pragma once
#include <iostream>

using namespace std;

struct com
{
public:
	static float dt;
	static float maxTime;
	static float input();
	static void output(const float time);
	static void err(const char* text);
};