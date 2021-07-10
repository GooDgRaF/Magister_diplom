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



        string path_to_CPointsFile = "../Optimization program/Source information/Points/Test.txt";
        string path_to_HoldingAreasFile = "../Optimization program/Source information/Schemes/Test_hA.txt";
        string path_to_SchemesFile = "../Optimization program/Source information/Schemes/Test.txt";
//        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Test.txt";
        
//        string nameOfPointsFile = "../Optimization program/Source information/Points/Koltsovo.txt";
//        string nameOfSchemeFile = "../Optimization program/Source information/Schemes/Koltsovo.txt";
//        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Koltsovo.txt";
        
        fill_Zone(path_to_CPointsFile, path_to_HoldingAreasFile, path_to_SchemesFile);
        
        print_Zone();
        
        map<int,int> tmp{};
        calc_best_trajectory(tmp,0, 2);
        
        for (const auto &trj : zone.trjs)
        {
            cout<< "Trj:"<<endl;
            for (const auto &[parent, son] : trj)
            {
                cout << zone.checkPoints[parent].name << " --> "
                     <<zone.checkPoints[son].name << endl;
            }
        }
        
        
        
        
        
        
        
        zone;
        return 0;
        
    }
