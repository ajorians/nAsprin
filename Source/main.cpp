extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

#include "Asprin.h"
#include "Menu.h"
#include "Help.h"
#include "Difficulty.h"
#include "GameOver.h"

#define SCREEN_BIT_DEPTH        (16)
#define SCREEN_VIDEO_MODE (SDL_SWSURFACE|SDL_FULLSCREEN|SDL_HWPALETTE)

int main(int argc, char *argv[]) 
{
	printf("Initializing SDL.\n");
	
	/* Initialize the SDL library (starts the event loop) */
    if ( SDL_Init(SDL_INIT_VIDEO ) < 0 )
	{
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
	
	printf("SDL initialized.\n");
	
	SDL_Surface* pScreen = NULL;
	pScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SCREEN_VIDEO_MODE);
	
	if( pScreen == NULL )
	{
		fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SDL_GetError());
		exit(1);
	}
	else
	{
		/* Hides the cursor */
		SDL_ShowCursor(SDL_DISABLE);
		
		while(true)
		{
			bool bShowHelp = false;
			{
			SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

			AsprinMenu menu(pScreen);
			while(menu.Loop()){}
			if( menu.ShouldQuit() )
				break;
			bShowHelp = menu.ShouldShowHelp();
			}
			
			if( bShowHelp )
			{
				AsprinHelp help(pScreen);
				while(help.Loop()){}
				if( help.ShouldQuit() )
					break;
			}
			else
			{
				Difficulty eDifficulty = Medium;
				{
					AsprinDifficulty difficult(pScreen);
					while(difficult.Loop()){}
					if( difficult.ShouldQuit() )
						break;
					eDifficulty = difficult.GetDifficulty();
				}				
				
				bool bPlay = true;
				while(bPlay)
				{
					SDL_EnableKeyRepeat(10,SDL_DEFAULT_REPEAT_INTERVAL);//Want fast!
					
					AsprinGame game(pScreen, eDifficulty);
					/* Game loop */
					while(game.Loop()){}
						
					if( game.IsGameOver() )
					{
						AsprinGameOver gameover(pScreen, game.GetScore());
						while(gameover.Loop()){}
						bPlay = gameover.PlayAgain();
					}
					else//quit game
					{
						break;
					}
				}
				break;
			}
		}
	}
	
	printf("Quitting SDL.\n");
    
    /* Shutdown all subsystems */
    SDL_Quit();
    
    printf("Quitting...\n");
	
	return 0;
}
