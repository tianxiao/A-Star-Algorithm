// astar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <math.h>
#include <list>
#include <vector>

#include "txNode.h"
#include "txMap.h"
#include "txAstar.h"

#define TABLEROW 5
#define TABLECOLUMN 6
#define STARTI 2
#define STARTJ 1
#define ENDI 2
#define ENDJ 4
#define HORIZEN 10
#define VERTICAL HORIZEN
#define DIGANAL 14
#define MAXH (TABLEROW*HORIZEN+TABLECOLUMN*VERTICAL)

int diganalHeuristicF(const txNode &node)
{
	double xl=node.i-ENDI;
	double yl=node.j-ENDJ;

	return (int) (sqrt(xl*xl+yl*yl)*HORIZEN);
}


txNode *creatNode(int i, int j, int edgevalue, txNode *node, std::list<txNode*> &nodelist)
{
		txNode *n = new txNode;
		n->i = i;
		n->j = j;
		n->g = node->g+edgevalue;
		n->h = diganalHeuristicF(*n);
		n->f = n->g + n->h;
		n->parent = node;

		nodelist.push_back(n);

		return n;
}


int map[TABLEROW][TABLECOLUMN];
std::list<txNode*> opennodes;
std::list<txNode*> closenodes;

void initializemap()
{
	for (int i=0; i<TABLEROW; i++)
	{
		for (int j=0; j<TABLECOLUMN; j++)
		{
			// 0 means the path is ok
			map[i][j]=0;
		}
	}

	map[1][3] = -1;
	map[2][3] = -1;
	map[3][3] = -1;
	map[4][3] = -1;
	map[1][4] = -1;
}

txNode *minNodesInOpennodes()
{
	assert(opennodes.size());
	int min = MAXH;
	txNode *rtn=NULL;
	
	for (std::list<txNode*>::iterator it=opennodes.begin(); it!=opennodes.end(); it++)
	{
		if (min>(*it)->f){
			min = (*it)->f;
			rtn = *it;
		}
	}

	assert(rtn);
	return rtn;
}

bool isValid(int i, int j)
{
	if (i>=0 && i<TABLEROW && j>=0 && j<TABLECOLUMN && map[i][j]==0){
		return true;
	}
	return false;
}

std::list<txNode*> nodeAdjacent(txNode *node)
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
	if (isValid(upleftI, upleftJ)){
		creatNode(upleftI, upleftJ,DIGANAL, node, adjnodes);
	}

	// up
	if (isValid(upI, upJ)){
		creatNode(upI, upJ, VERTICAL, node, adjnodes);
	}

	// upright
	if (isValid(uprightI, uprightJ)){
		creatNode(uprightI, uprightJ, DIGANAL, node, adjnodes);
	}

	// left
	if (isValid(leftI, leftJ)){
		creatNode(leftI, leftJ, HORIZEN, node, adjnodes);
	}

	// right
	if (isValid(rightI, rightJ)){
		creatNode(rightI, rightJ, HORIZEN, node, adjnodes);
	}

	// downleft
	if (isValid(downleftI, downleftJ)){
		creatNode(downleftI, downleftJ, DIGANAL, node, adjnodes);
	}

	// down
	if (isValid(downI, downJ)){
		creatNode(downI, downJ, VERTICAL, node, adjnodes);
	}

	// downright
	if (isValid(downrightI, downrightJ)){
		creatNode(downrightI, downrightJ, DIGANAL, node, adjnodes);
	}
		
	return adjnodes;
}

void moveOpen2Close(txNode *n)
{
	std::list<txNode *>::iterator it;
	for (it=opennodes.begin(); it!=opennodes.end();)
	{
		if (n->i==(*it)->i&&n->j==(*it)->j){
			it = opennodes.erase(it);
		}
		else
		{
			it++;
		}
	}
	
	// what's different between opennodes.remove(n)???
	closenodes.push_back(n);
}

bool isGoal(txNode *n)
{
	if (n->i==ENDI&&n->j==ENDJ){
		return true;
	}

	return false;
}

bool isExistsEqualBetter(txNode *n, std::list<txNode *> &list)
{
	for (std::list<txNode*>::iterator it=list.begin(); it!=list.end(); it++)
	{
		if (n->i==(*it)->i && n->j==(*it)->j && n->f>(*it)->f){
			return true;
		}
	}
	return false;
}

void removeNode(txNode *n, std::list<txNode*> &nodes)
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


int _tmain(int argc, _TCHAR* argv[])
{
	initializemap();

	int nmap[TABLEROW][TABLECOLUMN] = 
	{
		{0,0,0,0,0,0},
		{0,0,0,3,0,0},
		{0,1,0,3,2,0},
		{0,0,0,3,0,0},
		{0,0,0,0,0,0}
	};

	int c=0; 
	int cmap[TABLEROW*TABLECOLUMN];
	for (int i=0; i<TABLEROW; i++)
	{
		for (int j=0; j<TABLECOLUMN; j++)
		{
			cmap[c++] = nmap[i][j];
		}
	}

	txMap map(TABLEROW, TABLECOLUMN);
	map.SetMap(cmap);

	txAstar astar(&map);
	astar.CalculatePath();


	//txNode * startnode = new txNode;
	//startnode->i = STARTI;
	//startnode->j = STARTJ;
	//startnode->g = 0;
	//startnode->h = diganalHeuristicF(*startnode);
	//startnode->f = startnode->g + startnode->h;
	//startnode->parent = NULL;

	//opennodes.push_back(startnode);

	//txNode *goal = new txNode;

	//while (opennodes.size())
	//{
	//	txNode *node = minNodesInOpennodes();

	//	moveOpen2Close(node);

	//	if (isGoal(node)){
	//		goal->parent = node;
	//		break;
	//	}

	//	std::list<txNode *> adj;
	//	adj = nodeAdjacent(node);

	//	for (std::list<txNode*>::iterator it=adj.begin(); it!=adj.end(); it++)
	//	{
	//		if (isExistsEqualBetter(*it,opennodes)) continue;
	//		if (isExistsEqualBetter(*it,closenodes)) continue;

	//		removeNode(*it, opennodes);
	//		removeNode(*it, closenodes);

	//		opennodes.push_back(*it);
	//	}

	//}



	return 0;
}

