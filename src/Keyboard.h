#include <SDL/SDL.h>


namespace Keyboard{

	bool isKeyOnKeypadPressed(int key);

	
	SDLKey waitForKeyPress();

	void updateKeys();
	void setState(const SDL_KeyboardEvent &state);
	void init();

}
