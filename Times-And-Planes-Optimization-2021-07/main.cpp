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
        
        read_checkPoints(path_to_CPointsFile);
        read_schemes(path_to_SchemesFile);
        read_holding_areas(path_to_HoldingAreasFile);
        
        
        
        
        
        
        
        
        
        
        
        zone;
        return 0;
        
    }
