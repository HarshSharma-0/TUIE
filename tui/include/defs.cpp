#include <defs.hpp>

const char *dirNames[] = {"app",     "app/home", "build",
                          "include", "src",      nullptr};
const char *dirfiles[] = {"app/home/home.xml", "CMakeLists.txt", "src/main.cpp",
                          nullptr};

const char *maincpp = R"(#include <TUIE.hpp>

stateManager<int> intStateManager(0, &cursesEngine);

int start_cursesUI_engine(int argc, char** argv){
    intStateManager.setState(42);
    return 0;
})";

const char *HomeContent = R"(<TUIEngine>
     <View>
        <Text> open home.xml to start editing </Text>
     </View>
 </TUIEngine>)";

const char *CMakeFileHeader = R"(cmake_minimum_required(VERSION 3.6.0)
project(${PROJECT_NAME})

if(DEFINED ENV{HOME})
    set(CMAKE_INSTALL_PREFIX $ENV{HOME})
else()
    message(FATAL_ERROR "Environment variable HOME is not set.")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)

file(GLOB SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
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

# Add shared libraries
add_library(${PROJECT_NAME} SHARED ${SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX "")

# Install the shared libraries
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION .local/${PROJECT_NAME}/lib)

# Custom command to copy the folder
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/.local/${PROJECT_NAME}/app
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/.local/${PROJECT_NAME}/lib
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/app ${CMAKE_INSTALL_PREFIX}/.local/${PROJECT_NAME}/app
    COMMENT "Copying app folder to ${CMAKE_INSTALL_PREFIX}/.local/${PROJECT_NAME}"
)

# Custom target to run the command
add_custom_target(copy_app_folder ALL
    DEPENDS ${PROJECT_NAME}
    COMMENT "Ensure app folder is copied to ${CMAKE_INSTALL_PREFIX}/.local/${PROJECT_NAME}"
))";
