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
        string nameOfFlowsFile = "../Source information/Flows/Koltsovo.txt";//

        stage_minus_one(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile, zone);

        PlanePoint plane1;
        plane1.x = Coordinate::createKMs(-122);
        plane1.y = Coordinate::createKMs(72);
        plane1.z = Coordinate::createMs(5700);
        plane1.V = Velocity::createVm_s(130);

        string flow_for_plane1 = "Flow 1";

        calc_new_plane(zone,plane1,flow_for_plane1);

        //zone.print_times();






        //time_segment()









//		for (auto &flow : zone.flows)
//		{
//			calculateTimes(zone, flow);
//		}

        //zone.print_times();

        //zone.print_not_merged_times();


        return 0;
    }
