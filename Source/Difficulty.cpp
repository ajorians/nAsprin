#include "Difficulty.h"
#include "GameBackground.h"

extern void draw_rectangle(SDL_Surface* Surface, Uint32 color, Uint16 x, Uint16 y, Uint16 width, Uint16 height, Uint8 lnpx );

AsprinDifficulty::AsprinDifficulty(SDL_Surface* pScreen)
: m_pScreen(pScreen), m_eChoice(Medium), m_bQuit(false)
{
	m_pBackground = nSDL_LoadImage(image_DifficultyScreen);
}

AsprinDifficulty::~AsprinDifficulty()
{
	SDL_FreeSurface(m_pBackground);
}

bool AsprinDifficulty::Loop()
{
	//Handle keypresses
	if( PollEvents() == false )
		return false;
	
	UpdateDisplay();
	
	return true;
}

bool AsprinDifficulty::ShouldQuit() const
{
	return m_bQuit;
}

Difficulty AsprinDifficulty::GetDifficulty() const
{
	return m_eChoice;
}

bool AsprinDifficulty::PollEvents()
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
						m_bQuit = true;
					return false;
					break;
					
					case SDLK_UP:
					case SDLK_8:
					case SDLK_LEFT:
					case SDLK_4:
						if( m_eChoice == Hard )
							m_eChoice = Medium;
						else if( m_eChoice == Medium )
							m_eChoice = Easy;
						break;
					
					case SDLK_DOWN:
					case SDLK_2:
					case SDLK_RIGHT:
					case SDLK_6:
						if( m_eChoice == Easy )
							m_eChoice = Medium;
						else if( m_eChoice == Medium )
							m_eChoice = Hard;
						break;
					
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

void AsprinDifficulty::UpdateDisplay()
{
	//Draw background
	SDL_BlitSurface(m_pBackground, NULL, m_pScreen, NULL);
	
	if( m_eChoice == Easy )
		draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 141, 111, 38, 22, 1);
	else if( m_eChoice == Medium )
		draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 128, 131, 61, 22, 1);
	if( m_eChoice == Hard )
		draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 140, 150, 41, 22, 1);
	
	SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}




