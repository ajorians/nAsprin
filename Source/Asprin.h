#ifndef ASPRIN_H
#define ASPRIN_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

#include "AsprinPiece.h"
#include "AsprinTarget.h"
#include "AsprinLine.h"
#include "Defines.h"

class AsprinGame
{
public:
	AsprinGame(SDL_Surface* pScreen, Difficulty eDifficulty);
	~AsprinGame();

	bool Loop();
	bool IsGameOver() const;
	int GetScore() const;
	
protected:
	bool PollEvents();
	void UpdateDisplay();
	void HandleCollisions();
	void AddLine();
	int GetPosition(bool bHorizontal) const;//Gets position of a new line
	int GetNewPosition(bool bHorizontal) const;

protected:
	SDL_Surface	*m_pScreen;//Does not own
	SDL_Surface *m_pBackground;
	nSDL_Font *m_pFont;
	AsprinPiece m_Piece;
	AsprinTarget m_Object;
	AsprinLines m_Lines;
	Difficulty m_eDifficulty;
	int m_nTargetsCaught;
	bool m_bGameOver;
};

#endif
