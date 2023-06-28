# MIT License
#
# Copyright (c) 2023 Juan Francisco Montilla
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.0.0)
project(x86_Sincless VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# for development it is better OFF to improve compilation times
option(BUILD_DOC "Build Doxygen Documentation" OFF)

find_package(Doxygen)
if (DOXYGEN_FOUND AND BUILD_DOC)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})
    message("Doxygen build started")

    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else (DOXYGEN_FOUND AND BUILD_DOC)
   message("To build the documentation you need to install Doxygen and activate the BUILD_DOC option")
endif (DOXYGEN_FOUND AND BUILD_DOC)

# -pthread for the examples
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -pthread -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=unreachable,address")

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

add_executable(example1 "${CMAKE_CURRENT_SOURCE_DIR}/examples/example1.cpp")
target_link_libraries(example1 ${PROJECT_NAME})

add_executable(example2 "${CMAKE_CURRENT_SOURCE_DIR}/examples/example2.cpp")
target_link_libraries(example2 ${PROJECT_NAME})