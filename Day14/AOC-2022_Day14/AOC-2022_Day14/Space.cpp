#include "Space.h"
#include <assert.h>
#include <iostream>
#include <string>

void FillGridWithAir(Space* grid) {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			Location location(j, i);
			GetFromGrid(grid, location)->SetType(SpaceType::AIR);
		}
	}
}

Space* GetFromGrid(Space* grid, Location location) {
	int row = location.second * COLS;
	int col = location.first;

	return grid + row + col;
}

void SetInGrid(Space* grid, Location location, SpaceType type) {
	GetFromGrid(grid, location)->SetType(type);
}

void FillWithRocks(Space* grid, Location start, Location end) {
	if (start.first == end.first) { // vertical line
		Location startLine;
		Location endLine;

		startLine.second = std::min(start.second, end.second);
		startLine.first = start.first;

		endLine.second = std::max(start.second, end.second);
		endLine.first = end.first;

		int x = startLine.first;
		for (int i = startLine.second; i <= endLine.second; ++i) {
			SetInGrid(grid, Location(x, i), SpaceType::ROCK);
		}
	}

	else if (start.second == end.second) { // horizontal line
		Location startLine;
		Location endLine;

		startLine.first = std::min(start.first, end.first);
		startLine.second = start.second;

		endLine.first = std::max(start.first, end.first);
		endLine.second = end.second;

		int y = startLine.second;
		for (int i = startLine.first; i <= endLine.first; ++i) {
			SetInGrid(grid, Location(i, y), SpaceType::ROCK);
		}
	}

	else {
		assert(0); // unreachable
	}
}

void Visualize(Space* grid) {
	for (int row = 0; row < ROWS; ++row) {
		std::string output = "";
		for (int col = 0; col < COLS; ++col) {
			switch (GetFromGrid(grid, Location(col, row))->Contains()) {
			case SpaceType::AIR:
				output += '.';
				break;
			case SpaceType::ROCK:
				output += '#';
				break;
			case SpaceType::SAND:
				output += 'O';
				break;
			}
		}
		std::cout << output << std::endl;
	}
}