#include "bots.h"
#include <limits>
#include <utility>
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
	while (closed[gTarget.PositionX()][gTarget.PositionY()] == false)
	{
		float minCost = std::numeric_limits<float>::max();
		int lowestI, lowestJ;
		lowestI = lowestJ = 0;

		for (int i = 0; i < GRIDHEIGHT; i++) {
			for (int j = 0; j < GRIDWIDTH; j++) {
				if (cost[i][j] < minCost && closed[i][j] == false && gLevel.isValid(i,j)) {
					lowestI = i;
					lowestJ = j;
					minCost = cost[i][j];
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

		if (gLevel.isValid(lowestI, lowestJ - 1)
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

void cAStar::Build(cBotBase& bot)
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
	while (closed[gTarget.PositionX()][gTarget.PositionY()] == false)
	{
		float minCost = std::numeric_limits<float>::max();
		int lowestI, lowestJ;
		lowestI = lowestJ = 0;

		for (int i = 0; i < GRIDHEIGHT; i++) {
			for (int j = 0; j < GRIDWIDTH; j++) {
				float euclideanDistance = sqrt(pow(fabs(gTarget.PositionX()) - i, 2) + pow(fabs(gTarget.PositionY() - j), 2));
				// float manhattanDistance = fabs(gTarget.PositionX()-i) + fabs(gTarget.PositionY() -j);
				if (cost[i][j] + euclideanDistance < minCost && closed[i][j] == false && gLevel.isValid(i, j)) {
					lowestI = i;
					lowestJ = j;
					minCost = cost[i][j] + euclideanDistance;
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

		if (gLevel.isValid(lowestI, lowestJ - 1)
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
		coords.push_back(std::make_pair(nextClosedX, nextClosedY));
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) done = true;
	}

	completed = true;
}

cAStar gAStar;