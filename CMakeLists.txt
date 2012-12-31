cmake_minimum_required (VERSION 2.6)
project (Sprint)
file(GLOB Sprint_SRC *.h *.cpp)
add_library(Sprint ${Sprint_SRC})
target_link_libraries(Sprint -lrt)
set(CMAKE_BUILD_TYPE, Release)
if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-DSPRINT_POSIX)
    add_definitions(-std=c++0x)
endif()

# We compile Google Test ourselves instead of using pre-compiled libraries.
# See the Google Test FAQ "Why is it not recommended to install a
# pre-compiled copy of Google Test (for example, into /usr/local)?"
# at http://code.google.com/p/googletest/wiki/FAQ for more details.
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/gtest/CMakeLists.txt)
  # Build format
  if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/format/CMakeLists.txt)
      add_subdirectory(format)
      include_directories(format)
  endif()
  option(
    gtest_force_shared_crt
    "Use shared (DLL) run-time lib even when Google Test is built as static lib."
    ON)
  add_subdirectory(gtest)
  include_directories(gtest/include)
  link_directories(${CMAKE_CURRENT_BINARY_DIR}/gtest)
  enable_testing()
  add_executable(SprintTest SprintTest.cpp)
  target_link_libraries(SprintTest Sprint gtest format)
  if (CMAKE_COMPILER_IS_GNUCXX)
      set_target_properties(SprintTest PROPERTIES COMPILE_FLAGS
      "-Wall -Wextra -pedantic -Wno-long-long -Wno-variadic-macros")
  endif ()
  add_test(SprintTest SprintTest)
endif ()
