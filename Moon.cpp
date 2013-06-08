#include "Moon.h"

Moon::Moon(string name, GLfloat r, GLfloat or)
	: Stars(name, r, or)
{
	// 空
}

Moon::~Moon()
{

}

void Moon::draw()
{
	// 绘制月亮的代码
	glRotatef(year, 0.0, 1.0, 0.0);
	glTranslatef(orbitRadius, 0.0, 0.0);
	
	glPushMatrix();
	  glRotatef(day, 0.0, 1.0, 0.0);
	  glRotatef((GLfloat)-90.0f, 1.0, 0.0, 0.0);
	  glBindTexture(GL_TEXTURE_2D, textureID);
	  gluSphere(quad, 0.1, 50, 50);
	glPopMatrix();
	
	updatePosition();
};