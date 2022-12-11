#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <assert.h>

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

	int result = 0;

	while (std::getline(file, text)) {
		std::set<char> items;
		for (int i = 0; i < text.length() / 2; ++i) {
			items.insert(text[i]);
		}

		for (int i = text.length() / 2; i < text.length(); ++i) {
			if (items.find(text[i]) != items.end())
			{
				result += GetPriority(text[i]);
				break;
			}
		}
	}

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	file.close();
}

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	std::set<char> rucksacks[3];

	int line = 0;
	while (std::getline(file, text)) {
		int index = line % 3;

		rucksacks[index].clear();
		for (int i = 0; i < text.length(); ++i) {
			rucksacks[index].insert(text[i]);
		}

		if ((line % 3) == 2) { // we have a new group of 3 now
			result += EvaluateCommonItem(rucksacks);
		}

		line++;
	}

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

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


int GetPriority(char item) {
	if (item >= 97)
		return item - 96;
	else if (item >= 65)
		return item - 38;

	assert(0);
	return 0;
}


int EvaluateCommonItem(std::set<char> rucksacks[3]) {
	std::set<char> rucksackOne = rucksacks[0];
	std::set<char> rucksackTwo = rucksacks[1];
	std::set<char> rucksackThree = rucksacks[2];


	std::set<char>::iterator iterator;
	for (iterator = rucksackOne.begin(); iterator != rucksackOne.end(); iterator++) {
		char target = *iterator;

		bool containedInSecond = rucksackTwo.find(target) != rucksackTwo.end();
		bool containedInThird = rucksackThree.find(target) != rucksackThree.end();

		if (containedInSecond && containedInThird) {
			return GetPriority(target);
		}
	}

	assert(0);
	return -1;
}