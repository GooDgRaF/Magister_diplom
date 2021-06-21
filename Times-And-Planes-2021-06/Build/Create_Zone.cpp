//
// Created by Антон on 14.04.2020.
//
#include <Build/Build_graph_of_Zone.h>
#include <Build/Build_Flow.h>
#include <Read/Read_CheckPointsRegExp.h>
#include <Functions/Times functions/Calculate_times.h>
#include "Create_Zone.h"
#include "Read/Read_SchemesRegExp.h"
#include "Read/Read_FlowsRegExp.h"
#include "Functions/Assistant functions/Topologic_Sort.h"
#include "Build/Build_constricted_Zone.h"


using namespace std;

Zone create_zone(std::string &path_checkPointsFile, std::string &path_SchemesFile, std::string &path_FlowsFile)
	{
	    Zone zone;

		Read_CheckPointsRegExp(path_checkPointsFile, zone.checkPoints);
		zone.graph.resize(zone.checkPoints.size());

        Read_SchemesRegExp(path_SchemesFile, zone.checkPoints, zone.schemes, zone.standardSchemes);

        Read_FlowsRegExp(path_FlowsFile, zone.flows);
		
		Build_graph_of_Zone(zone);
		
		for (auto &flow : zone.flows)
		{
			Build_Flow(zone, flow);
		}
		
		for (auto &flow : zone.flows)
		{
			topologicalSort_of_flow(flow);
		}
        
        build_constricted_Zone(zone);
        
        calc_TS_edges_of_constricted_zone(zone);

        return zone;
	}


