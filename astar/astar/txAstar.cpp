#include "StdAfx.h"
#include <assert.h>

#include "txAstar.h"
#include "txMap.h"
#include "txNode.h"


txAstar::txAstar(txMap *map, int h, int v, int d)
	:hcost(h)
	,vcost(v)
	,digcost(d)
{
	this->map = map;
	maxlen = map->GetNumRow()*hcost + map->GetNumColumn()*vcost;
}

txAstar::~txAstar(void)
{
	DestryNodes(opennodes);
	DestryNodes(closenodes);
}

void txAstar::DestryNodes(std::list<txNode*> nodes)
{
	for (std::list<txNode*>::iterator it=nodes.begin(); it!=nodes.end(); it++)
	{
		delete (*it);
		*it = NULL;
	}
}

void txAstar::CalculatePath()
{
	txNode *startnode = new txNode;
	startnode->i = map->GetStartI();
	startnode->j = map->GetStartJ();
	startnode->g = 0;
	startnode->h = DiganalHeuristicF(startnode);
	startnode->f = startnode->g + startnode->h;
	startnode->parent = NULL;

	opennodes.push_back(startnode);

	txNode *goal;

	while (opennodes.size())
	{
		txNode *node = MinNodesInOpennodes();

		MoveOpen2Close(node);

		if (IsGoal(node))
		{
			goal = node;
			break;
		}

		std::list<txNode*> adj;
		adj = NodeAdjacent(node);

		for (std::list<txNode*>::iterator it=adj.begin(); it!=adj.end(); it++)
		{
			if (IsExistsEqualBetter(*it, opennodes)) continue;
			if (IsExistsEqualBetter(*it, closenodes)) continue;

			RemoveNode(*it, opennodes);
			RemoveNode(*it, closenodes);

			opennodes.push_back(*it);
		}
	}

	goal = goal->parent;
	while (goal->parent!=NULL)
	{
		path.push_back(goal->i);
		path.push_back(goal->j);
		goal = goal->parent;
	}

}

int txAstar::DiganalHeuristicF(txNode *node)
{
	double xl=node->i-map->GetGoalI();
	double yl=node->j-map->GetGoalJ();

	return (int) (sqrt(xl*xl+yl*yl)*hcost);
}

txNode *txAstar::MinNodesInOpennodes()
{
	assert(opennodes.size());
	int min = maxlen;
	txNode *rtn=NULL;

	for ( std::list<txNode*>::iterator it=opennodes.begin(); it!=opennodes.end(); it++)
	{
		if (min>(*it)->f)
		{
			min = (*it)->f;
			rtn = *it;
		}
	}

	assert(rtn);
	return rtn;
}

void txAstar::MoveOpen2Close(txNode *n)
{
	std::list<txNode*>::iterator it;
	for (it=opennodes.begin(); it!=opennodes.end();)
	{
		if (n->i==(*it)->i&&n->j==(*it)->j)
		{
			it = opennodes.erase(it);
		}
		else
		{
			it++;
		}
	}

	closenodes.push_back(n);
}

bool txAstar::IsGoal(txNode *n)
{
	if (n->i==map->GetGoalI()&&n->j==map->GetGoalJ())
	{
		return true;
	}

	return false;
}

std::list<txNode*> txAstar::NodeAdjacent(txNode *node)
{
	std::list<txNode*> adjnodes;

	const int i=node->i;
	const int j=node->j;
	// the following are determnined by the adjacent relation in
	// the matrix map
	const int upleftI=i-1;
	const int upI = i-1;
	const int uprightI = i-1;

	const int leftI = i;
	const int rightI = i;

	const int downleftI = i+1;
	const int downI = i+1;
	const int downrightI = i+1;

	const int upleftJ = j-1;
	const int leftJ = j-1;
	const int downleftJ = j-1;

	const int upJ = j;
	const int downJ = j;

	const int uprightJ = j+1;
	const int rightJ = j+1;
	const int downrightJ = j+1;

	// upleft
	if (IsValid(upleftI, upleftJ)){
		CreatNode(upleftI, upleftJ,digcost, node, adjnodes);
	}

	// up
	if (IsValid(upI, upJ)){
		CreatNode(upI, upJ, vcost, node, adjnodes);
	}

	// upright
	if (IsValid(uprightI, uprightJ)){
		CreatNode(uprightI, uprightJ, digcost, node, adjnodes);
	}

	// left
	if (IsValid(leftI, leftJ)){
		CreatNode(leftI, leftJ, hcost, node, adjnodes);
	}

	// right
	if (IsValid(rightI, rightJ)){
		CreatNode(rightI, rightJ, hcost, node, adjnodes);
	}

	// downleft
	if (IsValid(downleftI, downleftJ)){
		CreatNode(downleftI, downleftJ, digcost, node, adjnodes);
	}

	// down
	if (IsValid(downI, downJ)){
		CreatNode(downI, downJ, vcost, node, adjnodes);
	}

	// downright
	if (IsValid(downrightI, downrightJ)){
		CreatNode(downrightI, downrightJ, digcost, node, adjnodes);
	}
		
	return adjnodes;
}

// This function should be move to the map class 
// make the map have more functionality.
bool txAstar::IsValid(int i, int j)
{
	if (i>=0 && i<map->GetNumRow() && j>=0 && j<map->GetNumColumn() && (map->GetIJValue(i,j)==ROAD||map->GetIJValue(i,j)==START ||map->GetIJValue(i,j)==GOAL))
	{
		return true;
	}
	return false;
}

txNode *txAstar::CreatNode(int i, int j, int edgevalue, txNode *node, std::list<txNode*> &nodelist)
{
	txNode *n = new txNode;
	n->i = i;
	n->j = j;
	n->g = node->g+edgevalue;
	n->h = DiganalHeuristicF(n);
	n->f = n->g + n->h;
	n->parent = node;

	nodelist.push_back(n);

	return n;
}

bool txAstar::IsExistsEqualBetter(txNode *n, std::list<txNode *> &list)
{
	for (std::list<txNode*>::iterator it=list.begin(); it!=list.end(); it++)
	{
		if (n->i==(*it)->i && n->j==(*it)->j && n->f>(*it)->f){
			return true;
		}
	}
	return false;
}

void txAstar::RemoveNode(txNode *n, std::list<txNode*> &nodes)
{
	for (std::list<txNode*>::iterator it=nodes.begin(); it!=nodes.end(); )
	{
		if (n->i==(*it)->i && n->j==(*it)->j)
		{
			delete *it;
			it = nodes.erase(it);
		}
		else
		{
			it++;
		}
	}
}



