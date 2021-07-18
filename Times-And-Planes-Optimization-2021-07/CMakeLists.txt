cmake_minimum_required(VERSION 3.15)
project(Times-And-Planes-Optimization-2021-07)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Times-And-Planes-Optimization-2021-07
        main.cpp

        "Optimization program/Flow.cpp" "Optimization program/Flow.h" "Optimization program/Fields of Zone/Fields of Flow.h"
        "Optimization program/Measure units/Measure units.h" "Optimization program/Measure units/Measure units.cpp"


        "Optimization program/Read/Read.cpp" "Optimization program/Read/Read.h" "Optimization program/Errors/Errors.h"
        "Optimization program/Build/Build.cpp" "Optimization program/Build/Build.h"
        "Optimization program/Fields of Zone/Fields of Flow.cpp"
        "Optimization program/Flow.cpp")


target_include_directories(Times-And-Planes-Optimization-2021-07 PUBLIC C:/gurobi912/win64/include)
target_link_directories(Times-And-Planes-Optimization-2021-07 PUBLIC C:/gurobi912/win64/lib)
target_link_libraries(Times-And-Planes-Optimization-2021-07 gurobi_c++ gurobi91)