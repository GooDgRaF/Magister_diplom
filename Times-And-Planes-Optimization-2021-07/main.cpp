#include "iostream"
#include "Optimization program/Measure units/Measure units.h"
#include "Optimization program/Zone.h"
#include "Optimization program/Read/Read points.h"

using namespace std;

int main()
    {
//        Distance a{30,"m"}, b{9,"m"};
//        cout << (a-b).meter << endl;
        
//        Velocity v{10,"m_s"}, va{20,"m_s"};
//        cout << (v+va).meters_per_second << endl;

//        string nameOfPointsFile = "../Optimization program/Source information/Points/Test.txt";
//        string nameOfSchemeFile = "../Optimization program/Source information/Schemes/Test.txt";
//        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Test.txt";
        
        string nameOfPointsFile = "../Optimization program/Source information/Points/Koltsovo.txt";
        string nameOfSchemeFile = "../Optimization program/Source information/Schemes/Koltsovo.txt";
        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Koltsovo.txt";

        read_CheckPoints(nameOfPointsFile);
    zone;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
////        TS a{0, 10}, b{2,4}, c{15,20,"h"},
////           z{1,3}, x{5,9}, v{8,30, "h"};
////        vector<TS> v1{a,b,c}, v2{z,x,v};
////        auto res = intersection_vTS(v1,v2);
////        for (const auto &el : res)
////        {
////            cout <<" " << el << endl;
////        }
//
//
//
//
//
//
//
//        string nameOfPointsFile = "../Source information/Points/Test.txt";
//        string nameOfSchemeFile = "../Source information/Schemes/Test.txt";//NameSt (St1)(2): St1 St2 St3 St4a
//        string nameOfFlowsFile = "../Source information/Flows/Test.txt";
//
////        string nameOfPointsFile = "../Source information/Points/KoltsovoStScheme.txt";
////        string nameOfSchemeFile = "../Source information/Schemes/Koltsovo.txt";
////        string nameOfFlowsFile = "../Source information/Flows/Koltsovo.txt";
//
//        Zone zone = create_zone(nameOfPointsFile, nameOfSchemeFile, nameOfFlowsFile);
////        out_constricted_zone(zone);
//
//
////zone.print_flows_as_string_anc();
////zone.print_flows_as_string_des();
////       zone.print_constricted_TS();
//
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
////       zone.print_times();















        return 0;
        
    }
