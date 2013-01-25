#include "Keyboard.h"
#include "Debug.h"
#include "Chip8Exception.h"
#include <iostream>
#include <sstream>
#define NUM_KEYS 16

namespace Keyboard{

	static SDL_KeyboardEvent keyboardState;
	static bool keysPressed[NUM_KEYS];
	static const SDLKey keyboardKeys[] = {SDLK_x, SDLK_1, SDLK_2, SDLK_3, 
					SDLK_q, SDLK_w, SDLK_e, SDLK_a,
					SDLK_s, SDLK_d, SDLK_z, SDLK_c,
					SDLK_4, SDLK_r, SDLK_r, SDLK_v};

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


	unsigned char waitForKeyPress(){

		SDL_Event e;
		std::ostringstream os;

		while(1){
			if(!SDL_WaitEvent(&e)){
				throw Chip8Exception("Error waiting for event");
			}

			if(e.type != SDL_KEYDOWN){
				if(e.type == SDL_QUIT){
					exit(1);
				}
				continue;
			}

			for(int i = 0; i < NUM_KEYS; i++){
				if(keyboardKeys[i] == e.key.keysym.sym){
					keyboardState = e.key;	
					return i;
				}
			}

		}
		





	}

	void setState(const SDL_KeyboardEvent &state)
	{
		keyboardState = state;
	}	

	bool isKeyOnKeypadPressed(int key){
		return keysPressed[key];
	}

	void updateKeys(){

		for(int i = 0; i < NUM_KEYS; i++){
			
			if(isKeyDown(keyboardKeys[i])){
				keysPressed[i] = true;
			}

			if(isKeyUp(keyboardKeys[i])){
				keysPressed[i] = false;
			}
		}

	
	
	}
}
