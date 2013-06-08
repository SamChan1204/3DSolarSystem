#include <GL\glut.h>
#include "Stars.h"

#define SIZE 11
#define FRAMES 30  //模式切换间动画需要的帧数

//各种状态
enum State{GLOBAL, PAUSE, APPROACHING, VIEW_DETAIL, LEAVING};

//相机移动方向
enum cameraDir{UP, DOWN, LEFT, RIGHT, FRONT, BACK};

class GLManager 
{
public:
	GLManager();
	~GLManager();
	void initializeGL();
	void reshapeGL(int w, int h);
	void displayGL();
	void animateGL();
	void keyPress(unsigned char key, int x, int y);
	void loadTextures();
	void moveCamera(cameraDir dir);
	void setCamera(Point eye, Point lookat);
	void setCamera();
	void selectObject(GLuint numSelected, GLuint selectInfo[]);

private:
	Stars *stars[SIZE];  //各个星球
	State state;  //当前模式
	Point eyePos;  //视点位置
	Point lookat;  //目视目标

	Point eyestep;  //接近或远离的步长
	Point lookstep;
	int now;
};