#pragma once
#include "inoutsymble.h"

enum txEntitiesC
{
	ROAD,
    START,
    GOAL,
    OBSTACLE,
	SHOTEST_PATH,
    NUM_OF_COLORS_IN_E
};


class ASTAR_ALGORITHM_API txMap
{
public:
	txMap(int m, int n);
	~txMap(void);

	// If the user use the i,j or i to set the map value
	// He is responsible to call the SetStartEndIJ() value!
	// whereas the user use the SetMap is unnecessary!
	void SetIJValue(int i, int j, int v);
	void SetValue(int i, int v);
	void SetStartEndIJ();

	int GetIJValue(int i, int j);

	void SetMap(int *mp);

	int GetNumRow() { return m; };
	int GetNumColumn() {return n; };

	int GetStartI() { return startI; };
	int GetStartJ() { return startJ; };
	int GetGoalI() { return goalI; };
	int GetGoalJ() { return goalJ; };

private:
	void DestroyMap();

private:
	int *map;
	int m;
	int n;

	int startI;
	int startJ;

	int goalI;
	int goalJ;


};

