#ifndef _STATE_H
#define _STATE_H
enum class State {
	GAME_WON,
	GAME_INPROGRESS,
	GAME_NOT_STARTED
};

enum Difficulty {
	Easy, //2,3 colors
	Medium, //4,5,6 colors
	Hard //7,8,9 colors
};

const int CUBES_PER_STACK = 4;
#endif // !_STATE_H
