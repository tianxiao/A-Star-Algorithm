// cstarwrapper01.h

#pragma once

using namespace System;

class txMap;
class txAstar;

namespace cstarwrapper01 {

	public ref class Class1
	{
		// TODO: Add your methods for this class here.
	};

	public ref class txMapWrapper
	{
	public:
		txMapWrapper(int m, int n, array<int>^ a);
		~txMapWrapper();

		txMap *GetNativeMap() { return map; };

	private:
		txMap *map;
	};

	public ref class txAstarWrapper
	{
	public:
		txAstarWrapper(txMapWrapper^ map);

		~txAstarWrapper();

		void CalculatePath();

		array<int>^ GetPath();

		array<int>^ GetAccessed();

	private:
		txAstar *astar;
	};
}
