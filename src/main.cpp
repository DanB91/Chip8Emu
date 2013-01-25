#include <SDL/SDL.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>
#include "Chip8.h"
#include "GFX.h"
#include "Debug.h"
#include "Timer.h"
#include "Keyboard.h"

#define MIN_ARGS 2

static SDL_Event event; //represents an event such as a keypress or quititng the game
static SDL_Surface *screen; //represents the screen
static bool running = true; //tells whether the emulator is running
static int currentFPS = 0; //current frames per second

static void printUsageAndExit(){
	std::cout << "Usage: chip8emu [game] [-d][-c cyles_per_second]\n";
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
			case SDL_KEYUP:
				Keyboard::setState(event.key);
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

	SDL_WM_SetCaption("CHIP-8 Emulator", NULL);

}


static void cleanUp(){
	Debug::turnOff();
	SDL_FreeSurface(screen);
	SDL_Quit();
}

static void printDebug(){
	std::ostringstream oss;
	oss << "FPS: " << currentFPS << '\n';

	Debug::writeStringToScreen(oss.str());

}

static void startExecLoop(){
	int frames = 0; //used to calculate frames per second
	Timer fps, update;

	fps.start();
	update.start();

	while(running)
	{
		Debug::drawToScreen();
		
		Chip8::step();

		if(Chip8::shouldDraw())
			GFX::drawVRAMToScreen(screen, 10);

		handleSDLEvents();

		Keyboard::updateKeys();

		if(update.getTicks() > 1000){

			currentFPS = frames / (fps.getTicks() / 1000.0);
			update.start();
		}

		frames++;

		printDebug();	




	}

}


static std::map<std::string, std::string> parseArguments(int argc, char **argv)
{
	std::map<std::string, std::string> arguments;
	arguments["clockSpeed"] = "120";
	arguments["debug"] = "false";

	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			switch(argv[i][1])
			{
				case 'c':
					if(i + 1 < argc){
						 arguments["clockSpeed"] = argv[++i];
					}

					break;
				case 'd':
					arguments["debug"] = "true";
					break;
				default:
					printUsageAndExit();
			}

		}
		else{
			arguments["gamePath"] = argv[i];
		}
		
	}

	return arguments;
}



static void init(int argc, char **argv){

	int width = 640, height = 320;
	std::map<std::string, std::string> args = parseArguments(argc, argv);
	
	try{	
		const char *gamePath = args.at("gamePath").c_str();	
		bool debugFlag = args.at("debug") == "true";
		int clockSpeed = atoi(args.at("clockSpeed").c_str());



		initSDL(width, height);
		Chip8::init(clockSpeed);
		Chip8::loadGame(gamePath);

		if(debugFlag){
			Debug::turnOn();
		}
	}
	catch(std::out_of_range &){
		printUsageAndExit();
	}

	Keyboard::init();

}

int main(int argc, char **argv)
{

	try{
		init(argc, argv);
		startExecLoop();
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
