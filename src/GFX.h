#pragma once
#include <vector>
#include <SDL/SDL.h>
namespace GFX{

	bool loadSpriteToVRAM(int posX, int posY, const std::vector<unsigned char> &sprite);
	void drawVRAMToScreen(SDL_Surface *screen, unsigned short scale);
	void clearVRAM();
	
}
