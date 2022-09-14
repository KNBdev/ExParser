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
