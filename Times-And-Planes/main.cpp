#include <iostream>
#include <Fields of Zone/Maps.h>
#include <Functions/Assistant functions/Distance between two Points.h>
#include <Functions/Calculate times new plane.h>
#include "Read/Read_SchemesRegExp.h"
#include "Zone.h"
#include "Stage -1.h"
#include "Functions/Assistant functions/Nearest point from the center to .h"
#include "Functions/Calculate times.h"

using namespace std;

int main()
    {
        Zone zone;

        string nameOfPointsFile = "../Source information/Points/KoltsovoStScheme.txt";//Test.txt
        string nameOfSchemeFile = "../Source information/Schemes/KoltsovoStScheme.txt";//Test.txt
        string nameOfFlowsFile = "../Source information/Flows/Koltsovo.txt";//Test

        stage_minus_one(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile, zone);

        PlanePoint plane1;
        plane1.x = Coordinate::createKms(-180);
        plane1.y = Coordinate::createKms(100);
        plane1.z = Coordinate::createMs(5700);
        plane1.V = Velocity::createVm_s(138);
        plane1.flow_for_plane = "RALUB";
        plane1.destination = "TUNED";
        plane1.on_edge = {"RALUB", "TUNED"};
//
//        PlanePoint plane2;
//        plane2.x = Coordinate::createKms(-0.5);
//        plane2.y = Coordinate::createKms(1);
//        plane2.z = Coordinate::createKms(0);
//        plane2.V = Velocity::createVkm_h(13);
//        plane2.flow_for_plane = "Flow 1";
//        plane2.destination = "A2";
//        plane2.on_edge = {"A1", "A2"};


        calc_plane(zone, plane1);
//        calc_plane(zone, plane2);
        calculateTimes(zone, zone.flows[0]);
        zone.flows[0].print_times();




        //time_segment()









//		for (auto &flow : zone.flows)
//		{
//			calculateTimes(zone, flow);
//		}

        //zone.print_times();

        //zone.print_not_merged_times();


        return 0;
    }
