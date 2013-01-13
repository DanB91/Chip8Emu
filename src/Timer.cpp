#include "Timer.h"
#include <SDL/SDL.h>

int Timer::getTicks(){
    if(started){
        if(paused)
            return pausedTicks;
        else
            return SDL_GetTicks() - startTicks;
    }

    return 0;
   
}

void Timer::start(){
    paused = false;
    started = true;
    startTicks = SDL_GetTicks();

}

void Timer::stop(){
    paused = false;
    started = true;
}

void Timer::pause(){

    if(started && !paused){
        pausedTicks = SDL_GetTicks() - startTicks;
        paused = true;
    }
}

void Timer::unpause(){
    if(paused && started){
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }

}
