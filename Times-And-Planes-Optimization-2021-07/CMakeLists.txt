cmake_minimum_required(VERSION 3.15)
project(Times-And-Planes-2021-06)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Times-And-Planes-Optimization-2021-07
        main.cpp
        "Algorithmic program/Fields of Zone/Point.h"
        "Algorithmic program/Fields of Zone/Flow.h"
        "Algorithmic program/Fields of Zone/Maps.h" "Algorithmic program/Fields of Zone/Maps.cpp"
        "Algorithmic program/Read/Read_SchemesRegExp.cpp" "Algorithmic program/Read/Read_SchemesRegExp.h"
        "Algorithmic program/Fields of Zone/Scheme.h"
        "Algorithmic program/Build/Build_graph_of_Zone.cpp" "Algorithmic program/Build/Build_graph_of_Zone.h"
        "Algorithmic program/Functions/Assistant functions/Topologic_Sort.cpp" "Algorithmic program/Functions/Assistant functions/Topologic_Sort.h"
        "Algorithmic program/Zone.h" "Algorithmic program/Zone.cpp"
        "Algorithmic program/Build/Build_Flow.cpp" "Algorithmic program/Build/Build_Flow.h"
        "Algorithmic program/Build/Create_Zone.cpp"        "Algorithmic program/Build/Create_Zone.h"
        "Algorithmic program/Functions/Times functions/Calculate_times.cpp"        "Algorithmic program/Functions/Times functions/Calculate_times.h"
        "Algorithmic program/Functions/Times functions/MergeTimes.cpp" "Algorithmic program/Functions/Times functions/MergeTimes.h"
        "Algorithmic program/Measure units/Distance.cpp"        "Algorithmic program/Measure units/Distance.h"
        "Algorithmic program/Measure units/Velocity.cpp"        "Algorithmic program/Measure units/Velocity.h"
        "Algorithmic program/Measure units/Time.cpp"        "Algorithmic program/Measure units/Time.h"
        "Algorithmic program/Measure units/MeasureUnits.h"
        "Algorithmic program/Read/Read_CheckPointsRegExp.cpp" "Algorithmic program/Read/Read_CheckPointsRegExp.h"
        "Algorithmic program/Fields of Zone/Waiting area.h"
        "Algorithmic program/Functions/Geometric functions/Calculate standard scheme.cpp"        "Algorithmic program/Functions/Geometric functions/Calculate standard scheme.h"
        "Algorithmic program/Read/Read_FlowsRegExp.cpp" "Algorithmic program/Read/Read_FlowsRegExp.h" "Algorithmic program/Functions/Geometric functions/Nearest point from the center to .cpp" "Algorithmic program/Functions/Geometric functions/Nearest point from the center to .h" "Algorithmic program/Functions/Geometric functions/Distance between two Points.cpp" "Algorithmic program/Functions/Geometric functions/Distance between two Points.h" "Algorithmic program/Functions/Calculate times new plane.cpp" "Algorithmic program/Functions/Calculate times new plane.h" "Algorithmic program/Fields of Zone/Flow.cpp" "Algorithmic program/Functions/Geometric functions/Arc length.cpp" "Algorithmic program/Functions/Geometric functions/Arc length.h" "Algorithmic program/Functions/Times functions/Initialization of time segments.cpp" "Algorithmic program/Functions/Times functions/Initialization of time segments.h" "Algorithmic program/Functions/Times functions/Calc time segments for StScheme.cpp" "Algorithmic program/Functions/Times functions/Calc time segments for StScheme.h" "Algorithmic program/Functions/Times functions/Plane enum.h" "Algorithmic program/Build/Build_constricted_Zone.cpp" "Algorithmic program/Build/Build_constricted_Zone.h" "Algorithmic program/Functions/Output functions/Constricted zone.cpp" "Algorithmic program/Functions/Output functions/Constricted zone.h" "Algorithmic program/Functions/Times functions/Backward propagation.cpp" "Algorithmic program/Functions/Times functions/Backward propagation.h" "Algorithmic program/Functions/Assistant functions/Read and build.cpp" "Algorithmic program/Functions/Assistant functions/Read and build.h")
