#include "AsprinPiece.h"
#include "Defines.h"

#define VELOCITY			(5)
#define TOO_CLOSE_AMOUNT	(10)

//This is the moveable piece; a solid circle
static unsigned short image_Piece[] = {
    0x2a01,0x0008,0x0008,0x0000,0xffff,0xffff,0xdce6,0xdce6,0xdce6,0xdce6,
    0xffff,0xffff,0xffff,0x3186,0xdce6,0xdce6,0xdce6,0xdce6,0x3186,0xffff,
    0xdce6,0xdce6,0x3186,0xdce6,0xdce6,0x3186,0xdce6,0xdce6,0xdce6,0xdce6,
    0xdce6,0x3186,0x3186,0xdce6,0xdce6,0xdce6,0xdce6,0xdce6,0xdce6,0x3186,
    0x3186,0xdce6,0xdce6,0xdce6,0xdce6,0xdce6,0x3186,0xdce6,0xdce6,0x3186,
    0xdce6,0xdce6,0xffff,0x3186,0xdce6,0xdce6,0xdce6,0xdce6,0x3186,0xffff,
    0xffff,0xffff,0xdce6,0xdce6,0xdce6,0xdce6,0xffff,0xffff
};

AsprinPiece::AsprinPiece(SDL_Surface* pScreen)
: m_pScreen(pScreen), m_nX(0), m_nY(0)
{
	m_pPiece = nSDL_LoadImage(image_Piece);
	
	SDL_SetColorKey(m_pPiece, SDL_SRCCOLORKEY, SDL_MapRGB(m_pPiece->format, 255, 255, 255));
	
	SetUp();
}

AsprinPiece::~AsprinPiece()
{
	SDL_FreeSurface(m_pPiece);
}

void AsprinPiece::SetUp()
{
	m_nX = rand() % (SCREEN_WIDTH - BOARD_OFFSET_RIGHT - PIECE_WIDTH);
	m_nY = rand() % (SCREEN_HEIGHT - BOARD_OFFSET_BOTTOM - PIECE_HEIGHT);
}

void AsprinPiece::GetPos(int& nX, int& nY) const
{
	nX = m_nX;
	nY = m_nY;
}

bool AsprinPiece::IsCloseToPiece(bool bHorizontal, int nPos) const
{
	if( bHorizontal && abs(m_nY - nPos) < TOO_CLOSE_AMOUNT )
		return true;
	else if( !bHorizontal && abs(m_nX - nPos) < TOO_CLOSE_AMOUNT )
		return true;
	
	return false;
}

void AsprinPiece::Move(Direction eDirection)
{
	switch(eDirection)
	{
		default:
		case Up:
			if( m_nY > 0 )
				m_nY-=VELOCITY;
			break;
		
		case Down:
			if( m_nY + PIECE_HEIGHT + BOARD_OFFSET_BOTTOM < SCREEN_HEIGHT )
			m_nY+=VELOCITY;
			break;
		
		case Left:
			if( m_nX > 0 )
			m_nX-=VELOCITY;
			break;
		
		case Right:
			if( m_nX + PIECE_WIDTH + BOARD_OFFSET_RIGHT < SCREEN_WIDTH )
				m_nX+=VELOCITY;
			break;
	}	
}

void AsprinPiece::UpdateDisplay()
{
	DrawPiece(m_nX, m_nY);
}

void AsprinPiece::DrawPiece(int nX, int nY)
{
	SDL_Rect rectDest;
	rectDest.x = nX;
	rectDest.y = nY;
	rectDest.w = PIECE_WIDTH;
	rectDest.h = PIECE_HEIGHT;

    SDL_BlitSurface(m_pPiece, NULL, m_pScreen, &rectDest);
}














