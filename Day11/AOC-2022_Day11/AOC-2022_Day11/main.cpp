#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Monkey.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#elif INPUT == 1
#define PATH "Puzzle.txt"
#endif

#define PART 2

// attempt 1: 78678 -> correct!

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	uint64_t result = 0;

	std::vector<Monkey> monkeys;

	std::string monkeyText[7];
	int monkeyCounter = 0;
	while (std::getline(file, text)) {
		monkeyText[monkeyCounter % 7] = text;
		if (monkeyCounter % 7 == 0 && monkeyCounter != 0) {
			monkeys.push_back(CreateMonkey(monkeyText));
		}

		monkeyCounter++;
	}

	if (monkeyCounter % 7 == 0 && monkeyCounter != 0) {
		monkeys.push_back(CreateMonkey(monkeyText));
	}

	for (int i = 0; i < 20; ++i) {
		for (int monkey = 0; monkey < monkeys.size(); ++monkey) {
			monkeys[monkey].TakeTurn(monkeys);
		}
	}

	std::sort(monkeys.begin(), monkeys.end(), [](Monkey a, Monkey b) { return a.getInspects() > b.getInspects(); });

	result = (uint64_t)monkeys[0].getInspects() * (uint64_t)monkeys[1].getInspects();

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;
}

/* this part was tough... kept running into integer overflow.
   look up modular arithmetic to deal with large numbers / modular arithmetic prime numbers

   attempt 1: 15333249714 -> correct!
*/
void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	uint64_t result = 0; // amswer might get big so watch out

	std::vector<Monkey> monkeys;

	std::string monkeyText[7];
	int monkeyCounter = 0;
	while (std::getline(file, text)) {
		monkeyText[monkeyCounter % 7] = text;
		if (monkeyCounter % 7 == 0 && monkeyCounter != 0) {
			monkeys.push_back(CreateMonkey(monkeyText));
		}

		monkeyCounter++;
	}

	if (monkeyCounter % 7 == 0 && monkeyCounter != 0) {
		monkeys.push_back(CreateMonkey(monkeyText));
	}

	uint64_t bigMod = 1;
	for (int i = 0; i < monkeys.size(); ++i) {
		bigMod *= monkeys[i].getDivBy();
	}


	for (int i = 0; i < 10000; ++i) {
		for (int monkey = 0; monkey < monkeys.size(); ++monkey) {
			monkeys[monkey].TakeTurn(monkeys, bigMod, 2);
		}
	}

	std::sort(monkeys.begin(), monkeys.end(), [](Monkey a, Monkey b) { return a.getInspects() > b.getInspects(); });

	result = (uint64_t)monkeys[0].getInspects() * (uint64_t)monkeys[1].getInspects();

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