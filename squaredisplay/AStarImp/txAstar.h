#pragma once
#include "stdafx.h"
#include "inoutsymble.h"
#include <list>
#include <vector>

class txMap;
class txNode;

class ASTAR_ALGORITHM_API txAstar
{
public:
	txAstar(txMap *map, int h=10, int v=10, int d=14);
	~txAstar(void);

	void CalculatePath();

	std::vector<int> GetPath() { return path; };

	std::vector<int> GetAccessed() { return accclose; };

private:
	int DiganalHeuristicF(txNode *node);
	txNode *MinNodesInOpennodes();
	void MoveOpen2Close(txNode *node);
	bool IsGoal(txNode *node);
	std::list<txNode*> NodeAdjacent(txNode *node);
	bool IsValid(int i, int j);
	txNode *CreatNode(int i, int j, int edgevalue, txNode *node, std::list<txNode*> &nodelist);
	bool IsExistsEqualBetter(txNode *n, std::list<txNode *> &list);
	void RemoveNode(txNode *n, std::list<txNode*> &nodes);

	void DestryNodes(std::list<txNode*> nodes);

	

private:
	txMap *map;
	std::list<txNode*> opennodes;
	std::list<txNode*> closenodes;

	int hcost;
	int vcost;
	int digcost;

	int maxlen;

	std::vector<int> path;
	std::vector<int> accclose;
	
};

