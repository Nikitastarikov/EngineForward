cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

list(APPEND EXTRA_LIBS Com)
list(APPEND EXTRA_LIBS TestStand)
#list(APPEND EXTRA_LIBS cxxopts)

#if(CXXOPTS_BUILD_EXAMPLES)

#	message("INPUT!!!")
	add_executable(EngineForward Engine.cpp)

	target_link_libraries(
		EngineForward 

		PRIVATE
			${EXTRA_LIBS}
	)

	target_include_directories(
		EngineForward

		PUBLIC ${PROJECT_BINARY_DIR}
		INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	)
#endif()