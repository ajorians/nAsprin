#ifndef GAMEOVER_H
#define GAMEOVER_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

class AsprinGameOver
{
public:
	AsprinGameOver(SDL_Surface* pScreen, int nScore);
	~AsprinGameOver();

	bool PlayAgain() const;

	bool Loop();
	
protected:
	bool PollEvents();
	void UpdateDisplay();

protected:
	SDL_Surface	*m_pScreen;//Does not own
	nSDL_Font *m_pFont;
	nSDL_Font *m_pFontPlayAgain;
	int m_nScore;
	bool m_bPlayAgain;
};

#endif
