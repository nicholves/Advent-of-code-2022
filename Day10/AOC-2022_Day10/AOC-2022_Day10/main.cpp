#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include "funcs.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#elif INPUT == 1
#define PATH "Puzzle.txt"
#endif

#define PART 2

// attempt 1: 14160 -> correct

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0, cycle = 1, x = 1, leftover = 0;

	while (std::getline(file, text)) {
		// start of cycle:
		if (cycle == 20 || (cycle - 20) % 40 == 0) {
			result += x * cycle;
		}

		if (text[0] == 'n') {
			leftover = 0;
		}
		else if (text[0] == 'a') {
			leftover = std::stoi(text.substr(5));
			cycle++;
			if (cycle == 20 || (cycle - 20) % 40 == 0) {
				result += x * cycle;
			}
		}
		else {
			assert(0); // unreachable
		}

		// end of cycle
		cycle++;
		x += leftover;
		leftover = 0;
	}

	if (cycle == 20 || (cycle - 20) % 40 == 0) {
		result += x * cycle;
	}
	
	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;
}

// attempt 1: RJERPEFC -> correct

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	int cycle = 1, x = 1, leftover = 0;
	std::string result;

	while (std::getline(file, text)) {
		// start of cycle:
		if ((cycle - 1) % 40 == 0) {
			result += '\n';
		}

		if (text[0] == 'n') {
			leftover = 0;
		}
		else if (text[0] == 'a') {
			leftover = std::stoi(text.substr(5));
			DrawPixel(result, x, cycle);
			cycle++;
			if ((cycle - 1) % 40 == 0) {
				result += '\n';
			}
		}
		else {
			assert(0); // unreachable
		}

		// end of cycle
		DrawPixel(result, x, cycle);
		cycle++;
		x += leftover;
		leftover = 0;
	}

	if ((cycle - 1) % 40 == 0) {
		result += '\n';
	}

	std::cout << "Answer to Part 2 with " << PATH << ": " << std::endl << result << std::endl;
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

void DrawPixel(std::string& result, int x, int cycle) {
	cycle = cycle - 1;
	cycle = cycle % 40;
	if (x + 1 == cycle || x == cycle || x - 1 == cycle)
		result += '#';
	else
		result += '.';
}