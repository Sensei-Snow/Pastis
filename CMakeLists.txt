cmake_minimum_required(VERSION 4.0)
project(Pastis C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} WIN32
        ${SOURCES}
        src/main.c
        src/clipboard.c
        include/clipboard.h
        src/utils.c
        include/utils.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)