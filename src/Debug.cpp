#include "Debug.h"
#include <ncurses.h>
namespace Debug{

	static std::string debugString;


	void writeStringToScreen(const std::string &toDraw){

		debugString += toDraw + '\n';
	}

	void drawToScreen(){


		printw("%s", debugString.c_str());


		move(0,0);

		refresh();

		debugString.clear();

	}

	void cleanUp(){
		endwin();
	}

	void init(){
		initscr();
	}

}
