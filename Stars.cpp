#include "Stars.h"
#include <tchar.h>
#include <cstring>
#include <stdio.h>
#include <cmath>
extern int g_size = 12;	// ����ĸ���

Stars::Stars()
{
	// ��
}

Stars::Stars(string name, GLdouble r, GLdouble or)
{
	quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	texFile = "textures/" + name + ".bmp";
	textureID = (--g_size);
	printf("%s : %d\n", texFile.c_str(), textureID);
	this->name = name;
	radius = r;
	orbitRadius = or;
	year = 0.0;
	day = 0.0;
	pos = Point(0.0, 0.0, 0.0);
}
Stars::~Stars()
{
	// ��
}
void Stars::draw()
{
	glPushMatrix();
	  glRotatef(year, 0.0, 1.0, 0.0);
	  glTranslatef(orbitRadius, 0.0, 0.0);
	  glRotatef(day, 0.0, 1.0, 0.0);
	  // ��x����ת-90�ȣ���������
	  glRotatef(-90.0f, 1.0, 0.0, 0.0);
	  glBindTexture(GL_TEXTURE_2D, textureID);
	  gluSphere(quad, radius, 50, 50);
	glPopMatrix();
	updatePosition();
}

/**
 * ÿ����ת��Ҫ�����Լ���λ��
 */
void Stars::updatePosition()
{
	// ����ת�Ƕ�yearת���ɻ���
	GLdouble theta = year * (PI / 180);

	// ���ð뾶orbitRaidus�������꣨������->ֱ�����꣩
	pos.x = orbitRadius * cos(theta);
	pos.z = -orbitRadius * sin(theta);
}

const string& Stars::getName() const
{
	return name;
}

const string& Stars::getFileName() const
{
	return texFile;
}

GLuint& Stars::getTextureID() {
	return textureID;
}