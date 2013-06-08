#ifndef __EARTH_H__
#define __EARTH_H__
#include "Stars.h"
#include "Moon.h"
#include <string>

class Earth : public Stars
{
public:
	Earth(Moon *moon, string name, GLfloat r, GLfloat or);
	~Earth();
	virtual void draw();
private:
	Stars *moon;

};

#endif