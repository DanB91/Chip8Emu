#include "GFX.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

namespace GFX{
	
	static char VRAM[SCREEN_WIDTH][SCREEN_HEIGHT]; //if non-zero, draw a pixel, else leave black


	//sets vram to all black (false)
	void clearVRAM(){
		for(int i = 0; i < SCREEN_WIDTH; i++){
			for(int j = 0; j < SCREEN_HEIGHT; j++){
				VRAM[i][j] = 0;
			}
		}
	}


	void drawVRAMToScreen(SDL_Surface *screen, unsigned short scale){
		SDL_Rect pixel = {0, 0, scale, scale};

		//clear the screen to black before drawing
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );


		for(int i = 0; i < SCREEN_WIDTH; i++){
			for(int j = 0; j < SCREEN_HEIGHT; j++){

				if(VRAM[i][j])
					SDL_FillRect(screen, &pixel, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF));

				pixel.y += scale;
			}

			pixel.x += scale;
			pixel.y = 0;
		}

		SDL_Flip(screen);
	}


	/*
	   Loads sprite into vram at posX and posY.  Each byte in sprite represents a row of 8 pixels
	   Each bit in each byte represents a pixel. If bit is set, draw pixel, else leave black

	   returns true if pixels have been unset from 1 to 0, else false
	 */
	bool loadSpriteToVRAM(int posX, int posY, const std::vector<unsigned char> &sprite)
	{
		unsigned char mask = 0x80;
		int x = posX, y = posY;
		bool bitsHaveBeenUnset = false;

		for(unsigned char row : sprite){

			for(int i = 0; i < 8; i++){
				
				if(VRAM[x + i][y] && !(row & mask))
					bitsHaveBeenUnset = true;
				
				VRAM[x + i][y] = (row & mask) ? 1 : 0;
				mask >>= 1;	
			}

			y++;
			mask = 0x80;


			
		}

		return bitsHaveBeenUnset;
	}

}
