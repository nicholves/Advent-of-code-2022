#pragma once

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


bool RecusivelyCheckPaths(const std::pair<int, int>& current, std::set<std::pair<int, int>>& visited, std::vector<std::set<std::pair<int, int>>>& workingPaths, const std::vector<std::vector<char>>& data, std::set<std::pair<int, int>>& fullyChecked);