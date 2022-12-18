#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#include "Funcs.h"
#include "Dijkstras.h"

#define PART 1

using std::pair;

// first attempt:  820 -> too high
// second attempt: 810 -> too high

// try breadth first search

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	std::vector<std::set<pair<int, int>>> workingPaths;
	std::set<pair<int, int>> fullyChecked;

	std::vector<std::vector<char>> chars;

	int counter = 0;
	pair<int, int> startPos;
	pair<int, int> endPos;

	for (int i = 0; i < ROWS; ++i) {
		chars.push_back(std::vector<char>());
	}

	while (std::getline(file, text)) {
		for (size_t i = 0; i < text.size(); ++i) {
			chars[counter].push_back(text[i]);

			if (text[i] == 'S')
				startPos = pair<int, int>(counter, i);

			if (text[i] == 'E')
				endPos = pair<int, int>(counter, i);
		}
		counter++;
	}

	if (startPos.first - 1 >= 0) { // check up
		std::set<pair<int, int>> visited;
		visited.insert(startPos);

		RecusivelyCheckPaths(pair<int, int>(startPos.first - 1, startPos.second), visited, workingPaths, chars, fullyChecked);
	}

	if (startPos.second + 1 < COLS) { // check right
		fullyChecked.clear();
		std::set<pair<int, int>> visited;
		visited.insert(startPos);

		RecusivelyCheckPaths(pair<int, int>(startPos.first, startPos.second + 1), visited, workingPaths, chars, fullyChecked);
	}

	if (startPos.first + 1 < ROWS) { // check down
		fullyChecked.clear();
		std::set<pair<int, int>> visited;
		visited.insert(startPos);

		RecusivelyCheckPaths(pair<int, int>(startPos.first + 1, startPos.second), visited, workingPaths, chars, fullyChecked);
	}

	if (startPos.second - 1 >= 0) { // check left
		fullyChecked.clear();
		std::set<pair<int, int>> visited;
		visited.insert(startPos);

		RecusivelyCheckPaths(pair<int, int>(startPos.first, startPos.second - 1), visited, workingPaths, chars, fullyChecked);
	}

	std::sort(workingPaths.begin(), workingPaths.end(), [](std::set<pair<int, int>> a, std::set<pair<int, int>> b) { return a.size() < b.size(); });

	result = workingPaths[0].size() - 1;

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;
}


void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	while (std::getline(file, text)) {
	}

	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;
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

bool RecusivelyCheckPaths(const std::pair<int, int>& current, std::set<pair<int, int>>& visited, std::vector<std::set<pair<int, int>>>& workingPaths, const std::vector<std::vector<char>>& data, std::set<pair<int, int>>& fullyChecked) {
	visited.insert(current);

	char currentChar = data[current.first][current.second];
	
	if (data[current.first][current.second] == 'E') {
		int count = 0;
		if (visited.size() <= 30) {
			count++;
		}
		count++;

		workingPaths.push_back(visited);
		visited.erase(current);

		return true;
	}
	
	
	
	
	if (current.first - 1 >= 0) { // check up
		char checkAgainst = data[current.first - 1][current.second];
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= data[current.first][current.second] + 1) {
			if (visited.find(pair<int, int>(current.first - 1, current.second)) == visited.end() && fullyChecked.find(pair<int, int>(current.first - 1, current.second)) == fullyChecked.end())
				RecusivelyCheckPaths(pair<int, int>(current.first - 1, current.second), visited, workingPaths, data, fullyChecked);
		}
	}

	if (current.second + 1 < COLS) { // check right
		char checkAgainst = data[current.first][current.second + 1];
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= data[current.first][current.second] + 1) {
			if (visited.find(pair<int, int>(current.first, current.second + 1)) == visited.end() && fullyChecked.find(pair<int, int>(current.first, current.second + 1)) == fullyChecked.end())
				RecusivelyCheckPaths(pair<int, int>(current.first, current.second + 1), visited, workingPaths, data, fullyChecked);
		}
	}

	if (current.first + 1 < ROWS) { // check down
		char checkAgainst = data[current.first + 1][current.second];
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= data[current.first][current.second] + 1) {
			if (visited.find(pair<int, int>(current.first + 1, current.second)) == visited.end() && fullyChecked.find(pair<int, int>(current.first + 1, current.second)) == fullyChecked.end())
				RecusivelyCheckPaths(pair<int, int>(current.first + 1, current.second), visited, workingPaths, data, fullyChecked);
		}
	}

	if (current.second - 1 >= 0) { // check left
		char checkAgainst = data[current.first][current.second - 1];
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= data[current.first][current.second] + 1) {
			if (visited.find(pair<int, int>(current.first, current.second - 1)) == visited.end() && fullyChecked.find(pair<int, int>(current.first, current.second - 1)) == fullyChecked.end())
				RecusivelyCheckPaths(pair<int, int>(current.first, current.second - 1), visited, workingPaths, data, fullyChecked);
		}
	}
	
	visited.erase(current);
	fullyChecked.insert(current);

	return true;
}