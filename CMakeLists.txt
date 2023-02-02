cmake_minimum_required(VERSION 3.5)

project(hilang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hilang main.cpp hilang.h token.cpp lexer.cpp parser.cpp grammar.h util.h ast.h)

install(TARGETS hilang
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
