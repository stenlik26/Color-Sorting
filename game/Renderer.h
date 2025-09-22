#ifndef _RENDERER_H
#define _RENDERER_H
#include "Platform.h"
#include <raylib.h>
#include "Utils.h"

const int mapping[] =
{
	KEY_Q,		// 0
	KEY_W,		// 1
	KEY_E,		// 2
	KEY_R,		// 3
	KEY_T,		// 4
	KEY_A,		// 6
	KEY_S,		// 7
	KEY_D,		// 8
	KEY_F,		// 9
	KEY_G,		// A
};

class Renderer {
	Platform* game_platform;
	
	int screen_w, screen_h;
	int stack_frame_w, stack_frame_h;

	int selected_stack;

	Texture2D texture_blocks[10];
	Rectangle texture_rect;
	Vector2 texture_origin;

	Rectangle stack_frames[10];

	void load_textures();
	void unload_textures();

	//void setup_font();
		//Font custom_font;
	//Rectangle calculate_button_size(const char* text, int x_offset); 

	void draw_stacks();
	void draw_stack(const Stack& stack,int i, bool selected);
	void handle_keyboard();
	void handle_mouse();

public:
	Renderer(Platform* stacksPlatform);
	~Renderer();

	bool render();
};
#endif // !_RENDERER_H
