#include <GL\glut.h>
#include "Stars.h"

#define SIZE 11
#define FRAMES 30  //ģʽ�л��䶯����Ҫ��֡��

//����״̬
enum State{GLOBAL, PAUSE, APPROACHING, VIEW_DETAIL, LEAVING};

//����ƶ�����
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
	Stars *stars[SIZE];  //��������
	State state;  //��ǰģʽ
	Point eyePos;  //�ӵ�λ��
	Point lookat;  //Ŀ��Ŀ��

	Point eyestep;  //�ӽ���Զ��Ĳ���
	Point lookstep;
	int now;
};