#include "Stars.h"
#include <tchar.h>
#include <cstring>
#include <stdio.h>
#include <cmath>
extern int g_size = 12;	// 天体的个数

Stars::Stars()
{
	// 空
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
	// 空
}
void Stars::draw()
{
	glPushMatrix();
	  glRotatef(year, 0.0, 1.0, 0.0);
	  glTranslatef(orbitRadius, 0.0, 0.0);
	  glRotatef(day, 0.0, 1.0, 0.0);
	  // 绕x轴旋转-90度，矫正纹理
	  glRotatef(-90.0f, 1.0, 0.0, 0.0);
	  glBindTexture(GL_TEXTURE_2D, textureID);
	  gluSphere(quad, radius, 50, 50);
	glPopMatrix();
	updatePosition();
}

/**
 * 每次旋转后都要更新自己的位置
 */
void Stars::updatePosition()
{
	// 将旋转角度year转化成弧度
	GLdouble theta = year * (PI / 180);

	// 利用半径orbitRaidus计算坐标（极坐标->直角坐标）
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