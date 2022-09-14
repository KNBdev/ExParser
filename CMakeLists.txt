cmake_minimum_required(VERSION 3.16)

project(exparser)

file(GLOB SOURCES "src/*/*.c")

file(GLOB INCLUDE_DIRS "src/*/")
list(APPEND INCLUDE_DIRS "include")
include_directories(${INCLUDE_DIRS})

set(OBJLIB ${PROJECT_NAME}_o)
add_library(${OBJLIB} OBJECT ${SOURCES})
set_property(TARGET ${OBJLIB} PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(${PROJECT_NAME}_s STATIC $<TARGET_OBJECTS:${OBJLIB}>)
add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${OBJLIB}>)

#

add_executable(exparser_tests examples/exparser_tests.c)
target_link_libraries(exparser_tests exparser_s m)

add_executable(exparser_example_1 examples/exparser_example_1.c)
target_link_libraries(exparser_example_1 exparser_s m)

add_executable(exparser_example_2 examples/exparser_example_2.c)
target_link_libraries(exparser_example_2 exparser_s m)