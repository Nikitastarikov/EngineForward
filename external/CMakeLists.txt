  cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_subdirectory(gTest)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

#add_subdirectory(cxxopts)

###########################################GIT########################################

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
    	#Log a message
        message(STATUS "Submodule update")
        #Execute one or more child processes.
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
        				#The named directory will be set as the current working directory of the child processes.
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        #The variable will be set to contain the result of last child process. 
                        #This will be an integer return code from the last child or a string describing an error condition.
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/gTest/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
 #NOT EXISTS "${PROJECT_SOURCE_DIR}/external/cxxopts/CMakeLists.txt" OR 