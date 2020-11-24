#include "InternalCombustionEngine.h"
#include <cstring>

bool is_digit(string value) 
{
	size_t i = value.find_first_not_of(" ");
	size_t i_last = value.find_last_not_of(" ");
	bool check = false;

	while (i < i_last && value[i] != ',') {

		if (!('0' <= value[i] && value[i] <= '9')) {
			return false;
		}

		i++;
		if (i < value.size()) {
			if (value[i] == '.' && !check) {
				check = true;
				i++;
			} else if (value[i] == '.' && check) {
				return false;
			}	
		}
	}
	return true;
}

//Creates new ICE from file stream with opened config
ICE::ICE(ifstream* config)
{
	vector<float> buffer;
	string line, param, value;

	while (std::getline(*config, line)) {
		if (line != "") {
			auto len = line.length();
			for (size_t i = 0; i < len; i++) {
				if (line[i] == ' ') continue;
				if (line[i] == ':' || line[i] == '=') {
					param = line.substr(0, i);
					value = line.substr(i + 1, len - 1);
					break;
				}
			}

			if (param == "I") {
				if (!is_digit(value)) {
					cout << "Erorr: unknown parameter " + param + " : " + value << endl;
					return;
				}
				I = stof(value);
			}
			else if (param == "M" || param == "V") {
				len = value.length();
				int last = 0;

				for (size_t i = 0; i < len; i++) {
					if (value[i] == ' ') continue;
					if (value[i] == ',' || i + 1 == len) {
						string sub_value = value.substr(last, i);
						if (!is_digit(sub_value)) {
							cout << "Erorr: unknown parameter " + param + " : " + value << endl;
							return;
						}
						buffer.push_back(stof(sub_value));
						if (value[i] == ',') {
							last = i + 1;
						}		
					}
				}

				if (param == "M") {
					Ms = buffer;
					buffer.clear();
				} else {
					Vs = buffer;
					buffer.clear();
				}
					
			} else if (param == "To") {
				if (!is_digit(value)) {
					cout << "Erorr: unknown parameter " + param + " : " + value << endl;
					return;
				}
				To = stof(value);
			} else if (param == "Hm") {
				if (!is_digit(value)) {
					cout << "Erorr: unknown parameter " + param + " : " + value << endl;
					return;
				}
				Hm = stof(value);
			} else if (param == "Hv") {
				if (!is_digit(value)) {
					cout << "Erorr: unknown parameter " + param + " : " + value << endl;
					return;
				}
				Hv = stof(value);
			} else if (param == "C") {
				if (!is_digit(value)) {
					cout << "Erorr: unknown parameter " + param + " : " + value << endl;
					return;
				}
				C = stof(value);
			} else {
				cout << "Erorr: unknown parameter " + param + " : " + value << endl;
				return;
			}
		}
	}

	if (Ms.size() != Vs.size()) {
		cout << "Error: Vs.size != Ms.size" << endl;
		return;
	} else if (I == 0) {
		cout << "Error: I == 0" << endl;
		return;
	}

	is_valid = true;
}

void ICE::Update(float dt, float te)
{
	UpdateTorque();
	UpdateVelocity(dt);
	auto h = HeatUp(dt);
	auto c = CoolDown(te, dt);
	T += h + c;
}

void ICE::UpdateTorque()
{
	for (size_t i = 0; i < Ms.size() - 1; i++) {
		if (V >= Vs.at(i) && V < Vs.at(i + 1)) {
			// getting new torque depending on current velocity by linear interpolation
			// a + f * (b - a)
			M = Ms.at(i) + (V / Vs.at(i + 1)) * (Ms.at(i + 1) - Ms.at(i));
			return;
		}
	}
	M = Ms.back();
}

void ICE::ShowParam()
{
	cout << "\t\tParameters" << endl;
	cout << "I = " << I << endl;
	cout << "M[" << Ms.size() << "] = ";
	for (size_t i = 0; i < Ms.size(); i++) {
		cout << Ms[i];
		if (i != Ms.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl << "V[" << Vs.size() << "] = ";
	for (size_t i = 0; i < Vs.size(); i++) {
		cout << Vs[i];
		if (i != Vs.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl << "To = " << To << endl;
	cout << "Hm = " << Hm << endl;
	cout << "Hv = " << Hv << endl;
	cout << "C = " << C << endl;
	cout << "V = " << V << endl;
	cout << "I = " << I << endl;
	cout << "M = " << M << endl;
	cout << "Hm = " << Hm << endl;
	cout << "Hv = " << Hv << endl;
	cout << "T = " << T << endl << endl;
}
