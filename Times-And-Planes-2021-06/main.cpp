#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Distance between two Points.h>
#include <Functions/Calculate times new plane.h>
#include "Functions/Create_Zone.h"

using namespace std;

int main()
    {

        string nameOfPointsFile = "../Source information/Points/Test.txt";//KoltsovoStScheme
        string nameOfSchemeFile = "../Source information/Schemes/Test.txt";//KoltsovoStScheme
        string nameOfFlowsFile = "../Source information/Flows/Test.txt";//Koltsovo

        Zone zone = create_zone(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile);


        PlanePoint plane1;
        plane1.x = Distance::createKm(-40);
        plane1.y = Distance::createKm(35);
        plane1.z = Distance::createKm(2);
        plane1.V = Velocity::createVkm_h(400);
        plane1.flow_for_plane = "Flow 1";
        plane1.destination = "P2";
        plane1.on_edge = {"P1", "St4"};

        PlanePoint plane2;
        plane2.x = Distance::createKm(-55);
        plane2.y = Distance::createKm(121);
        plane2.z = Distance::createKm(2);
        plane2.V = Velocity::createVkm_h(400);
        plane2.flow_for_plane = "Flow 1";
        plane2.destination = "St3";
        plane2.on_edge = {"St2", "St3"};
//        plane2.destination = "A2";
//        plane2.on_edge = {"A2", "St2"};

        vector<int> ID_points_to_calculate = {};
        map<int, vector<pair<double, double>>> res;
        map<int, vector<pair<pair<double, double>, int>>> not_merged_res;//Вершина --> { ([t1,t2], parent) ... ([tn-1,tn], parent) }

        calc_plane(zone, plane2, res, not_merged_res, ID_points_to_calculate);

        for (auto &el : res)
        {
            cout << zone.checkPoints[el.first].name << ": ";
            for (auto &ts : el.second)
            {
                cout << "[" << round(ts.first) << ", " << round(ts.second) << "] ";
            }
            cout << "\\\\" << endl;
        }

        cout << endl << "NOT MERGED:" << endl;

        for (auto &el : not_merged_res)
        {
            cout << zone.checkPoints[el.first].name << ": ";
            for (auto &ts : el.second)
            {
                cout << "[" << round(ts.first) << ", " << round(ts.second) << "] ";
            }
            cout << "\\\\" << endl;
        }
        return 0;
    }
