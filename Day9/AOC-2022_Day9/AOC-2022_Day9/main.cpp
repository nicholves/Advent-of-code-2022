#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#include "Funcs.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#elif INPUT == 1
#define PATH "Puzzle.txt"
#elif INPUT == 2
#define PATH "Sample2.txt"
#endif

#define PART 2

// attempt 1: 6470 -> correct

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	Head head;
	Tail tail;

	std::vector<Knot> positions;
	positions.push_back(tail); // the starting position of the tail

	

	int result = 0;
	//PrintSampleBoard(head, tail);
	//std::cout << std::endl;

	while (std::getline(file, text)) {
		char dir = text[0];
		int amount = stoi(text.substr(1));

		EvalMove(dir, amount, head, tail, positions);
		//PrintSampleBoard(head, tail);
		//std::cout << std::endl;
	}

	result = CalculateDupes(positions);

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;
}

// attempt 1: 2658 -> correct

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	Knot rope[10];

	std::vector<Knot> positions;
	positions.push_back(rope[9]); // the starting position of the tail



	int result = 0;
	//PrintSample2Board(rope);
	//std::cout << std::endl;

	while (std::getline(file, text)) {
		char dir = text[0];
		int amount = stoi(text.substr(1));

		EvalMovePart2(dir, amount, rope, positions, true); // only save the position if we are on the final knot
		
		//PrintSample2Board(rope);
		//std::cout << std::endl;
	}

	result = CalculateDupes(positions);

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

void EvalMove(const char dir, const int amount, Head& head, Tail& tail, std::vector<Knot>& positions, bool save) {

	if (dir == 'L' || dir == 'R') {
		for (int i = 0; i < amount; ++i) {
			Knot knotCopy = head;
			bool diagonal = AreDiagonal(head, tail);

			head.x += dir == 'R' ? 1 : -1;
			if (AreFar(head, tail)) {
				if (diagonal)
					tail = knotCopy;
				else
					tail.x += dir == 'R' ? 1 : -1;

				 if (save) 
					 positions.push_back(tail);
			}
		}
	}

	if (dir == 'U' || dir == 'D') {
		for (int i = 0; i < amount; ++i) {
			Knot knotCopy = head;
			bool diagonal = AreDiagonal(head, tail);

			head.y += dir == 'U' ? 1 : -1;
			if (AreFar(head, tail)) {
				if (diagonal)
					tail = knotCopy;
				else
					tail.y += dir == 'U' ? 1 : -1;

				if (save)
					positions.push_back(tail);
			}
		}
	}
}

bool AreDiagonal(const Knot& knot1, const Knot& knot2) {
	if (knot1.x != knot2.x && knot1.y != knot2.y)
		return true;
	
	return false;
}

bool AreDiagonal(const Knot& knot1, const Knot& knot2, Quadrant& quad) {
	if (knot1.x != knot2.x && knot1.y != knot2.y) {
		if (knot2.x > knot1.x && knot2.y > knot1.y)
			quad = QuadTwo;

		if (knot2.x > knot1.x && knot2.y < knot1.y)
			quad = QuadFour;

		if (knot2.x < knot1.x && knot2.y > knot1.y)
			quad = QuadOne;

		if (knot2.x < knot1.x && knot2.y < knot1.y)
			quad = QuadThree;

		return true;
	}

	return false;
}

bool AreFar(const Knot& knot1, const Knot& knot2) {
	int difx = abs(knot1.x - knot2.x);
	int dify = abs(knot1.y - knot2.y);

	return difx > 1 || dify > 1;
}

int CalculateDupes(const std::vector<Knot>& positions) { // this function is O(n^2) and really bad
	std::vector<Knot> checked;

	for (int i = 0; i < positions.size(); ++i) {
		bool flag = false;
		Knot knot = positions[i];
		for (int j = 0; j < checked.size(); ++j) {
			if (positions[i] == checked[j]) {
				flag = true;
				break;
			}
		}

		if (!flag) {
			checked.push_back(positions[i]);
		}
	}

	return checked.size();
}

void PrintSampleBoard(const Knot& head, const Knot& tail) {
	for (int y = 4; y >= 0; --y) {
		for (int x = 0; x < 6; ++x) {
			Knot tempKnot = Knot(x, y);

			if (tempKnot == head && tempKnot == tail) {
				std::cout << "B";
			}
			else if (tempKnot == head) {
				std::cout << "H";
			}
			else if (tempKnot == tail) {
				std::cout << "T";
			}
			else {
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}
}

void EvalMovePart2(const char dir, const int amount, Head knots[10], std::vector<Knot>& positions, bool save) {
	// needed to read instructions better. Caused me issues

	if (dir == 'L' || dir == 'R') {
		for (int i = 0; i < amount; ++i) {
			for (int j = 0; j < 9; ++j) {
				Knot& head = knots[j];
				Knot& tail = knots[j + 1];

				if (j == 0)
					head.x += dir == 'R' ? 1 : -1;

				if (AreFar(head, tail)) {
					Quadrant quad;
					bool diagonal = AreDiagonal(tail, head, quad);

					if (diagonal) {
						switch (quad)
						{
						case QuadOne:
							tail.x -= 1;
							tail.y += 1;
							break;
						case QuadTwo:
							tail.x += 1;
							tail.y += 1;
							break;
						case QuadThree:
							tail.x -= 1;
							tail.y -= 1;
							break;
						case QuadFour:
							tail.x += 1;
							tail.y -= 1;
							break;
						default:
							break;
						}
					}
					else {
						if (tail.y == head.y) {
							tail.x += tail.x < head.x ? 1 : -1;
						}
						else if (tail.x == head.x) {
							tail.y += tail.y < head.y ? 1 : -1;
						}
						else {
							assert(0);
						}
					}

					if (save && j + 1 == 9)
						positions.push_back(tail);
				}
			}
		}
	}

	if (dir == 'U' || dir == 'D') {
		for (int i = 0; i < amount; ++i) {
			for (int j = 0; j < 9; ++j) {
				Knot& head = knots[j];
				Knot& tail = knots[j + 1];

				if (j == 0)
					head.y += dir == 'U' ? 1 : -1;

				if (AreFar(head, tail)) {
					Quadrant quad;
					bool diagonal = AreDiagonal(tail, head, quad);

					if (diagonal) {
						switch (quad)
						{
						case QuadOne:
							tail.x -= 1;
							tail.y += 1;
							break;
						case QuadTwo:
							tail.x += 1;
							tail.y += 1;
							break;
						case QuadThree:
							tail.x -= 1;
							tail.y -= 1;
							break;
						case QuadFour:
							tail.x += 1;
							tail.y -= 1;
							break;
						default:
							break;
						}
					}
					else {
						if (tail.y == head.y) {
							tail.x += tail.x < head.x ? 1 : -1;
						}
						else if (tail.x == head.x) {
							tail.y += tail.y < head.y ? 1 : -1;
						}
						else {
							assert(0);
						}
					}

					if (save && j + 1 == 9)
						positions.push_back(tail);
				}
			}
		}
	}
}