cmake_minimum_required(VERSION 3.15)
project(Assignment_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Assignment_2 main.c)

find_package(OpenMP REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenMP_C_LIBRARIES})