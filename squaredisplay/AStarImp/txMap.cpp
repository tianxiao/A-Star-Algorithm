#include "StdAfx.h"
#include "txMap.h"

#include <assert.h>

txMap::txMap(int m, int n)
{
	assert(m);
	assert(n);
	this->m = m;
	this->n = n;
	map = new int[m*n];
}


txMap::~txMap(void)
{
	DestroyMap();
}

void txMap::DestroyMap()
{
	delete[] map;
}

void txMap::SetIJValue(int i, int j, int v)
{
	map[i*n+j] = v;
}

void txMap::SetValue(int i, int v)
{
	map[i] = v;
}

int txMap::GetIJValue(int i, int j)
{
	return map[i*n+j];
}

void txMap::SetMap(int *mp)
{
	
	for (int i=0; i<m*n; i++)
	{
		assert(mp[i]>=0);
		map[i] = mp[i];
	}

	SetStartEndIJ();
}

void txMap::SetStartEndIJ()
{
	for (int i=0; i<m*n; i++)
	{
		if (map[i] == START)
		{
			startI = i/n;
			startJ = i-startI*n;
		}

		if (map[i] == GOAL)
		{
			goalI = i/n;
			goalJ = i-goalI*n;
		}
	}
}
