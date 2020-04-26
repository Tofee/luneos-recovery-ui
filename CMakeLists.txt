cmake_minimum_required(VERSION 3.5)

project(luneos_recovery_ui LANGUAGES C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(".")

add_executable(luneos_recovery_ui main.c)
target_link_libraries(luneos_recovery_ui liblvgl.a libdrivers.a)

install(TARGETS luneos_recovery_ui RUNTIME)
