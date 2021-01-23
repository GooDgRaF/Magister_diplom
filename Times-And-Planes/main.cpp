#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Distance between two Points.h>
#include <Functions/Calculate times new plane.h>
#include "Functions/Stage -1.h"

using namespace std;

int main()
    {
        Zone zone;

        string nameOfPointsFile = "../Source information/Points/Test.txt";//KoltsovoStScheme
        string nameOfSchemeFile = "../Source information/Schemes/Test.txt";//KoltsovoStScheme
        string nameOfFlowsFile = "../Source information/Flows/Test.txt";//Koltsovo

        stage_minus_one(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile, zone);


        PlanePoint plane2;
        plane2.x = Distance::createKms(0);
        plane2.y = Distance::createKms(1);
        plane2.z = Distance::createKms(0);
        plane2.V = Velocity::createVkm_h(15);
        plane2.flow_for_plane = "Flow 1";
        plane2.destination = "A2";
        plane2.on_edge = {"A2", "St2"};

        calc_plane(zone, plane2);

        return 0;
    }
