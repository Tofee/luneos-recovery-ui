cmake_minimum_required(VERSION 3.10)
project(luneos-recovery-ui)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE INCLUDES "*.h" "../recovery/ui/*.h" )
file(GLOB_RECURSE SOURCES  "*.c" "../recovery/ui/*.c" )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

add_compile_definitions(LV_CONF_INCLUDE_SIMPLE=1)

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(luneos-recovery-ui ${SOURCES} ${INCLUDES})
target_link_libraries(luneos-recovery-ui PRIVATE SDL2 )
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/luneos-recovery-ui)
