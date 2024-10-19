cmake_minimum_required(VERSION 3.10)
project(cursesUI)

# Find libxml2 package
find_package(LibXml2 REQUIRED)

# Set the library name
set(ENGINE_NAME TUIE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(DEFINED ENV{PREFIX})
    set(CMAKE_INSTALL_PREFIX $ENV{PREFIX})
else()
    message(FATAL_ERROR "Environment variable HOME is not set.")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/StateManager
    ${PROJECT_SOURCE_DIR}/NavigationManager
    ${PROJECT_SOURCE_DIR}/TUIEParser
    ${PROJECT_SOURCE_DIR}/Engine
    ${LIBXML2_INCLUDE_DIR}
)


file(GLOB SRCS
        "${PROJECT_SOURCE_DIR}/include/*"
        "${PROJECT_SOURCE_DIR}/src/*"
        "${PROJECT_SOURCE_DIR}/StateManager/*"
        "${PROJECT_SOURCE_DIR}/NavigationManager/*"
        "${PROJECT_SOURCE_DIR}/TUIEParser/*"
        "${PROJECT_SOURCE_DIR}/Engine/*"
)

# Add the library sources
add_executable(${ENGINE_NAME} ${SRCS})

# Link against libxml2 library
target_link_libraries(${ENGINE_NAME} ${LIBXML2_LIBRARIES})

# Installation directives
install(TARGETS ${ENGINE_NAME} DESTINATION bin)


