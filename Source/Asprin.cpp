#include "Asprin.h"
#include "GameBackground.h"

AsprinGame::AsprinGame(SDL_Surface* pScreen, Difficulty eDifficulty)
: m_pScreen(pScreen), m_Piece(pScreen), m_Object(pScreen), m_Lines(pScreen), m_eDifficulty(eDifficulty), m_nTargetsCaught(0), m_bGameOver(false)
{
	m_pBackground = nSDL_LoadImage(image_background);
	m_pFont = nSDL_LoadFont(NSDL_FONT_THIN, 0, NSDL_FONTCFG_DEFAULT);
	
	int nStartingLines = eDifficulty == Easy ? STARTING_LINES_EASY : eDifficulty == Medium ? STARTING_LINES_MEDIUM : STARTING_LINES_HARD;
	for(int i=0; i<nStartingLines; i++)
		AddLine();
}

AsprinGame::~AsprinGame()
{
	SDL_FreeSurface(m_pBackground);
	nSDL_FreeFont(m_pFont);
}

bool AsprinGame::Loop()
{
	//Handle keypresses
	if( PollEvents() == false )
		return false;
	
	//Move lines
	m_Lines.Move();
	
	//Check for collisions!
	HandleCollisions();
	
	//Update screen
	UpdateDisplay();
	
	//SDL_Delay(5);
	
	return !IsGameOver();
}

bool AsprinGame::IsGameOver() const
{
	return m_bGameOver;
}

int AsprinGame::GetScore() const
{
	return m_nTargetsCaught;
}

bool AsprinGame::PollEvents()
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
					return false;
					break;
					
					case SDLK_UP:
					case SDLK_8:
						m_Piece.Move(Up);
					break;
					
					case SDLK_DOWN:
					case SDLK_2:
						m_Piece.Move(Down);
					break;
					
					case SDLK_RIGHT:
					case SDLK_6:
						m_Piece.Move(Right);
					break;
					
					case SDLK_LEFT:
					case SDLK_4:
						m_Piece.Move(Left);
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

void AsprinGame::UpdateDisplay()
{
	//Draw background
	SDL_BlitSurface(m_pBackground, NULL, m_pScreen, NULL);
	
	//Draw score stuff
	nSDL_DrawString(m_pScreen, m_pFont, 0, SCREEN_HEIGHT-10, "Current score: %d      Number of lines: %d", m_nTargetsCaught, m_Lines.GetNumberOfLines() );
	
	//Draw moving piece
	m_Piece.UpdateDisplay();
	
	//Draw target object
	m_Object.UpdateDisplay();
	
	//Draw lines
	m_Lines.UpdateDisplay();
	
	SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void AsprinGame::HandleCollisions()
{
	int nXPiece, nYPiece;
	int nXTarget, nYTarget;
	m_Piece.GetPos(nXPiece, nYPiece);
	m_Object.GetPos(nXTarget, nYTarget);
	
	bool bWithinLeftEdge = nXTarget > nXPiece ? (nXTarget-nXPiece < PIECE_WIDTH) : true;
	bool bWithinRightEdge = nXTarget > nXPiece ? true : (nXPiece-nXTarget < OBJECT_WIDTH);
	bool bWithinTopEdge = nYTarget > nYPiece ? (nYTarget-nYPiece < PIECE_HEIGHT) : true;
	bool bWithinBottomEdge = nYTarget > nYPiece ? true : (nYPiece-nYTarget < OBJECT_HEIGHT);
	
	if( bWithinLeftEdge && bWithinRightEdge && bWithinTopEdge && bWithinBottomEdge )//Got target
	{
		m_nTargetsCaught++;
		m_Object.Setup();//Reposition target
		AddLine();
	}
	
	if( m_Lines.CheckCollision(nXPiece, nYPiece) )
	{
		//Game over
		m_bGameOver = true;
	}
}

void AsprinGame::AddLine()
{
	bool bHorizontal = rand() % 2 == 0;
	m_Lines.AddLine(m_eDifficulty, bHorizontal, GetPosition(bHorizontal));
}

int AsprinGame::GetPosition(bool bHorizontal) const
{
	int nPos;
	int nAttempts = 0;
	do
	{
		nPos = GetNewPosition(bHorizontal);
		nAttempts++;
		if( nAttempts > 50 )//Continously getting a random isn't technically an algorithm by definition
			break;//So if cannot add a line after some number of attempts; keep going.
	} while(m_Lines.LineWithPosition(bHorizontal, nPos) || m_Piece.IsCloseToPiece(bHorizontal, nPos));
	
	return nPos;
}

int AsprinGame::GetNewPosition(bool bHorizontal) const
{
	return rand() % (bHorizontal ? (SCREEN_HEIGHT - BOARD_OFFSET_BOTTOM) : (SCREEN_WIDTH - BOARD_OFFSET_RIGHT));
}














