cmake_minimum_required(VERSION 3.15)
project(Times-And-Planes-2021-06)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Times-And-Planes-2021-06
        main.cpp
        "Fields of Zone/Point.h"
        "Fields of Zone/Flow.h"
        "Fields of Zone/Maps.h" "Fields of Zone/Maps.cpp"
        Read/Read_SchemesRegExp.cpp Read/Read_SchemesRegExp.h
        "Fields of Zone/Scheme.h"
        Build/Build_graph_of_Zone.cpp Build/Build_graph_of_Zone.h
        "Functions/Assistant functions/Topologic_Sort.cpp" "Functions/Assistant functions/Topologic_Sort.h"
        Zone.h        Zone.cpp
        Build/Build_Flow.cpp        Build/Build_Flow.h
        "Build/Create_Zone.cpp"        "Build/Create_Zone.h"
        "Functions/Times functions/Calculate_times.cpp"        "Functions/Times functions/Calculate_times.h"
        "Functions/Times functions/MergeTimes.cpp" "Functions/Times functions/MergeTimes.h"
        "Measure units/Distance.cpp"        "Measure units/Distance.h"
        "Measure units/Velocity.cpp"        "Measure units/Velocity.h"
        "Measure units/Time.cpp"        "Measure units/Time.h"
        "Measure units/MeasureUnits.h"
        Read/Read_CheckPointsRegExp.cpp        Read/Read_CheckPointsRegExp.h
        "Fields of Zone/Waiting area.h"
        "Functions/Geometric functions/Calculate standard scheme.cpp"        "Functions/Geometric functions/Calculate standard scheme.h"
        Read/Read_FlowsRegExp.cpp Read/Read_FlowsRegExp.h "Functions/Geometric functions/Nearest point from the center to .cpp" "Functions/Geometric functions/Nearest point from the center to .h" "Functions/Geometric functions/Distance between two Points.cpp" "Functions/Geometric functions/Distance between two Points.h" "Functions/Calculate times new plane.cpp" "Functions/Calculate times new plane.h" "Fields of Zone/Flow.cpp" "Functions/Geometric functions/Arc length.cpp" "Functions/Geometric functions/Arc length.h" "Functions/Times functions/Initialization of time segments.cpp" "Functions/Times functions/Initialization of time segments.h" "Functions/Times functions/Calc time segments for StScheme.cpp" "Functions/Times functions/Calc time segments for StScheme.h" "Functions/Times functions/Plane enum.h" Build/Build_constricted_Zone.cpp Build/Build_constricted_Zone.h "Functions/Output functions/Constricted zone.cpp" "Functions/Output functions/Constricted zone.h" "Functions/Times functions/Backward propagation.cpp" "Functions/Times functions/Backward propagation.h" "Functions/Assistant functions/Read and build.cpp" "Functions/Assistant functions/Read and build.h")
