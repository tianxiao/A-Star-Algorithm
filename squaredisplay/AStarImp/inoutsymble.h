#pragma once

#ifdef PATHTRACING_ASTARALGORITHM_DLL
#define ASTAR_ALGORITHM_API _declspec(dllexport)
#else
#define ASTAR_ALGORITHM_API _declspec(dllimport)
#endif