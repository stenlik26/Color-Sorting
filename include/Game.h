#ifndef _GAME_H
#define _GAME_H
#include "Stack.h"
#include "Common.h"
#include "Platform.h"
#include "Utils.h"
#include <stack>

struct UndoInfo {
	int from, to, cnt;
};

class Game : public Platform {
private:
	std::vector<Stack> stacks;
	int colors_count;
	int stacks_count;
	State game_state;

	std::vector<Stack> restart_stacks;
	std::stack<UndoInfo> undo_cache;

	int get_colors_by_difficulty(Difficulty diff);
	void shuffle_stacks(int shuffle_steps);
	void update_locks_and_status();

public:
	Game();
	void init_game(Difficulty diff);

	//TODO: make this private
	//Platform interface
	const std::vector<Stack>& get_stacks() const override;
	State get_game_state() const override;
	bool apply_move(int from, int to) override;
	void new_game(Difficulty diff) override;
	void restart_game() override;
	void undo() override;
};

#endif