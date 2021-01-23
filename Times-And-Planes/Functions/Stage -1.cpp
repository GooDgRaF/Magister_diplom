//
// Created by Антон on 14.04.2020.
//
#include <Build/Build_graph_of_Zone.h>
#include <Build/Build_Flow.h>
#include <Read/Read_CheckPointsRegExp.h>
#include "Stage -1.h"
#include "Read/Read_SchemesRegExp.h"
#include "Read/Read_FlowsRegExp.h"
#include "Functions/Assistant functions/Topologic_Sort.h"

void stage_minus_one(string &path_checkPointsFile, string &path_SchemesFile, string &path_FlowsFile, Zone &zone)
	{
		Read_CheckPointsRegExp(path_checkPointsFile, zone.checkPoints);
		zone.graph_of_descendants.resize(zone.checkPoints.size());

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
	}

