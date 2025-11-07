cmake_minimum_required(VERSION 3.20)
project(alg-lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#52eb8108c5bdec04579160ae17225d66034bd723

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE ut-src Tests/*.cc)
add_executable(
  alg-lib-ut 
  ${ut-src}
)
target_include_directories(
  alg-lib-ut PUBLIC
  Include/
)
target_link_libraries(
  alg-lib-ut PUBLIC
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(alg-lib-ut)

