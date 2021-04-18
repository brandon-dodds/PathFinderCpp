#include "bots.h"
#include <limits>
void cDijkstra::Build(cBotBase& bot) 
{
	for (int i = 0; i < GRIDHEIGHT; i++) {
		for (int j = 0; j < GRIDWIDTH; j++) {
			closed[i][j], inPath[i][j] = false;
			cost[i][j] = std::numeric_limits<float>::max();
			linkX[i][j], linkY[i][j] = -1;
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0;
	while (!completed) 
	{
		int lowestI, lowestJ = 0;
		for (int i = 0; i < GRIDHEIGHT; i++) {
			for (int j = 0; j < GRIDWIDTH; j++) {
				if (cost[i][j] < cost[lowestI][lowestJ]) {
					lowestI = i; 
					lowestJ = j;
				}
			}
		}
		closed[lowestI][lowestJ] = true;
	}
}

