cmake_minimum_required(VERSION 3.15)
project(Times_And_Planes)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Times_And_Planes
        main.cpp
        "Fields of Zone/Point.h"
        "Fields of Zone/Flow.h"
        "Functions/Assistant functions/OpenFile.cpp" "Functions/Assistant functions/OpenFile.h"
        "Fields of Zone/Maps.h" "Fields of Zone/Maps.cpp"
        Read/Read_SchemesRegExp.cpp Read/Read_SchemesRegExp.h
        "Fields of Zone/Scheme.h"
        "Functions/Assistant functions/Fill-scheme.cpp" "Functions/Assistant functions/Fill-scheme.h"
        Build/Build_graph_of_Zone.cpp Build/Build_graph_of_Zone.h
        "Functions/Assistant functions/Find-InVector-bool.h"
        "Functions/Assistant functions/Topologic_Sort.cpp" "Functions/Assistant functions/Topologic_Sort.h"
        Zone.h        Zone.cpp
        Build/Build_Flow.cpp        Build/Build_Flow.h
        "Stage -1.cpp"        "Stage -1.h"
        "Functions/Times functions/Calculate times.cpp"        "Functions/Times functions/Calculate times.h"
        "Functions/Times functions/MergeTimes.cpp" "Functions/Times functions/MergeTimes.h"
        "Measure units/Distance.cpp"        "Measure units/Distance.h"
        "Measure units/Velocity.cpp"        "Measure units/Velocity.h"
        "Measure units/Time.cpp"        "Measure units/Time.h"
        "Measure units/MeasureUnits.h"
        Read/Read_CheckPointsRegExp.cpp        Read/Read_CheckPointsRegExp.h
        "Fields of Zone/StandardScheme.h"
        "Functions/Geometric functions/Calculate standard scheme.cpp"        "Functions/Geometric functions/Calculate standard scheme.h"
        Read/Read_FlowsRegExp.cpp Read/Read_FlowsRegExp.h "Functions/Geometric functions/Nearest point from the center to .cpp" "Functions/Geometric functions/Nearest point from the center to .h" "Functions/Geometric functions/Distance between two Points.cpp" "Functions/Geometric functions/Distance between two Points.h" "Functions/Calculate times new plane.cpp" "Functions/Calculate times new plane.h" "Fields of Zone/Flow.cpp" "Functions/Assistant functions/Fill checkPoint coordinate and velocity.cpp" "Functions/Assistant functions/Fill checkPoint coordinate and velocity.h" "Functions/Assistant functions/Hesh mu_vector.cpp" "Functions/Assistant functions/Hesh mu_vector.h" "Functions/Geometric functions/Arc length.cpp" "Functions/Geometric functions/Arc length.h" "Functions/Times functions/Time segment from point to checkPoint.cpp" "Functions/Times functions/Time segment from point to checkPoint.h" "Functions/Times functions/Initialization of time segments.cpp" "Functions/Times functions/Initialization of time segments.h" "Functions/Times functions/Arc time.cpp" "Functions/Times functions/Arc time.h")
