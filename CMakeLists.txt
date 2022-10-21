cmake_minimum_required(VERSION 3.18)
project(nanovk)

set(CMAKE_CXX_STANDARD 20)

# Set build type if not set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Build flags: ${CMAKE_CXX_FLAGS_DEBUG}")
else()
    message(STATUS "Build flags: ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

message(STATUS "Using compiler: ${CMAKE_CXX_COMPILER_ID}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    #set to see all warnings
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
elseif(MSVC)
    #set to see all warnings and if windows set exception handling mode to sc [https://docs.microsoft.com/en-us/cpp/build/reference/eh-exception-handling-model?view=msvc-170]
    set(CMAKE_CXX_FLAGS "-EHsc")
endif()

find_package(Vulkan REQUIRED)
message(STATUS "Vulkan include dirs: ${Vulkan_INCLUDE_DIRS}")

# Library implementation in src
add_subdirectory(src)

target_include_directories(nanovk PUBLIC
    "include"
    ${Vulkan_INCLUDE_DIRS}
)

# Include external dependencies
add_subdirectory(dependencies)

# Build sample project
if (NANOVK_BUILD_EXAMPLES)
    add_subdirectory(samples)
endif()

# keep enable_testing command in the source directory root because ctest expects to find a test file in the build directory root.
# enable_testing() 

# Test configuration in the test folder
# add_subdirectory(tests)