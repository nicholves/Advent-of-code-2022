#pragma once
#include <utility>

typedef std::pair<int, int> Location;

extern int ROWS, COLS; // define the grid size in these


enum class SpaceType {
	AIR,
	SAND,
	ROCK
};

class Space {
public:
	inline SpaceType Contains() const { return m_type; }

	inline void SetType(SpaceType space) { m_type = space; }

private:
	SpaceType m_type;
};

void FillGridWithAir(Space* grid);
Space* GetFromGrid(Space* grid, Location location);
void FillWithRocks(Space* grid, Location start, Location end);
void SetInGrid(Space* grid, Location location, SpaceType type);

void Visualize(Space* grid);