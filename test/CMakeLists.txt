find_package(Boost 1.62.0 COMPONENTS unit_test_framework REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#add_subdirectory()
