#ifndef HELP_H
#define HELP_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

class AsprinHelp
{
public:
	AsprinHelp(SDL_Surface* pScreen);
	~AsprinHelp();

	bool Loop();

	bool ShouldQuit() const;
	
protected:
	bool PollEvents();
	void UpdateDisplay();

protected:
	SDL_Surface	*m_pScreen;//Does not own
	SDL_Surface *m_pBackground;
	bool m_bShouldQuit;
};

#endif
