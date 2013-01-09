#include <SDL/SDL.h>
#include <iostream>
#include <ncurses.h>
#include "Chip8.h"

#define MIN_ARGS 2

static SDL_Event event; //represents an event such as a keypress or quititng the game
static SDL_Surface *screen; //represents the screen
static bool running = true; //tells whether the emulator is running

static void printUsageAndExit(){
	std::cout << "Usage: chip8emu file [resolution]\n";
	exit(1);
}

static void handleSDLEvents()
{
    while(SDL_PollEvent(&event))
    {
	switch(event.type)
	{
	    case SDL_QUIT:
		running = false;
		return;
	    case SDL_KEYDOWN:
		break;
	    case SDL_KEYUP:
		break;
	}


    }
}


/*
   Initializes the SDL library and screen
   @oarams width, height: Width and height of the screen
 */
static void initSDL(int width, int height)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw Chip8Exception("SDL init failed");

	if((screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
		throw Chip8Exception("Screen initialization failed");

}

void drawDebugOutput(){
	printw("%s", Chip8::getCPUStatus().c_str());

	move(0,0);
	refresh();

}

static void cleanUp(){
	endwin();
	SDL_FreeSurface(screen);
	SDL_Quit();
}


int main(int argc, char **argv)
{
	int width = 640, height = 320;

	if(argc < MIN_ARGS) printUsageAndExit();
	
	try{
		initSDL(width, height);
		Chip8::init();
		Chip8::loadGame(argv[1]);
		initscr();

		while(running)
		{
			drawDebugOutput();	
			handleSDLEvents();
			Chip8::step();
			Chip8::updateKeys();
		}
		
		cleanUp();

	}
	catch(std::exception &e)
	{
		cleanUp();
		std::cout << e.what() << '\n';
		return 1;
	}



	return 0;
}
