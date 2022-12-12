#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <set>

#include "Funcs.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#else
#define PATH "Puzzle.txt"
#endif

#define PART 2



void part1(std::string path) {
	std::ifstream file(path);
	std::string text;
	std::deque<char> lastFour;

	int result = 0;

	while (std::getline(file, text)) {
		for (char c : text) {
			lastFour.push_back(c);

			if (lastFour.size() > 4)
				lastFour.pop_front();

			result++;
			if (allDiferent(lastFour))
				break;
		}
	}

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	file.close();
}

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;
	std::deque<char> lastFourteen;

	int result = 0;

	while (std::getline(file, text)) {
		for (char c : text) {
			lastFourteen.push_back(c);

			if (lastFourteen.size() > 14)
				lastFourteen.pop_front();

			result++;
			if (allDiferent(lastFourteen))
				break;
		}
	}

	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;

	file.close();
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

#if PART == 1
#define SIZE 4
#else
#define SIZE 14
#endif

bool allDiferent(std::deque<char> lastFour) {
	std::set<char> tempSet;

	if (lastFour.size() != SIZE) {
		return false;
	}

	for (char c : lastFour) {
		if (tempSet.find(c) != tempSet.end()) {
			return false;
		}
		tempSet.insert(c);
	}

	return true;
}