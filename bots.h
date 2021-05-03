#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include <vector>
class cBotRandom : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cDijkstra
{
public:
	bool closed[GRIDWIDTH][GRIDHEIGHT];
	float cost[GRIDWIDTH][GRIDHEIGHT];
	int linkX[GRIDWIDTH][GRIDHEIGHT];
	int linkY[GRIDWIDTH][GRIDHEIGHT];
	bool inPath[GRIDWIDTH][GRIDHEIGHT];
	bool completed;
	
	virtual void Build(cBotBase& bot);

	cDijkstra() {
		completed = false;
	}
};

class cAStar : public cDijkstra
{
public:
	std::vector<std::pair<int, int>> coords;
	virtual void Build(cBotBase& bot);
};
extern cDijkstra gDijkstra;
extern cAStar gAStar;
