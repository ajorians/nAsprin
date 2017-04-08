#include "AsprinLine.h"
#include "Defines.h"
#include "AsprinPiece.h"//For PIECE_WIDTH && PIECE_HEIGHT

#define LINE_VELOCITY_EASY		(2)
#define LINE_VELOCITY_MEDIUM	(3)
#define LINE_VELOCITY_HARD		(5)
#define LINE_LENGTH				(10)
#define MINIMUM_SPACING			(7)//Distance between 2 lines of the same orientation

/*
 * Set the pixel at (x, y) of the specified surface to the given RGB value
 * NOTE: The surface must be locked before calling this!
 * Also, this doesn't update the screen, you'll have to do it yourself!
 */
void DrawPixel(SDL_Surface *Surface, int x, int y,Uint8 R, Uint8 G,Uint8 B)
{
    Uint32 color = SDL_MapRGB(Surface->format, R, G, B);
    Uint8 *  bufp= (Uint8 *)Surface->pixels + y*Surface->pitch + x*Surface->format->BytesPerPixel;
    switch (Surface->format->BytesPerPixel) {
        case 4:
            bufp[3] = color >> 24;
        case 3:
            bufp[2] = color >> 16;
        case 2:
            bufp[1] = color >> 8;
        case 1:
            bufp[0] = color;
    }
    return;
}

AsprinLine::AsprinLine()
: m_eOrient(Horizontal), m_nPos(0), m_nOtherCoord(0), m_eDirection(Increasing), m_nVelocity(LINE_VELOCITY_MEDIUM)
{
}

AsprinLine::~AsprinLine()
{
}

void AsprinLine::Setup(Difficulty eDifficulty, Orientation eOrient, int nPos)
{
	m_eOrient = eOrient;
	m_nPos = nPos;
	m_nOtherCoord = rand() % 
		(IsHorizontal() ?  (SCREEN_WIDTH - LINE_LENGTH - BOARD_OFFSET_RIGHT) : 
							(SCREEN_HEIGHT - LINE_LENGTH - BOARD_OFFSET_BOTTOM)
		  );
	m_nVelocity = eDifficulty == Easy ? LINE_VELOCITY_EASY : eDifficulty == Medium ? LINE_VELOCITY_MEDIUM : LINE_VELOCITY_HARD;
}

bool AsprinLine::IsHorizontal() const
{
	return m_eOrient == Horizontal;
}

bool AsprinLine::IsVertical() const
{
	return !IsHorizontal();
}

int AsprinLine::GetPosition() const
{
	return m_nPos;
}

int AsprinLine::GetOtherPos() const
{
	return m_nOtherCoord;
}

void AsprinLine::Move()
{
	//m_nPos stays the same
	if( m_eDirection == Increasing )
	{
		if( IsVertical() && m_nOtherCoord + LINE_LENGTH + m_nVelocity + BOARD_OFFSET_BOTTOM < SCREEN_HEIGHT )
			m_nOtherCoord+=m_nVelocity;
		else if( IsHorizontal() && m_nOtherCoord + LINE_LENGTH + m_nVelocity + BOARD_OFFSET_RIGHT < SCREEN_WIDTH )
			m_nOtherCoord+=m_nVelocity;
		else
			m_eDirection = Decreasing;
	}
	else
	{
		if( IsVertical() && m_nOtherCoord - m_nVelocity >= 0 )
			m_nOtherCoord-=m_nVelocity;
		else if( IsHorizontal() && m_nOtherCoord - m_nVelocity >= 0 )
			m_nOtherCoord-=m_nVelocity;
		else
			m_eDirection = Increasing;
	}
}

void AsprinLine::UpdateDisplay(SDL_Surface *pSurface)
{
	for(int i=0; i<LINE_LENGTH; i++)
		DrawPixel(pSurface, IsVertical() ? m_nPos : (m_nOtherCoord + i), 
					IsHorizontal() ? m_nPos : (m_nOtherCoord + i), 255, 0, 0);
}

/////////////////////////////////////////////////////////

AsprinLines::AsprinLines(SDL_Surface* pScreen)
: m_pScreen(pScreen), m_nNumberOfLines(0)
{
}

AsprinLines::~AsprinLines()
{
}

int AsprinLines::GetNumberOfLines() const
{
	return m_nNumberOfLines;
}

bool AsprinLines::LineWithPosition(bool bHorizontal, int nPos) const
{
	for(int i=0; i<GetNumberOfLines(); i++)
		if( m_Lines[i].IsHorizontal() == bHorizontal && abs(m_Lines[i].GetPosition() - nPos) < MINIMUM_SPACING )
			return true;
		
	return false;
}

bool AsprinLines::CheckCollision(int nX, int nY) const
{
	for(int i=0; i<GetNumberOfLines(); i++)
	{
		if( 
			(m_Lines[i].IsHorizontal() && m_Lines[i].GetPosition() >= nY && (m_Lines[i].GetPosition() - nY) <= PIECE_HEIGHT &&
				((m_Lines[i].GetOtherPos() >= nX && (m_Lines[i].GetOtherPos() - nX) <= PIECE_WIDTH) ||
				((m_Lines[i].GetOtherPos()+LINE_LENGTH) >= nX && (m_Lines[i].GetOtherPos()+LINE_LENGTH - nX) <= PIECE_WIDTH) ) ) ||		
		
		
			(m_Lines[i].IsVertical() && m_Lines[i].GetPosition() >= nX && (m_Lines[i].GetPosition() - nX) <= PIECE_WIDTH && 
				((m_Lines[i].GetOtherPos() >= nY && (m_Lines[i].GetOtherPos() - nY) <= PIECE_HEIGHT) ||
				((m_Lines[i].GetOtherPos()+LINE_LENGTH) >= nY && (m_Lines[i].GetOtherPos()+LINE_LENGTH - nY) <= PIECE_HEIGHT) ) )
		)
		return true;
	}
	return false;
}

void AsprinLines::Move()
{
	for(int i=0; i<GetNumberOfLines(); i++)
		m_Lines[i].Move();
}

void AsprinLines::UpdateDisplay()
{
	if (SDL_MUSTLOCK(m_pScreen))
		SDL_LockSurface(m_pScreen);

	for(int i=0; i<GetNumberOfLines(); i++)
		DrawLine(m_Lines[i]);

	if ( SDL_MUSTLOCK(m_pScreen) )
		SDL_UnlockSurface(m_pScreen);
}

void AsprinLines::AddLine(Difficulty eDifficulty, bool bHorizontal, int nPos)
{
	if( GetNumberOfLines() >= MAX_LINES )//Not using dynamic memory :(
		return;
	
	m_Lines[m_nNumberOfLines].Setup(eDifficulty, bHorizontal ? AsprinLine::Horizontal : AsprinLine::Verticle, nPos);
	m_nNumberOfLines++;
}

void AsprinLines::DrawLine(AsprinLine& line)
{
	line.UpdateDisplay(m_pScreen);
}














