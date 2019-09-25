#include "stdafx.h"
#include "svga/svga.h"
#include "GameController.h"
#include <vector>
//This function update full screen from scrptr. The array should be at least sv_height*scrpitch bytes size;
void w32_update_screen(void *scrptr,unsigned scrpitch);

//If this variable sets to true - game will quit

extern bool game_quited;

// these variables provide access to joystick and joystick buttons
// In this version joystick is simulated on Arrows and Z X buttons

// [0]-X axis (-501 - left; 501 - right)
// [1]-Y axis (-501 - left; 501 - right)
extern int gAxis[2];
//0 - not pressed; 1 - pressed
extern int gButtons[6];


//sv_width and sv_height variables are width and height of screen
extern unsigned int sv_width,sv_height;

// main classes
GameController main_game_controller;

//These functions called from another thread, when a button is pressed or released
void win32_key_down(unsigned k){
  if(k==VK_F1) game_quited=true;
  if (k == VK_LEFT) main_game_controller.move_left();
  if (k == VK_RIGHT) main_game_controller.move_right();
}
void win32_key_up(unsigned){}

//This is default fullscreen shadow buffer. You can use it if you want to.
static unsigned *shadow_buf=NULL;


void init_game(){
  shadow_buf=new unsigned [sv_width*sv_height];
}

void close_game(){
  if(shadow_buf) delete shadow_buf;
  shadow_buf=NULL;
}



//draw the game to screen


void draw_rectangle(unsigned x, unsigned y, unsigned width, unsigned height)
{
	for (size_t i = y; i < y + height; i++)
	{
		memset(shadow_buf + i * sv_width + x, 250, width * 4);
	}
}

void draw_main_field(std::vector<std::vector<short>> field)
{
	static const unsigned block_size_width = 30;
	static const unsigned block_size_height = 30;
	static const unsigned start_x = sv_width / 2 - field[0].size() * block_size_width /2;
	static const unsigned start_y = 60;
	draw_rectangle(start_x - 20, start_y, 10, 400);
	draw_rectangle(start_x  + field[0].size()* block_size_width + 10, start_y, 10, 400);

	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[0].size(); j++)
		{
			if (field[i][j] == 0)
			{
				unsigned x = start_x + j * block_size_width;
				unsigned y = start_y + i * block_size_height;

				draw_rectangle(x, y, block_size_width, block_size_height);
			}
		}
	}

	//for (size_t i = 0; i < field.size(); i++)
	//{
	//	for (size_t j = 0; j < field[0].size(); j++)
	//	{
	//		if (field[i][j] == 0)
	//		{
	//			unsigned x = start_x + i * block_size_width;
	//			unsigned y = start_y + j * block_size_height;

	//			draw_rectangle(x, y, block_size_width, block_size_height);
	//		}
	//	}
	//}


}

void draw_game(){
  if(!shadow_buf)return;
  memset(shadow_buf,0,sv_width*sv_height*4);
  
  //here you should draw anything you want in to shadow buffer. (0 0) is left top corner

  //draw_rectangle(100, 30, 100, 100);
  std::vector<std::vector<short>> main_field = main_game_controller.get_draw_field();
  draw_main_field(main_field);


  w32_update_screen(shadow_buf,sv_width*4);
}

//act the game. dt - is time passed from previous act
void act_game(float dt)
{
	static const  float time_interval = 0.5;
	static float time_to_move = 0;
	time_to_move += dt;
	//move every time_interval seconds
	if (time_to_move > time_interval)
	{
		time_to_move = 0;
		main_game_controller.move_shape();


	}
}
