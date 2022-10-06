cmake_minimum_required(VERSION 3.20)
project(big_int)

set(CMAKE_CXX_STANDARD 14)

add_executable(big_int main.cpp BigInt.cpp BigInt.h gtest.cpp)

#find_package(GTest)
#target_link_libraries(big_int {GTEST_LIBRARY})
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(big_int gtest_main)
add_test(NAME example_test COMMAND example)