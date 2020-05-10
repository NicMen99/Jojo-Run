project(unittest)

set(GOOGLETEST_VERSION 1.10.1)

add_subdirectory(googletest)

add_executable(testrunner "")

target_sources(testrunner
        PUBLIC
        runner.cpp
        BlockTest.cpp
        # add test files here
)

#
# Source code
#

target_sources(testrunner
        PRIVATE
        # ${CMAKE_SOURCE_DIR}/Src/...
        )

target_include_directories(testrunner
        PUBLIC
        ${CMAKE_SOURCE_DIR}/Src
        )
#
# Googletest reference
#

target_include_directories(testrunner
        PUBLIC
        googletest/include
        googletest
        )

target_link_libraries(testrunner
        gtest
        gtest_main
        )

#
# Setup
#

enable_testing()
include(CTest)
include(Dart)

add_test(.., ..)