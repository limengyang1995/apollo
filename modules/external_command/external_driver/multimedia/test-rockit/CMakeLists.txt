cmake_minimum_required(VERSION 3.13.5)

project(rk-capture-demo)

execute_process(
COMMAND ldd --version
    OUTPUT_VARIABLE LDD_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REGEX MATCH "[0-9]+\\.[0-9]+" GLIBC_VERSION "${LDD_OUTPUT}")
message(STATUS "glibc version: ${GLIBC_VERSION}")
# GLIBC_VERSION 大于等于 2.33
if (${GLIBC_VERSION} VERSION_GREATER_EQUAL "2.33")
    message(STATUS "###################################### glibc version is greater or equal to 2.33, use new rockit")
    SET(ROCKIT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rockit-new)
else()
    SET(ROCKIT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rockit)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${ROCKIT_DIR}/include)
link_directories(${ROCKIT_DIR}/lib64)
link_libraries(rockit)

add_executable(demo-rk-capture main.cpp)
