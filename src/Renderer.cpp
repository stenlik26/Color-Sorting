#include "Renderer.h"
#include <string>
#include <algorithm>

const Color background = { 39,40,34,255 };
const Color stack_frame_bg = { 31,31,31,255 };
const Color stack_frame_selected_bg = { 61,61,61,255 };
const Color stack_frame_locked = {50,80,0,255 };

bool Renderer::render()
{
	if (WindowShouldClose())
		return false;

	BeginDrawing();

	ClearBackground(background);

	handle_keyboard();
	handle_mouse();

	draw_stacks();

	EndDrawing();

	return true;
}

void Renderer::handle_mouse()
{
	Vector2 mouse_pos = GetMousePosition();
	for (int i = 0; i < STACKS_TOTAL; i++) {
		if (CheckCollisionPointRec(mouse_pos, stack_frames[i]) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			if (selected_stack != -1)
			{
				game_platform->apply_move(selected_stack, i);
				selected_stack = -1;
				continue;
			}

			selected_stack = i;
		}
	}
}

void Renderer::handle_keyboard() 
{
	for (int key = 0; key < 10; key++)
	{
		if (IsKeyReleased(mapping[key])) {

			if (selected_stack != -1) {
				game_platform->apply_move(selected_stack, key);
				selected_stack = -1;
				continue;
			} 

			selected_stack = key;
		}
	}

	if (IsKeyReleased(KEY_BACKSLASH))
	{
		game_platform->restart_game();
	}

	if (IsKeyReleased(KEY_BACKSPACE))
	{		
		game_platform->undo();
	}
}

void Renderer::load_textures()
{
	for (size_t i = 1; i <= TEXTURE_BLOCK_COUNT; i++)
	{
		std::string path = "resources/" + std::to_string(i) + ".png";
		texture_blocks[i - 1] = LoadTexture(path.c_str()); 
	}

	texture_rect = Rectangle{ 0,0, (float)texture_blocks[0].width, (float)texture_blocks[0].height };
	texture_origin = Vector2{ 0,0 };
}

void Renderer::unload_textures()
{
	for (size_t i = 1; i <= TEXTURE_BLOCK_COUNT; i++)
	{
		UnloadTexture(texture_blocks[i - 1]);
	}
}

Rectangle get_rect_by_val(int x, int y, int w, int h) {
	return Rectangle{
		(float)x,
		(float)y,
		(float)w,
		(float)h
	};
}

void Renderer::draw_stack(const Stack& stack, int i, bool selected) {

	Color frame_bg_color = stack_frame_bg;

	if (selected) {
		frame_bg_color = stack_frame_selected_bg;
	}
	if (stack.locked) {
		frame_bg_color = stack_frame_locked;
	}

	DrawRectangleRec(stack_frames[i], frame_bg_color);

	int block_x = stack_frames[i].x + (stack_frames[i].width / 2) - (BLOCK_WIDTH / 2);
	int block_y = stack_frames[i].y - BLOCK_HEIGHT / 5;

	for (int j = 0; j < stack.stack.size(); j++)
	{
		DrawTexturePro(
			texture_blocks[stack.stack[j]], 
			texture_rect,
			get_rect_by_val(block_x, block_y + ((5-j) * BLOCK_OFFSET_Y), BLOCK_WIDTH, BLOCK_HEIGHT),
			texture_origin, 
			0, 
			WHITE
		);
	}
}

void Renderer::draw_stacks()
{
	const std::vector<Stack>& stacks = game_platform->get_stacks();

	for(int i = 0; i < stacks.size(); i++)
	{
		if (i >= stacks.size()) {
			break;
		}

		draw_stack(stacks[i],i, selected_stack == i);
	}
	
}

Renderer::Renderer(Platform* stacksPlatform)
{
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	InitWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "Minesweeper Raylib");

	InitAudioDevice();

	SetTargetFPS(120);

	this->game_platform = stacksPlatform;
	screen_w = GetScreenWidth();
	screen_h = GetScreenHeight();

	stack_frame_h = screen_h / STACKS_PER_COL;
	stack_frame_w = screen_w / STACKS_PER_ROW;

	selected_stack = -1;

	int i = 0;
	for (size_t r = 0; r < STACKS_PER_COL; r++) {
		for (size_t c = 0; c < STACKS_PER_ROW; c++)
		{
			stack_frames[i++] = {
				(float)(c * stack_frame_w) + STACK_FRAME_MARGIN,
				(float)(r * stack_frame_h) + STACK_FRAME_MARGIN,
				(float)stack_frame_w - 2 * STACK_FRAME_MARGIN,
				(float)stack_frame_h - 2 * STACK_FRAME_MARGIN
			};
		}
	}

	load_textures();

	//setup_font();
}

Renderer::~Renderer()
{
	//UnloadFont(custom_font);
	unload_textures();

	CloseAudioDevice();

	CloseWindow();
}
