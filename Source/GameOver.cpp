#include "GameOver.h"
//#include "GameBackground.h"

AsprinGameOver::AsprinGameOver(SDL_Surface* pScreen, int nScore)
: m_pScreen(pScreen), m_nScore(nScore), m_bPlayAgain(false)
{
	m_pFont = nSDL_LoadFont(NSDL_FONT_VGA, 0, NSDL_FONTCFG_DEFAULT);
	m_pFontPlayAgain = nSDL_LoadFont(NSDL_FONT_VGA, SDL_MapRGB(pScreen->format, 0, 0, 255), NSDL_FONTCFG_DEFAULT);
}

AsprinGameOver::~AsprinGameOver()
{
	nSDL_FreeFont(m_pFont);
	nSDL_FreeFont(m_pFontPlayAgain);
}

bool AsprinGameOver::PlayAgain() const
{
	return m_bPlayAgain;
}

bool AsprinGameOver::Loop()
{
	//Handle keypresses
	if( PollEvents() == false )
		return false;
	
	UpdateDisplay();
	
	return true;
}

bool AsprinGameOver::PollEvents()
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
						return false;
					break;
					
					case SDLK_SPACE:
					case SDLK_RETURN:
					case SDLK_LCTRL:
						m_bPlayAgain = true;
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

void AsprinGameOver::UpdateDisplay()
{
	nSDL_DrawString(m_pScreen, m_pFont, 125, 10, "Game Over!");
	
	nSDL_DrawString(m_pScreen, m_pFont, 115, 40, "Your score was:");
	
	nSDL_DrawString(m_pScreen, m_pFont, 155, 60, "%d", m_nScore);
	
	nSDL_DrawString(m_pScreen, m_pFontPlayAgain, 82, 80, "Press Enter to play again");
	
	SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}




