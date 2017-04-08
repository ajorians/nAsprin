#ifndef ASPRINTARGET_H
#define ASPRINTARGET_H

extern "C"
{
	#include <os.h>
	#include "SDL/SDL.h"
}

#define OBJECT_WIDTH	(16)
#define OBJECT_HEIGHT	(16)

class AsprinTarget
{
public:
	AsprinTarget(SDL_Surface* pScreen);
	~AsprinTarget();
	void Setup();
	void GetPos(int& nX, int& nY) const;

	void UpdateDisplay();

protected:
	void DrawObject(int nX, int nY);

protected:
	SDL_Surface	*m_pScreen;//Does not own
	SDL_Surface *m_pObject;
	int m_nX;
	int m_nY;
};

#endif
