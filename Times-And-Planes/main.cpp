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

        string nameOfPointsFile = "../Source information/Points/Test.txt";//KoltsovoStScheme.txt
        string nameOfSchemeFile = "../Source information/Schemes/Test.txt";//KoltsovoStScheme.txt
        string nameOfFlowsFile = "../Source information/Flows/Test.txt";//Koltsovo

        stage_minus_one(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile, zone);

        PlanePoint plane1;
        plane1.x = Coordinate::createKms(-1);
        plane1.y = Coordinate::createKms(0.5);
        plane1.z = Coordinate::createKms(0);
        plane1.V = Velocity::createVkm_h(13);

        string flow_for_plane1 = "Flow 1", there = "A1";
        pair<string,string> edge_plane = {"A0","A1"};

        PlanePoint plane2;
        plane2.x = Coordinate::createKms(-0.5);
        plane2.y = Coordinate::createKms(1);
        plane2.z = Coordinate::createKms(0);
        plane2.V = Velocity::createVkm_h(13);

        string flow_for_plane2 = "Flow 1", there2 = "A2";
        pair<string,string> edge_plane2 = {"A1","A2"};

        calc_plane(zone, plane1, flow_for_plane1, there, edge_plane);
        zone.flows[0].print_times();

//        calc_plane(zone, plane2, flow_for_plane2, there2, edge_plane2);
//        zone.flows[0].print_times();




        //time_segment()









//		for (auto &flow : zone.flows)
//		{
//			calculateTimes(zone, flow);
//		}

        //zone.print_times();

        //zone.print_not_merged_times();


        return 0;
    }
