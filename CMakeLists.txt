cmake_minimum_required(VERSION 3.8.2)
project(rastertovkp80)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
add_subdirectory(src)

install(DIRECTORY ppd/ DESTINATION /usr/share/ppd)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR ENABLE_TESTING)
        #include(cmake/test.cmake)

        #add_subdirectory(test)

        #add_all_test_targets()
    endif()
endif()

