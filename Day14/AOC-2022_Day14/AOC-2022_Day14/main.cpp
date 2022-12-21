#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>

// #define NOMINMAX
// #include <Windows.h> // sorry linux

#include "Space.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#elif INPUT == 1
#define PATH "Puzzle.txt"
#endif

#define PART 2

#define EXTRACOLS 500 // continuously increase this number until answer is consistent for part 2

int minx = std::numeric_limits<int>::max(), maxx = 0, maxy = 0, miny = std::numeric_limits<int>::max(), ROWS = 0, COLS = 0;

// attempt 1: 273 -> too low
// attempt 2: 329 -> too low
// attempt 3: 961 -> correct!

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	Space* grid;
	std::vector<std::vector<Location>> rocks;

	int result = 0;

	int counter = 0;
	while (std::getline(file, text)) {
		rocks.push_back(std::vector<Location>());
		int index = 0;
		while (true) {
			Location current;
			std::string nums = text.substr(index, text.find("-"));
			int x = stoi(nums.substr(0, text.find(',')));
			int y = stoi(nums.substr(nums.find(',') + 1));

			minx = std::min(minx, x);
			maxx = std::max(maxx, x);
			maxy = std::max(maxy, y);
			miny = std::min(miny, y);

			current.first = x;
			current.second = y;

			rocks[counter].push_back(current);
			index = text.find('>', index) + 2;
			if (index == std::string::npos + 2)
				break;
		}

		counter++;
	}

	ROWS = maxy + 2;
	COLS = maxx - minx + 3; // one extra to account for 0 indexing and another 2 extra for spaces on sides for sand to fall

	grid = new Space[ROWS * COLS];

	FillGridWithAir(grid);

	for (size_t i = 0; i < rocks.size(); ++i) {
		for (size_t j = 0; j < rocks[i].size() - 1; ++j) {
			Location start = rocks[i][j];
			Location end = rocks[i][j + 1];

			start.first = start.first - minx + 1;
			end.first = end.first - minx + 1;

			FillWithRocks(grid, start, end);
		}
	}

	const Location spawnPos = Location(500 - minx + 1, 0);
	bool ranOff = false;

	while (!ranOff) {
		/*if (result % 90 == 0) {
			system("cls");
			Visualize(grid);
			std::cout << std::endl;
			Sleep(500);
		}*/

		SetInGrid(grid, spawnPos, SpaceType::SAND);
		Location location = spawnPos;
		while (true) {
			if (location.first == 0 || location.first == COLS - 1 || location.second >= ROWS - 1) {
				ranOff = true;
				break;
			}
			Location potentialLocation = location;
			potentialLocation.second++;

			if (GetFromGrid(grid, potentialLocation)->Contains() == SpaceType::AIR) { // down is empty
				SetInGrid(grid, potentialLocation, SpaceType::SAND);
				SetInGrid(grid, location, SpaceType::AIR);
				location = potentialLocation;
				continue;
			}
			else { // down is full
				potentialLocation.first--;
				if (GetFromGrid(grid, potentialLocation)->Contains() == SpaceType::AIR) { // go down and left
					SetInGrid(grid, potentialLocation, SpaceType::SAND);
					SetInGrid(grid, location, SpaceType::AIR);
					location = potentialLocation;
					continue;
				}
				else { // down and left is full
					potentialLocation.first += 2;
					if (GetFromGrid(grid, potentialLocation)->Contains() == SpaceType::AIR) { // go down and right
						SetInGrid(grid, potentialLocation, SpaceType::SAND);
						SetInGrid(grid, location, SpaceType::AIR);
						location = potentialLocation;
						continue;
					}
					else { // all pathways are blocked
						break;
					}
				} 
			}
		}
		result++;
	}

	result--; // we counted one too far

	system("cls");
	Visualize(grid);
	std::cout << std::endl;

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	delete[] grid;
}

// attempt 1: 26375 -> correct!

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	Space* grid;
	std::vector<std::vector<Location>> rocks;

	int result = 0;

	int counter = 0;
	while (std::getline(file, text)) {
		rocks.push_back(std::vector<Location>());
		int index = 0;
		while (true) {
			Location current;
			std::string nums = text.substr(index, text.find("-"));
			int x = stoi(nums.substr(0, text.find(',')));
			int y = stoi(nums.substr(nums.find(',') + 1));

			minx = std::min(minx, x);
			maxx = std::max(maxx, x);
			maxy = std::max(maxy, y);
			miny = std::min(miny, y);

			current.first = x;
			current.second = y;

			rocks[counter].push_back(current);
			index = text.find('>', index) + 2;
			if (index == std::string::npos + 2)
				break;
		}

		counter++;
	}

	ROWS = maxy + 3;
	COLS = maxx - minx + EXTRACOLS; // a bunch extra to simulate being infinite

	grid = new Space[ROWS * COLS];

	FillGridWithAir(grid);

	for (size_t i = 0; i < rocks.size(); ++i) {
		for (size_t j = 0; j < rocks[i].size() - 1; ++j) {
			Location start = rocks[i][j];
			Location end = rocks[i][j + 1];

			start.first = start.first - minx + EXTRACOLS / 2;
			end.first = end.first - minx + EXTRACOLS / 2;

			FillWithRocks(grid, start, end);
		}
	}

	for (size_t i = 0; i < COLS; ++i) {
		Location location(i, ROWS - 1);
		SetInGrid(grid, location, SpaceType::ROCK);
	}

	const Location spawnPos = Location(500 - minx + EXTRACOLS / 2, 0);
	bool ranOff = false;

	// all visualization is turned off here because it probably won't fit in the console
	while (!ranOff) {
		/*if (result % 90 == 0) {
			system("cls");
			Visualize(grid);
			std::cout << std::endl;
			Sleep(500);
		}*/

		SetInGrid(grid, spawnPos, SpaceType::SAND);
		Location location = spawnPos;
		int moves = 0;
		while (true) {
			Location potentialLocation = location;
			potentialLocation.second++;

			if (GetFromGrid(grid, potentialLocation)->Contains() == SpaceType::AIR) { // down is empty
				SetInGrid(grid, potentialLocation, SpaceType::SAND);
				SetInGrid(grid, location, SpaceType::AIR);
				location = potentialLocation;
				continue;
			}
			else { // down is full
				potentialLocation.first--;
				if (GetFromGrid(grid, potentialLocation)->Contains() == SpaceType::AIR) { // go down and left
					SetInGrid(grid, potentialLocation, SpaceType::SAND);
					SetInGrid(grid, location, SpaceType::AIR);
					location = potentialLocation;
					continue;
				}
				else { // down and left is full
					potentialLocation.first += 2;
					if (GetFromGrid(grid, potentialLocation)->Contains() == SpaceType::AIR) { // go down and right
						SetInGrid(grid, potentialLocation, SpaceType::SAND);
						SetInGrid(grid, location, SpaceType::AIR);
						location = potentialLocation;
						continue;
					}
					else { // all pathways are blocked
						break;
					}
				}
			}
		}
		result++;
		if (GetFromGrid(grid, spawnPos)->Contains() == SpaceType::SAND) {
			ranOff = true;
			break;
		}
	}

	/*system("cls");
	Visualize(grid);
	std::cout << std::endl;*/

	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;

	delete[] grid;
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