#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "Stack.h"
#include "Common.h"

class Platform {
public:
	virtual ~Platform() = default;

	// Getters
	virtual const std::vector<Stack>& get_stacks() const = 0;
	virtual State get_game_state() const = 0;

	// Actions
	virtual bool apply_move(int from, int to) = 0;
	virtual void new_game(Difficulty diff) = 0;
	virtual void restart_game() = 0;
	virtual void undo() = 0;
};

#endif // !_PLATFORM_H
