//Toggle line numbers 
// Example program:
// Using SDL2 to create an application window

#include "SDL2/SDL.h"
#include <stdio.h>

#include <iostream>
//#include "SDL2/SDL_syswm.h"
#include <sys/time.h>

//int myCallback( void* userdata, SDL_Event *ev)
//{
//	printf( "%i   -%i\n", ev->type, *((int*)userdata));
//}


int main(int argc, char* argv[]) {

	struct timeval t1, t2;

	gettimeofday( &t1, NULL);

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        0,//SDL_WINDOWPOS_UNDEFINED,           // initial x position
        0,//SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1366,                               // width, in pixels
        768,                               // height, in pixels
        SDL_WINDOW_FULLSCREEN|SDL_WINDOW_RESIZABLE//SDL_WINDOW_OPENGL                  // flags - see below
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
//for( int i=0; i<20; i++)

SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (ren == NULL){
	SDL_DestroyWindow(window);
	std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}	
	
//SDL_Surface *s;
//s = SDL_CreateRGBSurface(0, 1388, 768, 32, 0, 0, 0, 0);
//s = SDL_GetWindowSurface( window);
//SDL_FillRect( s, NULL, SDL_MapRGB(s->format, 255, 0, 0));	

SDL_Rect r;
r.x=10;
r.w=10;
r.y=10;
r.h=10;
	
while( 1)
{

	//DrawRect( window, 10,10,10,10);
	gettimeofday( &t2, NULL);
//	printf( "%i\n", t2.tv_sec);

	if( t2.tv_sec-t1.tv_sec >10)
	{
		printf( "foo\n");
		break;
	}
	SDL_Event ev;
if(	SDL_PollEvent( &ev))
{
	//SDL_PumpEvents();
//	printf( ":0x%x::  --%i--\n", ev.type, ev.motion.which);

	if( ev.type == SDL_MOUSEMOTION)
		printf( "mouse: %i, %i, %i, %i\n", ev.motion.x, ev.motion.y, ev.motion.xrel, ev.motion.yrel);

	if( ev.type == SDL_MOUSEBUTTONDOWN)
	{
		printf( "MouseDown: %i, %i, %i, %i\n",ev.button.button, ev.button.state, ev.button.x, ev.button.y);

		r.x=ev.button.x;
		r.y=ev.button.y;
SDL_SetRenderDrawColor( ren, 0,0,255,255);
SDL_RenderDrawRect( ren, &r);
SDL_RenderPresent( ren);
	}

	if( ev.type == SDL_MOUSEBUTTONUP)
{		printf( "MouseUp: %i, %i, %i, %i\n",ev.button.button, ev.button.state, ev.button.x, ev.button.y);
		r.x=ev.button.x;
		r.y=ev.button.y;
SDL_SetRenderDrawColor( ren, 255,255,0,255);
SDL_RenderDrawRect( ren, &r);
SDL_RenderPresent( ren);
	
}	
}
}
    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
