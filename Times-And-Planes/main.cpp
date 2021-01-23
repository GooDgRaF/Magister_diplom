#include <iostream>
#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Distance between two Points.h>
#include <Functions/Calculate times new plane.h>
#include "Read/Read_SchemesRegExp.h"
#include "Zone.h"
#include "Functions/Stage -1.h"
#include "Functions/Geometric functions/Nearest point from the center to .h"
#include "Functions/Times functions/Calculate times.h"

using namespace std;

int main()
    {
        Zone zone;

        string nameOfPointsFile = "../Source information/Points/Test.txt";//KoltsovoStScheme
        string nameOfSchemeFile = "../Source information/Schemes/Test.txt";//KoltsovoStScheme
        string nameOfFlowsFile = "../Source information/Flows/Test.txt";//Koltsovo

        stage_minus_one(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile, zone);

//        PlanePoint plane1;
//        plane1.x = Distance::createKms(-180);
//        plane1.y = Distance::createKms(100);
//        plane1.z = Distance::createMs(5700);
//        plane1.V = Velocity::createVm_s(138);
//        plane1.flow_for_plane = "RALUB";
//        plane1.destination = "TUNED";
//        plane1.on_edge = {"RALUB", "TUNED"};
//
        PlanePoint plane2;
        plane2.x = Distance::createKms(-1.25);
        plane2.y = Distance::createKms(1.25);
        plane2.z = Distance::createKms(0);
        plane2.V = Velocity::createVkm_h(10);
        plane2.flow_for_plane = "Flow 1";
        plane2.destination = "A2";
        plane2.on_edge = {"A1", "A2"};





        calc_plane(zone, plane2);




//        calc_plane(zone, plane2);
 //       calculateTimes(zone.flows[0], zone, <#initializer#>, 0, 0);
   //    zone.flows[0].print_times();






//		for (auto &flow : zone.flows)
//		{
//			calculateTimes(zone, flow);
//		}

        //zone.print_times();

        //zone.print_not_merged_times();


        return 0;
    }
