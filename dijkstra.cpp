#include "bots.h"
#include <limits>
void cDijkstra::Build(cBotBase& bot)
{
	for (int i = 0; i < GRIDHEIGHT; i++) {
		for (int j = 0; j < GRIDWIDTH; j++) {
			closed[i][j] = false;
			inPath[i][j] = false;
			cost[i][j] = std::numeric_limits<float>::max();
			linkX[i][j] = -1;
			linkY[i][j] = -1;
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0;
	while (closed[bot.PositionX()][bot.PositionY()] == false)
	{
		int lowestI, lowestJ;
		lowestI = lowestJ = 0;

		for (int i = 0; i < GRIDHEIGHT; i++) {
			for (int j = 0; j < GRIDWIDTH; j++) {
				if (cost[i][j] < cost[lowestI][lowestJ] && closed[i][j] == false && gLevel.isBlocked(i,j)) {
					lowestI = i;
					lowestJ = j;
				}
			}
		}
		closed[lowestI][lowestJ] = true;

		if (gLevel.isValid(lowestI + 1, lowestJ)
			&& closed[lowestI + 1][lowestJ] == false
			&& cost[lowestI + 1][lowestJ] > cost[lowestI][lowestJ] + 1) {
			cost[lowestI + 1][lowestJ] = cost[lowestI][lowestJ] + 1;
			linkX[lowestI + 1][lowestJ] = lowestI;
			linkY[lowestI + 1][lowestJ] = lowestJ;
		}

		if (gLevel.isValid(lowestI - 1, lowestJ)
			&& closed[lowestI - 1][lowestJ] == false
			&& cost[lowestI - 1][lowestJ] > cost[lowestI][lowestJ] + 1) {
			cost[lowestI - 1][lowestJ] = cost[lowestI][lowestJ] + 1;
			linkX[lowestI - 1][lowestJ] = lowestI;
			linkY[lowestI - 1][lowestJ] = lowestJ;
		}

		if (gLevel.isValid(lowestI, lowestJ + 1)
			&& closed[lowestI][lowestJ + 1] == false
			&& cost[lowestI][lowestJ + 1] > cost[lowestI][lowestJ] + 1) {
			cost[lowestI][lowestJ + 1] = cost[lowestI][lowestJ] + 1;
			linkX[lowestI][lowestJ + 1] = lowestI;
			linkY[lowestI][lowestJ + 1] = lowestJ;
		}

		if (gLevel.isValid(lowestI + 1, lowestJ)
			&& closed[lowestI][lowestJ - 1] == false
			&& cost[lowestI][lowestJ - 1] > cost[lowestI][lowestJ] + 1) {
			cost[lowestI][lowestJ - 1] = cost[lowestI][lowestJ] + 1;
			linkX[lowestI][lowestJ - 1] = lowestI;
			linkY[lowestI][lowestJ - 1] = lowestJ;
		}

		if (gLevel.isValid(lowestI + 1, lowestJ + 1)
			&& closed[lowestI + 1][lowestJ + 1] == false
			&& cost[lowestI + 1][lowestJ + 1] > cost[lowestI][lowestJ] + 1.4f) {
			cost[lowestI + 1][lowestJ + 1] = cost[lowestI][lowestJ] + 1.4f;
			linkX[lowestI + 1][lowestJ + 1] = lowestI;
			linkY[lowestI + 1][lowestJ + 1] = lowestJ;
		}

		if (gLevel.isValid(lowestI - 1, lowestJ - 1)
			&& closed[lowestI - 1][lowestJ - 1] == false
			&& cost[lowestI - 1][lowestJ - 1] > cost[lowestI][lowestJ] + 1.4f) {
			cost[lowestI - 1][lowestJ - 1] = cost[lowestI][lowestJ] + 1.4f;
			linkX[lowestI - 1][lowestJ - 1] = lowestI;
			linkY[lowestI - 1][lowestJ - 1] = lowestJ;
		}

		if (gLevel.isValid(lowestI - 1, lowestJ + 1)
			&& closed[lowestI - 1][lowestJ + 1] == false
			&& cost[lowestI - 1][lowestJ + 1] > cost[lowestI][lowestJ] + 1.4f) {
			cost[lowestI - 1][lowestJ + 1] = cost[lowestI][lowestJ] + 1.4f;
			linkX[lowestI - 1][lowestJ + 1] = lowestI;
			linkY[lowestI - 1][lowestJ + 1] = lowestJ;
		}

		if (gLevel.isValid(lowestI + 1, lowestJ - 1)
			&& closed[lowestI + 1][lowestJ - 1] == false
			&& cost[lowestI + 1][lowestJ - 1] > cost[lowestI][lowestJ] + 1.4f) {
			cost[lowestI + 1][lowestJ - 1] = cost[lowestI][lowestJ] + 1.4f;
			linkX[lowestI + 1][lowestJ - 1] = lowestI;
			linkY[lowestI + 1][lowestJ - 1] = lowestJ;
		}
	}

	bool done = false;
	int nextClosedX = gTarget.PositionX();
	int nextClosedY = gTarget.PositionY();
	while (!done) {
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) done = true;
	}

	completed = true;
}

cDijkstra gDijkstra;
