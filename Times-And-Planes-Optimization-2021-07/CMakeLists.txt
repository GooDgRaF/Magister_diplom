cmake_minimum_required(VERSION 3.15)
project(Times-And-Planes-Optimization-2021-07)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Times-And-Planes-Optimization-2021-07
        main.cpp

        "Optimization program/Zone.cpp" "Optimization program/Zone.h" "Optimization program/Fields of Zone/Fields of Zone.h"
        "Optimization program/Measure units/Measure units.h" "Optimization program/Measure units/Measure units.cpp"


        "Optimization program/Read/Read.cpp" "Optimization program/Read/Read.h" "Optimization program/Read/Assistant.h" "Optimization program/Errors/Errors.h")


target_include_directories(Times-And-Planes-Optimization-2021-07 PRIVATE "/opt/gurobi911/include")
target_link_directories(Times-And-Planes-Optimization-2021-07 PRIVATE "/opt/gurobi911/lib")
target_link_libraries(Times-And-Planes-Optimization-2021-07 gurobi_c++)
target_link_libraries(Times-And-Planes-Optimization-2021-07 gurobi91)