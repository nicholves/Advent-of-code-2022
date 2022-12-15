#pragma once
#include <vector>

struct Knot {
	int x = 0;
	int y = 0;

	Knot() {
		this->x = 0;
		this->y = 0;
	}
	Knot(int x, int y) {
		this->x = x;
		this->y = y;
	}

	inline bool operator==(const Knot& knot2) const { return this->x == knot2.x && this->y == knot2.y; }
};

/*
Quadrants look like this

1  |  2
-------
3  |  4

*/

enum Quadrant {
	QuadOne,
	QuadTwo,
	QuadThree,
	QuadFour
};

typedef Knot Head;
typedef Knot Tail;

void EvalMove(const char dir, const int amount, Head& head, Tail& tail, std::vector<Knot>& positions, bool save = true);

bool AreDiagonal(const Knot& knot1, const Knot& knot2);

bool AreDiagonal(const Knot& knot1, const Knot& knot2, Quadrant& quad);

bool AreFar(const Knot& knot1, const Knot& knot2);

int CalculateDupes(const std::vector<Knot>& positions);

void PrintSampleBoard(const Knot& head, const Knot& tail);

void EvalMovePart2(const char dir, const int amount, Head knots[10], std::vector<Knot>& positions, bool save = true);