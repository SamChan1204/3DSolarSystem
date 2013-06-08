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
	// ���Ƶ���Ĵ���
	glPushMatrix();
	  glRotatef(year, 0.0, 1.0, 0.0);
	  glTranslatef(orbitRadius, 0.0, 0.0);
	    // ��������
	  glPushMatrix();
	    glRotatef(day, 0.0, 1.0, 0.0);
	    glRotatef((GLfloat)-90.0f, 1.0, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	    gluSphere(quad, radius, 20, 20);
	  glPopMatrix();
	  // �����ϱ任�Ļ����ϻ�������
	  moon->draw();

	glPopMatrix();
	updatePosition();
}