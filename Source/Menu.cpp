#include "Menu.h"
#include "GameBackground.h"

AsprinMenu::AsprinMenu(SDL_Surface* pScreen)
: m_pScreen(pScreen), m_eChoice(Play)
{
	m_pBackground = nSDL_LoadImage(image_HomeScreen);
	m_pFont = nSDL_LoadFont(NSDL_FONT_THIN, 0, NSDL_FONTCFG_DEFAULT);
}

AsprinMenu::~AsprinMenu()
{
	SDL_FreeSurface(m_pBackground);
	nSDL_FreeFont(m_pFont);
}

bool AsprinMenu::Loop()
{
	//Handle keypresses
	if( PollEvents() == false )
		return false;
	
	UpdateDisplay();
	
	//Best way I have found to seed the random number
	rand();
	
	return true;
}

bool AsprinMenu::ShouldQuit() const
{
	return m_eChoice == Quit;
}

bool AsprinMenu::ShouldShowHelp() const
{
	return m_eChoice == Help;
}

bool AsprinMenu::PollEvents()
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
						m_eChoice = Quit;
					return false;
					break;
					
					case SDLK_UP:
					case SDLK_8:
					case SDLK_LEFT:
					case SDLK_4:
						if( m_eChoice == Quit )
							m_eChoice = Help;
						else if( m_eChoice == Help )
							m_eChoice = Play;
						break;
					
					case SDLK_DOWN:
					case SDLK_2:
					case SDLK_RIGHT:
					case SDLK_6:
						if( m_eChoice == Play )
							m_eChoice = Help;
						else if( m_eChoice == Help )
							m_eChoice = Quit;
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

void draw_rectangle(SDL_Surface* Surface, Uint32 color, Uint16 x, Uint16 y, Uint16 width, Uint16 height, Uint8 lnpx )
{
	SDL_Rect DestRect;

	// Draw the top line
	DestRect.x = x;
	DestRect.y = y;
	DestRect.w = width;
	DestRect.h = 1;
	SDL_FillRect (Surface, &DestRect, color);

	// Draw the bottum line
	DestRect.y = y+height-1;
	SDL_FillRect (Surface, &DestRect, color);

	// Draw the left line
	DestRect.y = y;
	DestRect.w = 1;
	DestRect.h = height;
	SDL_FillRect (Surface, &DestRect, color);

	// Draw the left line
	DestRect.x = x+width-1;
	SDL_FillRect (Surface, &DestRect, color);
}

void AsprinMenu::UpdateDisplay()
{
	//Draw background
	SDL_BlitSurface(m_pBackground, NULL, m_pScreen, NULL);
	
	if( m_eChoice == Play )
		draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 114, 152, 89, 22, 1);
	else if( m_eChoice == Help )
		draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 140, 174, 40, 22, 1);
	if( m_eChoice == Quit )
		draw_rectangle(m_pScreen, SDL_MapRGB(m_pScreen->format, 255, 0, 0), 140, 194, 40, 22, 1);
	
	SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}




