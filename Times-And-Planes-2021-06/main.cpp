#include <Fields of Zone/Maps.h>
#include <Functions/Geometric functions/Distance between two Points.h>
#include <Functions/Calculate times new plane.h>
#include <Functions/Times functions/Calculate_times.h>
#include <Functions/Output functions/Constricted zone.h>
#include <Functions/Times functions/Backward propagation.h>
#include "Build/Create_Zone.h"

using namespace std;

int main()
    {
//        TS a{0, 10}, b{2,4}, c{15,20,"h"},
//           z{1,3}, x{5,9}, v{8,30, "h"};
//        vector<TS> v1{a,b,c}, v2{z,x,v};
//        auto res = intersection_vTS(v1,v2);
//        for (const auto &el : res)
//        {
//            cout <<" " << el << endl;
//        }


        
        
        
        
    
        string nameOfPointsFile = "../Source information/Points/Test.txt";
        string nameOfSchemeFile = "../Source information/Schemes/Test.txt";//NameSt (St1)(2): St1 St2 St3 St4a
        string nameOfFlowsFile = "../Source information/Flows/Test.txt";

//        string nameOfPointsFile = "../Source information/Points/KoltsovoStScheme.txt";
//        string nameOfSchemeFile = "../Source information/Schemes/Koltsovo.txt";
//        string nameOfFlowsFile = "../Source information/Flows/Koltsovo.txt";

        Zone zone = create_zone(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile);
//        out_constricted_zone(zone);


//zone.print_flows_as_string_anc();
//zone.print_flows_as_string_des();
//       zone.print_constricted_TS();

//        auto times = zone.flows[0].times; times.clear();
//        auto u = zone.flows[0].not_merged_times;
//        calc_TimeSegments(zone.flows[0], zone.checkPoints, zone.waitingAreas, times, u);
//
//        for (auto &[ID, tss] : times)
//        {
//            cout << zone.checkPoints[ID].name << " --> ";
//            for (auto &ts : tss)
//            {
//                cout << "[" << ts.min << ", " << ts.max << "] ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//
//       auto res = backward_propagation(zone, 0, TS(3600,5000).min);
       zone.print_times();




















//
//        PlanePoint plane1;
//        plane1.x = Distance::createKm(-40);
//        plane1.y = Distance::createKm(35);
//        plane1.z = Distance::createKm(2);
//        plane1.V = Velocity::createVkm_h(400);
//        plane1.flow_for_plane = "Flow 1";
//        plane1.destination = "P2";
//        plane1.on_edge = {"P1", "St4"};
//
//        PlanePoint plane2;
//        plane2.x = Distance::createKm(-55);
//        plane2.y = Distance::createKm(121);
//        plane2.z = Distance::createKm(2);
//        plane2.V = Velocity::createVkm_h(400);
//        plane2.flow_for_plane = "Flow 1";
//        plane2.destination = "St3";
//        plane2.on_edge = {"St2", "St3"};
//        plane2.destination = "A2";
//        plane2.on_edge = {"A2", "St2"};

//        vector<int> ID_points_to_calculate = {};
//        map<int, vector<pair<double, double>>> res;
//        map<int, vector<pair<pair<double, double>, int>>> not_merged_res;//Вершина --> { ([t1,t2], parent) ... ([tn-1,tn], parent) }
//
//        calc_plane(zone, plane2, res, not_merged_res, ID_points_to_calculate);
        return 0;
        
    }
