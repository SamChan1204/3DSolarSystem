#include "GLManager.h"
#include "Stars.h"

GLManager glmanager;


void setPerspective (GLenum mode, int x, int y)
{
	// get info about viewport (x, y, w, h)
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// set camera to view viewport area
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// check for selection
	if (mode == GL_SELECT)
	{
		// create 5x5 pixel picking region near cursor location
		gluPickMatrix(GLfloat(x), GLfloat(viewport[3] - y), 1.0, 1.0, viewport);
	}
	// view scene in perspective
	gluPerspective(60, (GLdouble)viewport[2]/(GLdouble)viewport[3], 0.1, 200);
	// prepare to work with model again
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// position user's camera
	glmanager.setCamera();
}

//鼠标点选时选择目标
void selectObject (int x, int y)
{
	// allocate enough space to store select info
	GLuint selectBuf[16];
	glSelectBuffer(16, selectBuf);

	// prepare for selection by initializing name info (0 represents a miss)
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);

	// render to select buffer instead of color buffer
	glPushMatrix();
	setPerspective(GL_SELECT, x, y);
	glmanager.displayGL();
	glPopMatrix();

	// get select info back and reset camera for viewing
	GLuint numHits = glRenderMode(GL_RENDER);
	setPerspective(GL_RENDER, 0, 0);
	if (numHits > 0)
	{
		glmanager.selectObject(numHits, selectBuf);
	}
}


void onIdle()
{
	// 静态变量，函数执行完毕后不会被销毁
	static int oldTime = 0;
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	// 控制帧速， 每秒30帧
	if (currentTime - oldTime > 15) {
		// 修改动画参数
		glmanager.animateGL();
		oldTime = currentTime;
	}
	glutPostRedisplay();
}

void init() {
	glmanager.initializeGL();
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glmanager.setCamera();
	glmanager.displayGL();

}

void reshape(int w, int h) 
{
	glmanager.reshapeGL(w, h);
}

void keyPress(unsigned char key, int x, int y)
{
	glmanager.keyPress(key, x, y);
}

void onMouseButtonPress (int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		selectObject(x, y);
	}
	glutPostRedisplay();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Mini Solar System");
	init();
	glutKeyboardFunc(keyPress);
	glutMouseFunc(onMouseButtonPress);
	glutIdleFunc(onIdle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}