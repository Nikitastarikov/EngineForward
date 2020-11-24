#include "Com.h"

float com::maxTime;
float com::dt;

float com::input()
{
	//cout << "time step: ";
	//cin >> dt;
	dt = 1;
	cout << "Max work time: ";
	cin >> maxTime;

	float in;
	cout << "Environment temperature: ";
	cin >> in;
	return in;
}

void com::output(const float time)
{
	if (time >= maxTime)
		cout << endl << "On current environment temperature engine doesn't overheat" << endl;
	else
		cout << endl << "Engine overheated at " << time << " seconds" << endl;
}

void com::err(const char* text) {
	cout << "Error: " << text << endl;
}
