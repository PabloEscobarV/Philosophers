cmake_minimum_required(VERSION 2.8)
set(NAME philosophers)
set(HEADERDIR hdrs)
set(SOURCEDIR src)
project(${NAME})
include_directories(${HEADERDIR})
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${SOURCEDIR}/*.c)
add_executable(${NAME} ${SOURCES})