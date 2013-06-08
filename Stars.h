#ifndef __STAR_H__
#define __STAR_H__

#include <GL\glut.h>
#include <GL\glaux.h>
#include <string>
using std::string;
#pragma comment( lib, "opengl32.lib")    // OpenGL32���ӿ�
#pragma comment( lib, "glu32.lib")       // GLu32���ӿ�
#pragma comment( lib, "glaux.lib")       // GLaux���ӿ�
#pragma comment( lib, "glut.lib")        // Glut���ӿ�
#define PI 3.141592653


// ��ά�ռ��еĵ�
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

// ���𻭳������������
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
	GLuint& getTextureID();	// ����id�����ã����������

public:
	Point pos;	// ��ά����
	GLdouble year;
	GLdouble day;

protected:
	string name;
	GLUquadric *quad;	// ���ڻ�������
	GLuint textureID;
	GLdouble radius;
	GLdouble orbitRadius;
	string texFile;
	
};

#endif

