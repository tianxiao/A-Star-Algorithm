#include "StdAfx.h"
#include "txAstarWrapper.h"
#include <assert.h>
#include "../AStarImp/txMap.h"



namespace ManagedC_Wrapper
{

	txAstarWrapper::txAstarWrapper()
	{
	}


	txMapWrapper::txMapWrapper(int m, int n, array<int>^Arr)
	{
		
		map = new txMap(m, n);
		assert(m*n==Arr->Length);
		for (int i=0; i<Arr->Length; i++)
		{
			map->SetValue(i, Arr[i]);
		}
	}

	txMapWrapper::!txMapWrapper()
	{
		delete map;
	}

	txMapWrapper::~txMapWrapper()
	{
		
	}
}
