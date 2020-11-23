add_library(Com STATIC Com.cpp Com.h)

target_include_directories(
	Com

	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)