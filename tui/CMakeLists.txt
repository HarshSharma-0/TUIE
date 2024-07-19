cmake_minimum_required(VERSION 3.6.0)
project(tui)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(DEFINED ENV{PREFIX})
    set(CMAKE_INSTALL_PREFIX $ENV{PREFIX})
else()
    message(FATAL_ERROR "Environment variable HOME is not set.")
endif()

# Include directories
include_directories(

    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)

# Gather source files
file(GLOB SRCS

    "${PROJECT_SOURCE_DIR}/src/*"
    "${PROJECT_SOURCE_DIR}/include/*"

)

set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Check for C++20 support
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
    message(STATUS "Your compiler does not support C++20, falling back to C++17.")
    set(CMAKE_CXX_STANDARD 17)
else()
    message(STATUS "Your compiler supports C++20, using C++20")
    set(CMAKE_CXX_STANDARD 20)
endif()

# Add executable
add_executable(tui ${SRCS})

install(TARGETS tui DESTINATION bin)




