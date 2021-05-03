#include "bots.h"

void cAStarBot::ChooseNextGridPosition()
{
	if (!gAStar.coords.empty()) {
		for (int i = 0; i < gAStar.coords.size(); i++)
		{
			int nextX = gAStar.coords[i].first;
			int nextY = gAStar.coords[i].second;
			SetNext(nextX, nextY, gLevel);
		}
	}
}