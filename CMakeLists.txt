cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Project2)

add_executable(MyProgram)

target_include_directories(MyProgram PRIVATE src)
find_package(glm REQUIRED)
target_link_libraries(MyProgram PRIVATE glm::glm)

target_sources(MyProgram
    PRIVATE
        src/app/main.cpp
)