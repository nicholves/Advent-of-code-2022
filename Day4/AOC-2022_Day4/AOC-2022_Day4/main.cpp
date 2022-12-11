#include <iostream>
#include <fstream>
#include <string>

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
		Range elf1;
		Range elf2;

		// sample range looks like: 8-10,6-8

		elf1.start = stoi(text.substr(0, text.find("-"))); // from start to -
		elf1.end = stoi(text.substr(text.find("-") + 1, text.find(","))); // from - to ,

		int seperate = text.find(",");

		elf2.start = stoi(text.substr(seperate + 1, text.find("-", seperate)));
		elf2.end = stoi(text.substr(text.find("-", seperate) + 1));

		if (FullyContained(elf1, elf2) || FullyContained(elf2, elf1)) {
			result++;
		}
	}

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	file.close();
}

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	while (std::getline(file, text)) {
		Range elf1;
		Range elf2;

		// sample range looks like: 8-10,6-8

		elf1.start = stoi(text.substr(0, text.find("-"))); // from start to -
		elf1.end = stoi(text.substr(text.find("-") + 1, text.find(","))); // from - to ,

		int seperate = text.find(",");

		elf2.start = stoi(text.substr(seperate + 1, text.find("-", seperate)));
		elf2.end = stoi(text.substr(text.find("-", seperate) + 1));

		if (Overlap(elf1, elf2) || Overlap(elf2, elf1)) {
			result++;
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

bool FullyContained(Range elf1, Range elf2) {
	if (elf1.start >= elf2.start && elf1.end <= elf2.end)
		return true;
	
	
	return false;
}


bool Overlap(Range elf1, Range elf2) {
	if (elf1.start >= elf2.start && elf1.start <= elf2.end)
		return true;


	return false;
}