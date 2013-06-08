#include "Earth.h"
#include "Moon.h"
Earth::Earth(Moon *moon, string name, GLfloat r, GLfloat or)
	: Stars(name, r, or)
{
	this->moon = moon;
}

Earth::~Earth()
{
}

void Earth::draw()
{
	// 绘制地球的代码
	glPushMatrix();
	  glRotatef(year, 0.0, 1.0, 0.0);
	  glTranslatef(orbitRadius, 0.0, 0.0);
	    // 矫正纹理
	  glPushMatrix();
	    glRotatef(day, 0.0, 1.0, 0.0);
	    glRotatef((GLfloat)-90.0f, 1.0, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	    gluSphere(quad, radius, 20, 20);
	  glPopMatrix();
	  // 在以上变换的基础上绘制月球
	  moon->draw();

	glPopMatrix();
	updatePosition();
}