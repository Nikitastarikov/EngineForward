cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

##################################GTest##############################

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(tests tests.cpp)

target_link_libraries(
	tests 
		
		PRIVATE
			gtest_main
			TestStand
)

add_test(NAME example_test COMMAND tests)