#pragma once

namespace RockPaperScissors {
	const int asciiTransform = -23; /* to transform from what we have to what they do in part 1 i.e
									   transform from XYZ to ABC */

	enum GameResult {
		LOSS = 0,
		DRAW = 3,
		WIN  = 6
	};


	class RPCGame {
	public:
		RPCGame(char oppPlayed, char wePlayed);

		int EvalScore() const;

		GameResult EvalVictory() const;

		void InvokeStrategy();

	private:
		char m_oppPlayed;
		char m_wePlayed;
	};

}