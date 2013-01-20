#include "Keyboard.h"
#define NUM_KEYS 16

namespace Keyboard{

	static SDL_KeyboardEvent keyboardState;
	static bool keysPressed[NUM_KEYS];

	static void resetKeys(){
		for(int i = 0; i < NUM_KEYS; i++){
			keysPressed[i] = false;
		}

	}

	static bool isKeyDown(SDLKey key)
	{
		if(keyboardState.state == SDL_PRESSED && keyboardState.keysym.sym == key)
			return true;

		return false;		
	}	
	
	static bool isKeyUp(SDLKey key)
	{
		if(keyboardState.state == SDL_RELEASED && keyboardState.keysym.sym == key)
			return true;

		return false;		
	}


	void init(){
		resetKeys();
	}


	SDLKey waitForKeyPress(){

		SDL_Event e;

		while(SDL_PollEvent(&e) && e.type != SDL_KEYDOWN)
			;

		keyboardState = e.key;

		return keyboardState.keysym.sym;


	}

	void setState(const SDL_KeyboardEvent &state)
	{
		keyboardState = state;
	}	

	bool isKeyOnKeypadPressed(int key){
		return keysPressed[key];
	}

	void updateKeys(){


	
		int keyPressed = 
			(isKeyDown(SDLK_1)) ? 1 :
			(isKeyDown(SDLK_2)) ? 2 :
			(isKeyDown(SDLK_3)) ? 3 : 
			(isKeyDown(SDLK_4)) ? 0xC : 
			(isKeyDown(SDLK_q)) ? 4 : 
			(isKeyDown(SDLK_w)) ? 5 : 
			(isKeyDown(SDLK_e)) ? 6 : 
			(isKeyDown(SDLK_r)) ? 0xD : 
			(isKeyDown(SDLK_a)) ? 7 :
			(isKeyDown(SDLK_s)) ? 8 : 
			(isKeyDown(SDLK_d)) ? 9 : 
			(isKeyDown(SDLK_f)) ? 0xE : 
			(isKeyDown(SDLK_z)) ? 0xA : 
			(isKeyDown(SDLK_x)) ? 0 :
			(isKeyDown(SDLK_c)) ? 0xB : 
			(isKeyDown(SDLK_v)) ? 0xF : 
			-1;
	int keyReleased = 
			(isKeyUp(SDLK_1)) ? 1 :
			(isKeyUp(SDLK_2)) ? 2 :
			(isKeyUp(SDLK_3)) ? 3 : 
			(isKeyUp(SDLK_4)) ? 0xC : 
			(isKeyUp(SDLK_q)) ? 4 : 
			(isKeyUp(SDLK_w)) ? 5 : 
			(isKeyUp(SDLK_e)) ? 6 : 
			(isKeyUp(SDLK_r)) ? 0xD : 
			(isKeyUp(SDLK_a)) ? 7 :
			(isKeyUp(SDLK_s)) ? 8 : 
			(isKeyUp(SDLK_d)) ? 9 : 
			(isKeyUp(SDLK_f)) ? 0xE : 
			(isKeyUp(SDLK_z)) ? 0xA : 
			(isKeyUp(SDLK_x)) ? 0 :
			(isKeyUp(SDLK_c)) ? 0xB : 
			(isKeyUp(SDLK_v)) ? 0xF : 
			-1;

		if(keyPressed != -1){
			keysPressed[keyPressed] = true;
		}
		
		if(keyReleased != -1){
			keysPressed[keyReleased] = false;
		}

	}
}
