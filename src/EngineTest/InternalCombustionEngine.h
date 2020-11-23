#pragma once
#include <vector>

#include "Engine.h"

using namespace std;

//Internal Combustion Engine
class ICE : public Engine
{

private:
	ICE() : Engine() {};
	vector<float> Ms; // torques
	vector<float> Vs; // velocities

	float I = 0; // Inertia
	float M = 0; // Current torque
	float V = 0; // Current velocity

	float Hm = 0; // Torque to heat coefficient
	float Hv = 0; // Velocity to heat coefficient

	float C = 0; // Environment influence coefficient

public:
	float T = 0; // Current temperature
	float To = 0; // Overheat temperature

	ICE(ifstream* config); //  Configurates new engine from opened config file
	void Update(float dt, float te);
	void ShowParam();

	// Updates current velocity
	void UpdateVelocity(float dt)
	{
		//velocity += acceleration * dt
		//acceleration = Current torque / Inertia (as said in task)
		V += (M / I) * dt;
	}

	// Heats up the engine depending on time step
	float HeatUp(float dt) { 
		return (M * Hm + V * V * Hv) * dt;
	}

	// Cools down the engine depending on time step and environment temperature
	float CoolDown(float e, float dt) {
		return C * (e - T) * dt;
	}

	// Updates current torque
	void UpdateTorque();
};

