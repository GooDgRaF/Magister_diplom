#include <Optimization program/Build/Build.h>
#include "iostream"
#include "Optimization program/Measure units/Measure units.h"
#include "Optimization program/Flow.h"
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
    
    build_Flow(path_to_CPointsFile, path_to_HoldingAreasFile, path_to_SchemesFile);
    
    print_hull();
    print_graph();
    
    
    calc_best_trajectory(flow.trjs, 0, 15);
    
    for (const auto &trj : flow.trjs)
        {
            cout<< "Trj:"<<endl;
            for (const auto &[parent, son] : trj)
            {
                cout << flow.graph[parent].name << " --> "
                     <<flow.graph[son].name << endl;
            }
        }
    
    Velocity v0{500, "km_h"};
    isBetter(flow.trjs[0], 0, 15, 0, v0.m_s(), 12000);
    
    
    
    
    
    
    
    
    flow;
    return 0;
}
