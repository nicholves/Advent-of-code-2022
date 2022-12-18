#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "Funcs.h"
#include "Dijkstras.h"

#define PART 2

using std::pair;

extern int dist[ROWS * COLS];

// first attempt:  820 -> too high
// second attempt: 810 -> too high
// thrid attempt: 412  -> correct!

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	std::vector<std::vector<char>> chars;
	vector<pair<int, int>>* adj = new vector<pair<int, int>>[ROWS * COLS];

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

	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			PushAdj(adj[(i * COLS) + j], chars, pair<int, int>(i, j));
		}
	}

	int source = (startPos.first * COLS) + startPos.second;

	DoDijkstra(adj, source, ROWS * COLS);

	result = dist[(endPos.first * COLS) + endPos.second];
	

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	delete[] adj;
}

// first attempt: 402 -> correct!

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	std::vector<std::vector<char>> chars;
	std::vector<pair<int, int>> startPoses;
	vector<pair<int, int>>* adj = new vector<pair<int, int>>[ROWS * COLS];

	int counter = 0;
	pair<int, int> startPos;
	pair<int, int> endPos;

	for (int i = 0; i < ROWS; ++i) {
		chars.push_back(std::vector<char>());
	}

	while (std::getline(file, text)) {
		for (size_t i = 0; i < text.size(); ++i) {
			chars[counter].push_back(text[i]);

			if (text[i] == 'S' || text[i] == 'a') {
				startPoses.push_back(pair<int, int>(counter, i));
			}

			if (text[i] == 'S')
				startPos = pair<int, int>(counter, i);

			if (text[i] == 'E')
				endPos = pair<int, int>(counter, i);
		}
		counter++;
	}

	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			PushAdj(adj[(i * COLS) + j], chars, pair<int, int>(i, j));
		}
	}

	int currShortest = std::numeric_limits<int>::max();

	for (size_t i = 0; i < startPoses.size(); ++i) {
		int source = (startPoses[i].first * COLS) + startPoses[i].second;

		DoDijkstra(adj, source, ROWS * COLS);

		if (dist[(endPos.first * COLS) + endPos.second] < currShortest) {
			currShortest = dist[(endPos.first * COLS) + endPos.second];
		}
	}
	

	result = currShortest;


	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;

	delete[] adj;
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

void PushAdj(std::vector<std::pair<int, int>>& adjList, const std::vector<std::vector<char>>& data, std::pair<int, int> current) {
	if (current.first - 1 >= 0) { // check up
		int checkIndex = ((current.first - 1) * COLS) + current.second;

		char checkAgainst = data[current.first - 1][current.second];
		char checkAt = data[current.first][current.second];
		if (checkAt == 'S') { checkAt = 'a'; }
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= checkAt + 1) {
			adjList.push_back(pair<int, int>(checkIndex, 1));
		}
	}

	if (current.second + 1 < COLS) { // check right
		int checkIndex = ((current.first) * COLS) + current.second + 1;

		char checkAgainst = data[current.first][current.second + 1];
		char checkAt = data[current.first][current.second];
		if (checkAt == 'S') { checkAt = 'a'; }
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= checkAt + 1) {
			adjList.push_back(pair<int, int>(checkIndex, 1));
		}
	}

	if (current.first + 1 < ROWS) { // check down
		int checkIndex = ((current.first + 1) * COLS) + current.second;

		char checkAgainst = data[current.first + 1][current.second];
		char checkAt = data[current.first][current.second];
		if (checkAt == 'S') { checkAt = 'a'; }
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= checkAt + 1) {
			adjList.push_back(pair<int, int>(checkIndex, 1));
		}
	}

	if (current.second - 1 >= 0) { // check left
		int checkIndex = ((current.first) * COLS) + current.second - 1;

		char checkAgainst = data[current.first][current.second - 1];
		char checkAt = data[current.first][current.second];
		if (checkAt == 'S') { checkAt = 'a'; }
		if (checkAgainst == 'E') { checkAgainst = 'z'; }

		if (checkAgainst <= checkAt + 1) {
			adjList.push_back(pair<int, int>(checkIndex, 1));
		}
	}
}