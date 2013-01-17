#pragma once
/*
 * Thank you lazyfoo!
 */

class Timer
{

    public:
        //Initializes variables
        Timer()
            :paused(false), started(false), startTicks(0), pausedTicks(0)
        {}

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        int getTicks();

        //Checks the status of the timer
        bool isStarted() { return started; }
        bool isPaused() { return paused; }     

    private:
        
	//The timer status
        bool paused;
        bool started;

	
	//The clock time when the timer started
        int startTicks;

        //The ticks stored when the timer was paused
        int pausedTicks;

       
};
