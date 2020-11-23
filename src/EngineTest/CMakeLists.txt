add_library(TestStand STATIC InternalCombustionEngine.cpp InternalCombustionEngine.h TestStand.h Engine.h)

target_include_directories(
	TestStand

	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)