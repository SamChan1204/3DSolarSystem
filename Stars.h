#ifndef __STAR_H__
#define __STAR_H__

#include <GL\glut.h>
#include <GL\glaux.h>
#include <string>
using std::string;
#pragma comment( lib, "opengl32.lib")    // OpenGL32连接库
#pragma comment( lib, "glu32.lib")       // GLu32连接库
#pragma comment( lib, "glaux.lib")       // GLaux连接库
#pragma comment( lib, "glut.lib")        // Glut链接库
#define PI 3.141592653


// 三维空间中的点
struct Point{
	GLdouble x, y, z;
	Point() {
		x = y = z = 0.0;
	}
	Point(GLdouble x, GLdouble y, GLdouble z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Point operator+(const Point& p){
		return Point(x + p.x, y + p.y, z + p.z);
	}

	Point operator-(const Point& p){
		return Point(x - p.x, y - p.y, z - p.z);
	}

	Point operator*(GLdouble d){
		return Point(x * d, y * d, z * d);
	}

	Point operator/(GLdouble d){
		return Point(x / d, y / d, z / d);
	}

	double length(){
		return sqrt(x * x + y * y + z * z);
	}
};

// 负责画出各种天体的类
class Stars
{
public:
	Stars();
	Stars(string name, GLdouble r, GLdouble or);
	~Stars();
	virtual void draw();
	void updatePosition();
	
// 	void setOrbitRadius();
// 	void setRadius();
	GLdouble getOrbitRadius() const;
	GLdouble getRadius() const;
	const string& getName() const;
	const string& getFileName() const;
	GLuint& getTextureID();	// 返回id的引用，用于纹理绑定

public:
	Point pos;	// 三维坐标
	GLdouble year;
	GLdouble day;

protected:
	string name;
	GLUquadric *quad;	// 用于绘制天体
	GLuint textureID;
	GLdouble radius;
	GLdouble orbitRadius;
	string texFile;
	
};

#endif

