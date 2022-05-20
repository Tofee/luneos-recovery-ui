cmake_minimum_required(VERSION 3.5)

project(luneos_recovery_ui LANGUAGES C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(".")

file(GLOB_RECURSE UI_FILES "ui/*.h" "ui/*.c" )

add_executable(luneos_recovery_ui main.c ${UI_FILES})
target_link_libraries(luneos_recovery_ui liblvgl.a liblv_drivers.a)

install(TARGETS luneos_recovery_ui RUNTIME)
