#ifndef __MOON_H__
#define __MOON_H__
#include "Stars.h"

class Moon : public Stars
{
public:
	Moon(string name, GLfloat r, GLfloat or);
	~Moon();

	virtual void draw();

};


#endif