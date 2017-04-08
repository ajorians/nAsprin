#ifndef DIFFICULTY_H
#define DIFFICULTY_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

#include "Defines.h"

class AsprinDifficulty
{
public:
	AsprinDifficulty(SDL_Surface* pScreen);
	~AsprinDifficulty();

	bool Loop();

	bool ShouldQuit() const;
	Difficulty GetDifficulty() const;
	
protected:
	bool PollEvents();
	void UpdateDisplay();

protected:
	SDL_Surface	*m_pScreen;//Does not own
	SDL_Surface *m_pBackground;
	Difficulty m_eChoice;
	bool m_bQuit;
};

#endif
