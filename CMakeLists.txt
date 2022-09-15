cmake_minimum_required(VERSION 3.16)

project(exparser)

set(SOURCES "src/*/*.c")
set(INCLUDE "include/exparser.h")
list(APPEND INCLUDE_DIRS "include" "src/*/")

#------------------------------------------------------------------------------

file(GLOB SOURCES ${SOURCES})

file(GLOB INCLUDE_DIRS ${INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})

set(OBJLIB ${PROJECT_NAME}_o)
add_library(${OBJLIB} OBJECT ${SOURCES})
set_property(TARGET ${OBJLIB} PROPERTY POSITION_INDEPENDENT_CODE 1)

set(LIBRARYSHARED ${PROJECT_NAME})
set(LIBRARYSTATIC ${PROJECT_NAME}_s)

add_library(${LIBRARYSTATIC} STATIC $<TARGET_OBJECTS:${OBJLIB}>)
add_library(${LIBRARYSHARED} SHARED $<TARGET_OBJECTS:${OBJLIB}>)

#------------------------------------------------------------------------------

install(FILES ${INCLUDE} DESTINATION /usr/local/include/)
install(TARGETS ${LIBRARYSHARED} ${LIBRARYSTATIC} DESTINATION /usr/local/lib/)

#------------------------------------------------------------------------------

add_executable(exparser_tests examples/exparser_tests.c)
target_link_libraries(exparser_tests exparser_s m)

add_executable(exparser_example_1 examples/exparser_example_1.c)
target_link_libraries(exparser_example_1 exparser_s m)

add_executable(exparser_example_2 examples/exparser_example_2.c)
target_link_libraries(exparser_example_2 exparser_s m)

add_executable(exparser_shell examples/exparser_shell.c)
target_link_libraries(exparser_shell exparser_s m)
