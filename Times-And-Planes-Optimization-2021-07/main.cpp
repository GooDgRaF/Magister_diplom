#include <Optimization program/Build/Build.h>
#include "iostream"
#include "Optimization program/Measure units/Measure units.h"
#include "Optimization program/Zone.h"
#include "Optimization program/Read/Read.h"
using namespace std;

int main()
{
//        Distance a{30,"m"}, b{9,"m"};
//        cout << (a-b).meter << endl;

//        Velocity v{10,"m_s"}, va{20,"m_s"};
//        cout << (v+va).meters_per_second << endl;
    
//    Coordinate a{1}, b{4}, c{5,"km"};

    Time sec{5,"s"}; //hmmm
    
    string path_to_CPointsFile = "../Optimization program/Source information/Points/Test.txt";
    string path_to_HoldingAreasFile = "../Optimization program/Source information/Schemes/Test_hA.txt";
    string path_to_SchemesFile = "../Optimization program/Source information/Schemes/Test.txt";
//        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Test.txt";

//        string nameOfPointsFile = "../Optimization program/Source information/Points/Koltsovo.txt";
//        string nameOfSchemeFile = "../Optimization program/Source information/Schemes/Koltsovo.txt";
//        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Koltsovo.txt";
    
    fill_Zone(path_to_CPointsFile, path_to_HoldingAreasFile, path_to_SchemesFile);
    
    print_Zone();
    
    map<int, int> linearZone{
            {0, 1},
            {1, 2},
            {2, 3},
            {3,  4},
            {4,  5},
            {5,  6},
            {6,  7},
            {7,  8},
            {8,  9},
            {9,  10},
            {10, 11},
            {11, 12},
            {12, 13},
            {13, 14},
            {14, 15},
            {15, 16}};
    
    Velocity v0{500, "km_h"};
    isBetter(linearZone, 0, 16, 0, v0.meters_per_second, 12000);
//        map<int,int> tmp{};
//        calc_best_trajectory(zone.trjs, 0, 16);
//
//        for (const auto &trj : zone.trjs)
//        {
//            cout<< "Trj:"<<endl;
//            for (const auto &[parent, son] : trj)
//            {
//                cout << zone.checkPoints[parent].name << " --> "
//                     <<zone.checkPoints[son].name << endl;
//            }
//        }
    
    
    
    
    
    
    
    zone;
    return 0;
}
