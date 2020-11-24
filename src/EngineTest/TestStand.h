#pragma once
#include "Engine.h"
#include "Com.h"

#include <memory>

//absolute error for temperature comparision
#define ERR 10e-3

namespace Stands {

	template<typename TypeEngine>
	class TestStand
	{
	private:

		bool isEngineOverheated();
		float dt = 1; // Time step
		float Te; // Environment temperature
	public:
		std::unique_ptr<TypeEngine> engine = nullptr;// Engine used for tests
		//TypeEngine engine; 
		float RunTest(); // Runs test
		TestStand(unique_ptr<TypeEngine> engine, float te); // Creates new instance of TestStand
	};

	template<typename TypeEngine>
	inline bool TestStand<TypeEngine>::isEngineOverheated() {
		return engine->T >= engine->To - ERR;
	}

	template<typename TypeEngine>
	float TestStand<TypeEngine>::RunTest() {
		float time = 0;
		while (!isEngineOverheated() && time < com::maxTime)
		{
			time += dt;
			engine->Update(dt, Te);
			//engine->ShowParam();
			if (engine->T >= engine->To) {
				break;
			}
		}
		return time;
	};

	template<typename TypeEngine>
	TestStand<TypeEngine>::TestStand(unique_ptr<TypeEngine> eng, float te) {
		engine = move(eng);
		dt = com::dt;
		Te = te;
		engine->T = Te;
	};
}