#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "RPCGame.h"

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

	std::vector<RockPaperScissors::RPCGame> games;


	while (std::getline(file, text)) {
		games.push_back(RockPaperScissors::RPCGame(text[0], text[2]));
	}

	int result = 0;
	for (int i = 0; i < games.size(); ++i) {
		result += games[i].EvalScore();
	}

	std::cout << "Answer to Part 1 with "  << PATH << ": " << result << std::endl;

	file.close();
}

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	std::vector<RockPaperScissors::RPCGame> games;


	while (std::getline(file, text)) {
		games.push_back(RockPaperScissors::RPCGame(text[0], text[2]));
	}

	int result = 0;
	for (int i = 0; i < games.size(); ++i) {
		games[i].InvokeStrategy();
		result += games[i].EvalScore();
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


