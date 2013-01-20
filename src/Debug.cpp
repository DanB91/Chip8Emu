#include "Debug.h"
#include <ncurses.h>
#include <stdio.h>
namespace Debug{

	static std::string debugString;
	static bool isOn = false;
	static FILE *log;

	void writeStringToScreen(const std::string &toDraw){
			if(isOn){
				debugString += toDraw + '\n';
			}
	}

	void drawToScreen(){

		if(isOn){
			printw("%s", debugString.c_str());
			fprintf(log, "%s", debugString.c_str());

			move(0,0);

			refresh();

			debugString.clear();
		}
	}

	void turnOff(){
		isOn = false;
		fclose(log);
		endwin();
	}

	void turnOn(){
		isOn = true;
		log = fopen("log.txt", "w");
		initscr();
	}

}
