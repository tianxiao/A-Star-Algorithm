#pragma once
using namespace System;

class txAstar;
class txMap;

namespace ManagedC_Wrapper
{

	public	ref class txAstarWrapper
	{
	public:
		txAstarWrapper();

		
	};

	public ref class txMapWrapper
	{
	public:
		txMapWrapper(int m, int n,array<int>^Arr);
		~txMapWrapper();

	protected:
		!txMapWrapper();
	private:
		txMap *map;
	};
}


