#pragma once
#include <SDL/SDL.h>
#include "Chip8Exception.h"

namespace Chip8{

	void init();

	//loads the program into chip8 memeory
	void loadGame(char *fileName);
	
	//if false, sprites should be drawn during that frame
	bool shouldDraw(); 

	//steps through a cpu instruction
	void step();

	//updates Chip8 input
	void updateKeys(); 

}


