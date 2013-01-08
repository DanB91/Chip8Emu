#include <SDL/SDL.h>


namespace Chip8{

	//loads the program into chip8 memeory
	void loadGame(char *fileName);

	
	//steps through a cpu instruction
	void step();

	//updates Chip8 input
	void updateKeys(); 

			
}
