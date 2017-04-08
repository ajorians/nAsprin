#include "Help.h"
#include "GameBackground.h"

AsprinHelp::AsprinHelp(SDL_Surface* pScreen)
: m_pScreen(pScreen), m_bShouldQuit(false)
{
	m_pBackground = nSDL_LoadImage(image_HelpScreen);
}

AsprinHelp::~AsprinHelp()
{
	SDL_FreeSurface(m_pBackground);
}

bool AsprinHelp::Loop()
{
	//Handle keypresses
	if( PollEvents() == false )
		return false;
	
	UpdateDisplay();
	
	return true;
}

bool AsprinHelp::ShouldQuit() const
{
	return m_bShouldQuit;
}

bool AsprinHelp::PollEvents()
{
	SDL_Event event;
	
	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
	/* more events on the event queue, our while loop will exit when */
	/* that occurs.                                                  */
	while( SDL_PollEvent( &event ) )
	{
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch( event.type )
		{
			case SDL_KEYDOWN:
				printf( "Key press detected\n" );
				switch (event.key.keysym.sym) 
				{
					case SDLK_ESCAPE:
						fprintf(stderr, "Hit Escape!n");
						m_bShouldQuit = true;
					return false;
					break;
					
					case SDLK_UP:
					case SDLK_8:
					case SDLK_LEFT:
					case SDLK_4:					
					case SDLK_DOWN:
					case SDLK_2:
					case SDLK_RIGHT:
					case SDLK_6:
					case SDLK_SPACE:
					case SDLK_RETURN:
					case SDLK_LCTRL:
						return false;
						break;
					
					default:
						break;
				}
				break;
			
			//Called when the mouse moves
			case SDL_MOUSEMOTION:
				break;
			
			case SDL_KEYUP:
				printf( "Key release detected\n" );
				break;
			
			default:
				break;
		}
	}
	return true;
}

void AsprinHelp::UpdateDisplay()
{
	//Draw background
	SDL_BlitSurface(m_pBackground, NULL, m_pScreen, NULL);
	
	SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}




