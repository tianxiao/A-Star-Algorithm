#pragma once
#include "inoutsymble.h"

class ASTAR_ALGORITHM_API txNode
{
public:
	txNode(void);
	~txNode(void);

	txNode *parent;

	int i;
	int j;

	int f;
	int g;
	int h;
};

