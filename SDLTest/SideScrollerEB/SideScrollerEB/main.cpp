//
//  main.cpp
//  SideScrollerEB
//
//  Created by James Nguyen on 4/30/13.
//  Copyright (c) 2013 James Nguyen. All rights reserved.
//

#include <iostream>
#include "SDL.h"


void basic_function();


int main( int argc, char* args[] )
{
    //The images
    SDL_Surface* hello = NULL;
    SDL_Surface* screen = NULL;
    
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    
    //Set up screen
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    
    //Load image
    hello = SDL_LoadBMP( "/Users/james/Developer/EBSideScroller/SideScrollerEB/SideScrollerEB/hello.bmp" );
    
    //Apply image to screen
    SDL_BlitSurface( hello, NULL, screen, NULL );
    
    //Update Screen
    SDL_Flip( screen );
    
    //Pause
    SDL_Delay( 2000 );
    
    //Free the loaded image
    SDL_FreeSurface( hello );
    
    //Quit SDL
    SDL_Quit();
    
    return 0;
}

void basic_function() {

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    
    //Create an SDL_Surface and display it
    SDL_Surface* screen = NULL;
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    
    //wait 2 seconds
    SDL_Delay( 2000 );
    
    //Quit SDL (this also cleans up the SDL_Surface
    //data - so never fear, we aren't leaking :)
    SDL_Quit();
    
    
}
