#include <SDL/SDL.h>


namespace Keyboard{

	bool isKeyOnKeypadPressed(int key);

	
	unsigned char waitForKeyPress();

	void updateKeys();
	void setState(const SDL_KeyboardEvent &state);
	void init();

}
