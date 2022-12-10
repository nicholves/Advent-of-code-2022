#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

	int maxElf = 0;
	int currElf = 0;

	while (std::getline(file, text)) {
		if (text == "") {
			maxElf = currElf > maxElf ? currElf : maxElf; // replace the max elf if the current one is bigger
			currElf = 0;
			continue;
		}
		currElf += stoi(text);
	}

	maxElf = currElf > maxElf ? currElf : maxElf; // account for final elf

	std::cout << "Answer to Part 1 with "  << PATH << ": " << maxElf << std::endl;

	file.close();
}

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	std::vector<int> elves;

	int currElf = 0;

	while (std::getline(file, text)) {
		if (text == "") {
			elves.push_back(currElf);
			currElf = 0;
			continue;
		}
		currElf += stoi(text);
	}

	std::sort(elves.begin(), elves.end());
	int length = elves.size();

	int result = elves[length - 1] + elves[length - 2] + elves[length - 3];

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


