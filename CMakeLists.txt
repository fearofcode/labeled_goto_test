cmake_minimum_required(VERSION 3.17)
project(labeled_goto_test)

set(CMAKE_CXX_STANDARD 20)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(labeled_goto_test main.cpp)
target_link_libraries(labeled_goto_test ${CONAN_LIBS})