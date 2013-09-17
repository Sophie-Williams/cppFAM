cmake_minimum_required(VERSION 2.8.9)
project(fam)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_subdirectory (src)
add_subdirectory (examples)

#======================
# Testing stuff...

# Enable a 'test' build target
# enable_testing()

#--------------
# Unit Tests
#

# Where are the relevant sources and their includes?
# set(TEST_SRCS src/board.cpp test/board_test.cpp)
# file(GLOB TEST_SRCS test/*.cpp src/board.cpp)
# include_directories("${CMAKE_SOURCE_DIR}/include")

# Since we're using real classes via fixtures, we're going
# to need TBB linked.
# link_directories(${CMAKE_SOURCE_DIR}/ext/tbb41_20130613oss/lib)

# For ctest / make test
# add_test(NAME UnitTests COMMAND run_unit_tests)

# Make a standalone test executable (separate from ctest / make test)
# add_executable(run_unit_tests ${TEST_SRCS})

# Link the test executable against gtest & gtest_main
# target_link_libraries(run_unit_tests gtest gtest_main tbb tbbmalloc)

#--------------
# Google Test
#

# ADD_SUBDIRECTORY (ext/googletest-read-only)
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
