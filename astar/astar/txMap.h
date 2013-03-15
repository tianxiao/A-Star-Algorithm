#pragma once

enum txEntitiesC
{
	ROAD,
    START,
    GOAL,
    OBSTACLE,
	SHOTEST_PATH,
    NUM_OF_COLORS_IN_E
};


class txMap
{
public:
	txMap(int m, int n);
	~txMap(void);

	void SetIJValue(int i, int j, int v);

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
	void SetStartEndIJ();

private:
	int *map;
	int m;
	int n;

	int startI;
	int startJ;

	int goalI;
	int goalJ;


};

