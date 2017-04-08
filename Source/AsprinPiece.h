#ifndef ASPRINPIECE_H
#define ASPRINPIECE_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

#define PIECE_WIDTH			(8)
#define PIECE_HEIGHT		(8)

enum Direction{Up, Down, Left, Right};

class AsprinPiece
{
public:
	AsprinPiece(SDL_Surface* pScreen);
	~AsprinPiece();
	void SetUp();
	void GetPos(int& nX, int& nY) const;

	bool IsCloseToPiece(bool bHorizontal, int nPos) const;

	void Move(Direction eDirection);
	void UpdateDisplay();

protected:
	void DrawPiece(int nX, int nY);

protected:
	SDL_Surface	*m_pScreen;//Does not own
	SDL_Surface *m_pPiece;
	int m_nX;
	int m_nY;
};

#endif
