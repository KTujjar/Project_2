cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project2)

add_executable(MyProgram)

target_sources(MyProgram
    PRIVATE
        src/app/main.cpp
)