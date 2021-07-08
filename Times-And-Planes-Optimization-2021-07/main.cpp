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

        string nameOfPointsFile = "../Optimization program/Source information/Points/Test.txt";
        string nameOfSchemeFile = "../Optimization program/Source information/Schemes/Test.txt";
//        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Test.txt";
        
//        string nameOfPointsFile = "../Optimization program/Source information/Points/Koltsovo.txt";
//        string nameOfSchemeFile = "../Optimization program/Source information/Schemes/Koltsovo.txt";
        string nameOfFlowsFile = "../Optimization program/Source information/Flows/Koltsovo.txt";

        read_CheckPoints(nameOfPointsFile);
        read_Schemes(nameOfSchemeFile);
        
        
        
        
        
        
        
        
        
        
        
        zone;
        return 0;
        
    }
