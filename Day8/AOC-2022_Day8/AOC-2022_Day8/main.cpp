#include <iostream>
#include <fstream>
#include <string>

#include "funcs.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#else
#define PATH "Puzzle.txt"
#endif

#define PART 2

// attempt 1: 1253 -> too low
// attempt 2: 1690 -> correct!

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	// first we count the number of lines in the file
	size_t rows = 0;
	size_t cols = 0;
	while (std::getline(file, text)) {
		cols = text.size();
		rows++;
	}
	file.clear();
	file.seekg(0); // go back to the start of the file

	char* trees = new char[rows * cols];

	memset(trees, 0, rows * cols); // for testing purposes

	size_t currRow = 0;
	while (std::getline(file, text)) {
		for (int i = 0; i < text.size(); ++i) {
			SetInTree(trees, currRow, i, (int)text[i], cols);
		}
		currRow++;
	}

	result = GetNumVisibleTrees(trees, rows, cols);

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	delete [] trees;
}

// attempt 1: 129	 -> too low
// attempt 2: 535680 -> correct!

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	// first we count the number of lines in the file
	size_t rows = 0;
	size_t cols = 0;
	while (std::getline(file, text)) {
		cols = text.size();
		rows++;
	}
	file.clear();
	file.seekg(0); // go back to the start of the file

	char* trees = new char[rows * cols];

	memset(trees, 0, rows * cols); // for testing purposes

	size_t currRow = 0;
	while (std::getline(file, text)) {
		for (int i = 0; i < text.size(); ++i) {
			SetInTree(trees, currRow, i, (int)text[i], cols);
		}
		currRow++;
	}

	result = GetBestScenicScore(trees, rows, cols);

	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;

	delete[] trees;
}


int main() {
#if PART == 1
	part1(PATH);
#endif

#if PART == 2
	part2(PATH);
#endif

	return 0;
}

char GetFromTree(const char* arr, size_t row, size_t col, size_t colsize) {
	int cols = row * colsize;
	int ones = col;

	return arr[cols + ones];
}

void SetInTree(char* arr, size_t row, size_t col, char c, size_t colsize) {
	int cols = row * colsize;
	int ones = col;

	arr[cols + ones] = c;
}

int GetNumVisibleTrees(const char* arr, size_t rows, size_t cols) {
	int total = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			total += TreeIsVisible(arr, i, j, rows, cols);
		}
	}
	return total;
}

bool TreeIsVisible(const char* arr, int y, int x, size_t rows, size_t cols) {
	if (rows == 0 || cols == 0) {
		return false; // the grid doesn't exist and something has gone wrong
	}

	if (y == 0 || x == 0 || y == rows - 1 || x == cols - 1) 
		return true; // the tree is on the edge of the grid

	int invisibleDirs = 0;

	int i = y - 1;
	while (i >= 0) {
		if (GetFromTree(arr, i, x, cols) >= GetFromTree(arr, y, x, cols)) { // checking down
			invisibleDirs++;
			break;
		}

		i--;
	}
	
	i = y + 1;
	while (i < rows) {
		if (GetFromTree(arr, i, x, cols) >= GetFromTree(arr, y, x, cols)) { // checking up
			invisibleDirs++;
			break;
		}

		i++;
	}
	
	i = x - 1;
	while (i >= 0) {
		if (GetFromTree(arr, y, i, cols) >= GetFromTree(arr, y, x, cols)) { // checking left
			invisibleDirs++;
			break;
		}

		i--;
	}
	
	i = x + 1;
	while (i < cols) {
		if (GetFromTree(arr, y, i, cols) >= GetFromTree(arr, y, x, cols)) { // checking right
			invisibleDirs++;
			break;
		}

		i++;
	}
	i = 0;

	if (invisibleDirs == 4)
		return false; // the tree is invisible from all 4 cardinal directions

	return true; // the tree isn't obstructed in any direction
}

int GetBestScenicScore(const char* arr, size_t rows, size_t cols) {
	int best = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			best = std::max(GetScenicScore(arr, i, j, rows, cols), best);
		}
	}
	return best;
}

int GetScenicScore(const char* arr, int y, int x, size_t rows, size_t cols) {
	if (rows == 0 || cols == 0) {
		return false; // the grid doesn't exist and something has gone wrong
	}

	int visibleDown = 0, visibleUp = 0,  visibleRight = 0, visibleLeft = 0;

	int i = y - 1;
	while (i >= 0) {
		if (GetFromTree(arr, i, x, cols) >= GetFromTree(arr, y, x, cols)) { // checking down
			visibleDown++;
			break;
		}

		i--;
		visibleDown++;
	}

	i = y + 1;
	while (i < rows) {
		if (GetFromTree(arr, i, x, cols) >= GetFromTree(arr, y, x, cols)) { // checking up
			visibleUp++;
			break;
		}

		i++;
		visibleUp++;
	}

	i = x - 1;
	while (i >= 0) {
		if (GetFromTree(arr, y, i, cols) >= GetFromTree(arr, y, x, cols)) { // checking left
			visibleLeft++;
			break;
		}

		i--;
		visibleLeft++;
	}

	i = x + 1;
	while (i < cols) {
		if (GetFromTree(arr, y, i, cols) >= GetFromTree(arr, y, x, cols)) { // checking right
			visibleRight++;
			break;
		}

		i++;
		visibleRight++;
	}

	return visibleDown * visibleUp * visibleRight * visibleLeft;
}