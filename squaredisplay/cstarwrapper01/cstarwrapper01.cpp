// This is the main DLL file.

#include "stdafx.h"
#include <assert.h>
#include <vector>

#include "cstarwrapper01.h"
#include "../AStarImp/txMap.h"
#include "../AStarImp/txAstar.h"



namespace cstarwrapper01
{
	txMapWrapper::txMapWrapper(int m, int n, array<int>^ a)
	{
		assert(m*n==a->Length);
		map = new txMap(m, n);
		for (int i=0; i<a->Length; i++)
		{
			map->SetValue(i, a[i]);
		}
		map->SetStartEndIJ();
	}
	txMapWrapper::~txMapWrapper()
	{
		delete map;
	}

	txAstarWrapper::txAstarWrapper(txMapWrapper^ map)
	{
		astar = new txAstar(map->GetNativeMap());
	}

	txAstarWrapper::~txAstarWrapper()
	{
		delete astar;
	}

	void txAstarWrapper::CalculatePath()
	{
		astar->CalculatePath();
	}

	array<int>^ txAstarWrapper::GetPath()
	{
		std::vector<int> result = astar->GetPath();
		array<int>^ a = gcnew array<int>(result.size());
		for (size_t i=0; i<result.size(); i++)
		{
			a[i] = result[i];
		}
		return a;
	}

	array<int>^ txAstarWrapper::GetAccessed()
	{
		std::vector<int> result = astar->GetAccessed();
		array<int>^ a = gcnew array<int>(result.size());
		for (size_t i=0; i<result.size(); i++)
		{
			a[i] = result[i];
		}

		return a;
	}
}

