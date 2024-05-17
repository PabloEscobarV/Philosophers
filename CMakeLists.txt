# cmake_minimum_required(VERSION 2.8)

# set(NAME philosophers)
# set(SOURCE_DIR src)
# set(HEADER_DIRS hdrs)

# project(${NAME})

# include_directories(${HEADER_DIRS})

# set(SOURCES
#     ${SOURCE_DIR}/alkash.cpp
#     ${SOURCE_DIR}/buchlo.cpp
#     ${SOURCE_DIR}/taskplanner.cpp
#     ${SOURCE_DIR}/test.cpp
#     )

# add_executable(NAME ${SOURCES})
cmake_minimum_required(VERSION 2.8)

# Set project name
set(NAME philosophers)

# Set source and header directories
set(SOURCE_DIR src)
set(HEADER_DIRS hdrs)

# Define project
project(${NAME})

# Include header directories
include_directories(${HEADER_DIRS})

# Define source files
# set(SOURCES
#     ${SOURCE_DIR}/alkash.cpp
#     ${SOURCE_DIR}/buchlo.cpp
#     ${SOURCE_DIR}/taskplanner.cpp
#     ${SOURCE_DIR}/test.cpp
# )
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${SOURCE_DIR}/*.c)

# Create executable from source files
add_executable(${NAME} ${SOURCES})

add_custom_target(fclean
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*
    COMMENT "Cleaning up build directory"
)
