#include "RPCGame.h"
#include <assert.h>

using namespace RockPaperScissors;

RPCGame::RPCGame(char oppPlayed, char wePlayed) {
	m_oppPlayed = oppPlayed;
	m_wePlayed = wePlayed;
}

int RPCGame::EvalScore() const {
	int playedScore = 0;

	if (m_wePlayed == 'X')
		playedScore = 1;
	else if (m_wePlayed == 'Y')
		playedScore = 2;
	else if (m_wePlayed == 'Z')
		playedScore = 3;

	return EvalVictory() + playedScore;
}

/*
	X = Rock
	Y = Paper
	Z = Scissors
*/
GameResult RPCGame::EvalVictory() const {
	 // the difference in characters between our options and the opponents

	if (m_oppPlayed == m_wePlayed + asciiTransform) 
		return DRAW;
	
	if (m_wePlayed == 'X') { // rock
		return m_oppPlayed == 'B' ? LOSS : WIN;
	}

	if (m_wePlayed == 'Y') { // paper
		return m_oppPlayed == 'C' ? LOSS : WIN;
	}

	if (m_wePlayed == 'Z') { // scissors
		return m_oppPlayed == 'A' ? LOSS : WIN;
	}

	assert(0); // unreachable
	return DRAW;
}

void RPCGame::InvokeStrategy() {
	if (m_wePlayed == 'X') { // we need to lose
		int reduceTo012 = m_oppPlayed - 65;
		m_wePlayed = ((reduceTo012 - 1) % 3) + 65;
		m_wePlayed = m_wePlayed == 64 ? 67 : m_wePlayed; // fix for taking module of -1
		m_wePlayed = m_wePlayed - asciiTransform;
	}

	else if (m_wePlayed == 'Y') { // we need to draw
		m_wePlayed = m_oppPlayed - asciiTransform;
	}

	else if (m_wePlayed == 'Z') { // we need to win
		int reduceTo012 = m_oppPlayed - 65;
		m_wePlayed = ((reduceTo012 + 1) % 3) + 65;
		m_wePlayed = m_wePlayed - asciiTransform;
	}	
}