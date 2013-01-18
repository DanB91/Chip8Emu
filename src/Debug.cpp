#include "Debug.h"
#include <ncurses.h>
namespace Debug{

	static std::string debugString;
	static bool isOn = false;

	void writeStringToScreen(const std::string &toDraw){
			if(isOn){
				debugString += toDraw + '\n';
			}
	}

	void drawToScreen(){

		if(isOn){
			printw("%s", debugString.c_str());


			move(0,0);

			refresh();

			debugString.clear();
		}
	}

	void turnOff(){
		isOn = false;
		endwin();
	}

	void turnOn(){
		isOn = true;
		initscr();
	}

}
