#pragma once
#include <vector>

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#elif INPUT == 1
#define PATH "Puzzle.txt"
#endif

#if INPUT == 0
#define ROWS 5
#define COLS 8
#else 
#define ROWS 41
#define COLS 93
#endif


void PushAdj(std::vector<std::pair<int, int>>& adjList, const std::vector<std::vector<char>>& data, std::pair<int, int> current);