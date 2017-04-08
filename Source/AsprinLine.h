#ifndef ASPRINLINE_H
#define ASPRINLINE_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

#include "Defines.h"

#define MAX_LINES	(100)

class AsprinLine
{
public:
	enum Orientation{Verticle, Horizontal};
	AsprinLine();
	~AsprinLine();
	void Setup(Difficulty eDifficulty, Orientation eOrient, int nPos);
	
	bool IsHorizontal() const;
	bool IsVertical() const;
	int GetPosition() const;
	int GetOtherPos() const;	
	
	void Move();
	void UpdateDisplay(SDL_Surface *pSurface);
protected:
	Orientation m_eOrient;
	int m_nPos;//Coordinate it moves
	int m_nOtherCoord;
	enum Direction{Increasing, Decreasing};
	Direction m_eDirection;
	int m_nVelocity;//I made this non-static that way each line *could* go at different speeds!  For now they are all the same speed.
};

class AsprinLines
{
public:
	AsprinLines(SDL_Surface* pScreen);
	~AsprinLines();

	int GetNumberOfLines() const;

	bool LineWithPosition(bool bHorizontal, int nPos) const;
	bool CheckCollision(int nX, int nY) const;

	void Move();
	void UpdateDisplay();
	void AddLine(Difficulty eDifficulty, bool bHorizontal, int nPos);

protected:
	void DrawLine(AsprinLine& line);

protected:
	SDL_Surface	*m_pScreen;//Does not own
	AsprinLine m_Lines[MAX_LINES];//Array of AsprinLines
	int m_nNumberOfLines;
};

#endif
