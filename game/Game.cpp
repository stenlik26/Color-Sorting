#include "Game.h"
#include <random>
#include <iostream>
#include <stack>

int Game::get_colors_by_difficulty(Difficulty diff)
{
	switch (diff)
	{
	case Easy:
		return 2 + (rand() % 2);
	case Medium:
		return 4 + (rand() % 3);
	case Hard:
		return 7 + (rand() % 2);
	default:
		return 3;
	}
}

void Game::shuffle_stacks(int shuffle_steps)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> random(0, colors_count - 1);
	std::uniform_int_distribution<> random_in_stack(0, CUBES_PER_STACK - 1);

	for (size_t i = 0; i < shuffle_steps; i++)
	{
		int s1 = random(gen);
		int s2;
		do {
			s2 = random(gen);
		} while (s1 == s2);
		
		int i1 = random_in_stack(gen);
		int i2 = random_in_stack(gen);
		std::swap(stacks[s1].stack[i1], stacks[s2].stack[i2]);
	}
}

bool check_full_stack_valid(const Stack& stackObj) {
	if (stackObj.stack.size() != CUBES_PER_STACK)
		return false;

	for (size_t i = 0; i < stackObj.stack.size() - 1; i++) {
		if (stackObj.stack[i] != stackObj.stack[i + 1]) {
			return false;
		}
	}

	return true;
}

void Game::update_locks_and_status()
{
	int filled_stacks = 0;
	for (size_t i = 0; i < stacks_count; i++)
	{
		if (check_full_stack_valid(stacks[i])) {
			stacks[i].locked = true;
			filled_stacks++;
		}
	}

	if (filled_stacks == colors_count) {
		game_state = State::GAME_WON;
	}
}

void Game::restart_game()
{
	stacks = restart_stacks;
	
	while (!undo_cache.empty()) {
		undo_cache.pop();
	}
}

void Game::undo()
{
	if (undo_cache.empty())
		return;

	UndoInfo info = undo_cache.top();
	undo_cache.pop();

	for (int i = 0; i < info.cnt; i++) {
		stacks[info.from].stack.push_back(stacks[info.to].stack.back());
		stacks[info.to].stack.pop_back();

	}
	update_locks_and_status();
}


const std::vector<Stack>& Game::get_stacks() const
{
	return stacks;
}

State Game::get_game_state() const
{
	return this->game_state;
}

bool Game::apply_move(int from, int to)
{
	if (from < 0 || from >= stacks.size() || to < 0 || to >= stacks.size()) {
		return false;
	}
	
	if (stacks[from].locked || stacks[to].locked) {
		return false;
	}
	
	if (stacks[from].stack.size() == 0) {
		return false;
	}

	int from_col = stacks[from].stack.back();
	int from_cnt = 1;
	
	for (int i = stacks[from].stack.size() - 2; i >= 0; i--) {
		if (stacks[from].stack[i] != from_col) {
			break;
		}
		from_cnt++;
	}

	if (stacks[to].stack.size() + from_cnt > CUBES_PER_STACK) {
		return false;
	}

	if (stacks[to].stack.size() > 0 && stacks[to].stack.back() != from_col) {
		return false;
	}

	for (int i = 0; i < from_cnt; i++) {
		stacks[to].stack.push_back(from_col);
		stacks[from].stack.pop_back();
	}
	
	update_locks_and_status();
	if (undo_cache.size() < GAME_MAX_UNDOS) {
		undo_cache.push({ from,to, from_cnt });
	}
	return true;
}

void Game::new_game(Difficulty diff)
{
	init_game(diff);
}

Game::Game()
{
	this->game_state = State::GAME_NOT_STARTED;
	this->stacks_count = 0;
	this->colors_count = 0;
}

void Game::init_game(Difficulty diff)
{
	colors_count = get_colors_by_difficulty(diff);
	stacks_count = colors_count + 2;
	stacks = std::vector<Stack>(stacks_count);

	for (size_t i = 0; i < colors_count; i++)
	{
		stacks[i].stack = std::vector<int>();
		for (size_t j = 0; j < CUBES_PER_STACK; j++)
		{
			stacks[i].stack.push_back(i);
		}
		stacks[i].locked = false;
	}

	shuffle_stacks(colors_count * CUBES_PER_STACK * 4);

	restart_stacks = stacks;
}