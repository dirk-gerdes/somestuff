//Toggle line numbers 
// Example program:
// Using SDL2 to create an application window

#include "SDL2/SDL.h"
#include <stdio.h>
//#include "SDL2/SDL_syswm.h"


int myCallback( void* userdata, SDL_Event *ev)
{
	printf( "%i   -%i\n", ev->type, *((int*)userdata));
}


int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        0,//SDL_WINDOWPOS_UNDEFINED,           // initial x position
        0,//SDL_WINDOWPOS_UNDEFINED,           // initial y position
        800,                               // width, in pixels
        600,                               // height, in pixels
        0//SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
	int i=5;
//	SDL_AddEventWatch(myCallback, &i);


//	SDL_SysWMinfo info;


    // The window is open: enter program loop (see SDL_PollEvent)
for( int i=0; i<20; i++)
{
	SDL_Event ev;
	SDL_PollEvent( &ev);
	//SDL_PumpEvents();
	printf( ":0x%x:%i:  --%i--\n", ev.type, ev.type, ev.motion.which);
}
    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
