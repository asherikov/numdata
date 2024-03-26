cmake_minimum_required(VERSION 3.12)
project(numdata VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE          ON)

add_subdirectory("google-double-conversion")

add_library(${PROJECT_NAME}
    src/${PROJECT_NAME}.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/google-double-conversion>
)

target_link_libraries(${PROJECT_NAME} double-conversion)


add_executable(demo
    test/demo.cpp
)

target_include_directories(
    demo PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(demo ${PROJECT_NAME})
