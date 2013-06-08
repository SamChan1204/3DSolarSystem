#include "GLManager.h"
#include "Stars.h"
#include "Earth.h"
#include "Moon.h"
#include <GL\glut.h>


GLManager::GLManager()
{
	stars[0] = new Stars("sun", 4.0, 0);
	stars[1] = new Stars("mercury", 0.2, 4.3);	// 水星
	stars[2] = new Stars("venus", 0.6, 6.0);	// 金星
	stars[2]->year = 90.0;
	stars[3] = new Moon("moon", 0.03, 0.8);	// 月球
	// downcasting is ok here!
	stars[4] = new Earth((Moon*)stars[3], "earth", 0.5, 7.8);	// 地球
	stars[4]->year = 30.0;
	stars[5] = new Stars("mars", 0.6, 10.0);	// 火星
	stars[5]->year = 120.0;
	stars[6] = new Stars("jupiter", 1.0, 14.703);	// 木星
	stars[6]->year = 180.0;
	stars[7] = new Stars("saturn", 0.8, 18.039);	// 土星
	stars[7]->year = 240.0;
	stars[8] = new Stars("uranus", 0.8, 27.767);	// 天王星
	stars[8]->year = 45.0;
	stars[9] = new Stars("neptune", 0.7, 35.74);	// 海王星
	stars[10] = new Stars("universe", 60, 0);
	state = GLOBAL;  //初始状态为全局观察
	now = 0;
}

GLManager::~GLManager()
{
	for (int i = 0; i <SIZE; i++)
	{
		delete stars[i];
	}
}

void GLManager::initializeGL()
{
	glClearColor(0,0,0,0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	// 载入所有星球的纹理
	loadTextures();

	//设置摄像机
	setCamera(Point(10.0, 2.0, 10.0), Point(0.0, 0.0, 0.0));


	//设置光照及材质
	GLfloat mat_shininess [] = {50.0};
	GLfloat light_position [] = {0,0,0,1};
	GLfloat lmodel_ambient [] = {0.8,0.8,0.8,1.0};

	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	
}

void GLManager::reshapeGL(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)w/(GLdouble)h, 0.1, 200);
	glMatrixMode(GL_MODELVIEW);
}

void GLManager::displayGL()
{

	//全局模式下设置点光源，细节模式下设置平行光源便于观察
	if(state != VIEW_DETAIL){
		GLfloat light_position[] = {0, 0, 0, 1};
		glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	} else {
		GLfloat light_position[] = {-(lookat - eyePos).x, -(lookat - eyePos).y, -(lookat - eyePos).z, 0};
		glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	}

	

	//设置太阳材质的辐射光
	GLfloat sun_self_emission[] = {1, 1, 1, 1};
	glMaterialfv(GL_FRONT , GL_EMISSION , sun_self_emission);
	glLoadName(0);
	stars[0]->draw();

	//设置行星材质的辐射光
	GLfloat planet_self_emission[] = {0, 0, 0, 0};
	glMaterialfv(GL_FRONT , GL_EMISSION , planet_self_emission);
	
	
	for (int i = 1; i < SIZE - 1; i++) {
		// 月球由地球负责来画
		if (i != 3){
			glLoadName(i);
			stars[i]->draw();
		}
	}

	// 画宇宙
	glLoadName(11);
	stars[10]->draw();

	setCamera();

	// 双缓冲，切换前后缓冲区
	glFlush();
	glutSwapBuffers();
}

void GLManager::animateGL()
{
	if(state == GLOBAL){  //全局模式
		stars[1]->year += 1.0; stars[1]->day += 5.0;
		stars[2]->year += 0.5; stars[2]->day += 8.0;
		stars[3]->year += 0.4; stars[3]->day += 0.4;
		stars[4]->year += 0.2; stars[4]->day += 2.0;
		stars[5]->year += 0.1; stars[5]->day += 2.0;
		stars[6]->year += 0.08; stars[6]->day += 0.5;
		stars[7]->year += 0.06; stars[7]->day += 0.5;
		stars[8]->year += 0.035; stars[8]->day += 0.2;
		stars[9]->year += 0.02; stars[9]->day += 0.1;
	} else if(state == APPROACHING){  //接近星球（从全局模式到细节模式）
		if(now < FRAMES){
			eyePos = eyePos + eyestep;
			lookat = lookat + lookstep;
			now++;
		} else{
			state = VIEW_DETAIL;
			now = 0;
		}
	} else if(state == VIEW_DETAIL){  //细节模式下只自转
		stars[1]->day += 5.0;
		stars[2]->day += 8.0;
		stars[3]->day += 0.4;
		stars[4]->day += 2.0;
		stars[5]->day += 2.0;
		stars[6]->day += 0.5;
		stars[7]->day += 0.5;
		stars[8]->day += 0.2;
		stars[9]->day += 0.1;
	} else if(state == LEAVING){
		if(now < FRAMES) {  //从细节模式返回全局模式
			eyePos = eyePos - eyestep;
			lookat = lookat - lookstep;
			now++;
		} else{
			state = GLOBAL;
			now = 0;
		}
	}
}

//键盘输入检测
void GLManager::keyPress(unsigned char key, int x, int y)
{
	switch(key){
	case VK_SPACE:  //暂停和全局观察之间切换
		if(state == GLOBAL){
			state = PAUSE;
		} else if(state == PAUSE){
			state = GLOBAL;
		}
		break;
	case VK_ESCAPE: //从细节模式返回全局模式
		if(state == VIEW_DETAIL){
			state = LEAVING;
		}
		break;
	//摄像机的移动
	case 'w':
		moveCamera(UP);
		break;
	case 's':
		moveCamera(DOWN);
		break;
	case 'a':
		moveCamera(LEFT);
		break;
	case 'd':
		moveCamera(RIGHT);
		break;
	case 'q':
		moveCamera(FRONT);
		break;
	case 'e':
		moveCamera(BACK);
		break;
	}
}

void GLManager::loadTextures()
{
	for(int i = 0; i < SIZE; i++) {
		AUX_RGBImageRec *texImage;
		string texFile = stars[i]->getFileName();
		GLuint& textureID = stars[i]->getTextureID();
		texImage = auxDIBImageLoad(texFile.c_str());
		printf("%s: %d\n", texFile.c_str(), texImage->sizeX);
		// 创建一个纹理
		glGenTextures(1, &textureID);
		/*printf("%s's id: %d\n", textureID);*/
		// 绑定纹理到对应的id
		glBindTexture(GL_TEXTURE_2D, textureID);
		// 设置纹理信息
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texImage->sizeX, texImage->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, texImage->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		if (texImage)
		{
			if (texImage->data)
			{
				free(texImage->data);
			}
			free(texImage);
		}
	}
}

void GLManager::setCamera(Point eye, Point lookat)
{
	eyePos = eye;
	this->lookat = lookat;
	gluLookAt(
		eyePos.x, eyePos.y, eyePos.z,
		lookat.x, lookat.y, lookat.z,
		0.0, 1.0, 0.0);
}

void GLManager::setCamera()
{
	gluLookAt(
		eyePos.x, eyePos.y, eyePos.z,
		lookat.x, lookat.y, lookat.z,
		0.0, 1.0, 0.0);
}

//移动摄像机
void GLManager::moveCamera(cameraDir dir)
{
	//细节模式时禁止移动摄像机
	if(state == VIEW_DETAIL){
		return;
	}

	GLdouble dx = 0.5, dy = 0.5, dz = 0.5;
	switch(dir) {
	case UP:
		eyePos.y += dy;
		break;
	case DOWN:
		eyePos.y -= dy;
		break;
	case LEFT:
		eyePos.x -= dx;
		break;
	case RIGHT:
		eyePos.x += dx;
		break;
	//前后移动需要三维坐标同时变化
	case FRONT:
		eyePos.z -= dz;
		if(eyePos.z != 0){
			eyePos.x -= dz * (eyePos.x / eyePos.z);
			eyePos.y -= dz * (eyePos.y / eyePos.z);
		}
		break;
	case BACK:
		eyePos.z += dz;
		if(eyePos.z != 0){
			eyePos.x += dz * (eyePos.x / eyePos.z);
			eyePos.y += dz * (eyePos.y / eyePos.z);
		}
		break;
	}

}

//选择星球
void GLManager::selectObject(GLuint numSelected, GLuint selectInfo[])
{
	if((state == GLOBAL) || (state == PAUSE)){
		//获取拾取目标
		GLuint *ptr;
		ptr = (GLuint *) selectInfo; 
		ptr += 3;
		int selected = *ptr;
		// 跳过太阳
		if (selected == 0)
			return;
		
		// 跳过宇宙
		if (selected == 11)
			return;
		//printf("%d", seleted);
		
		//计算靠近步长
		lookstep = (stars[selected]->pos - lookat) / FRAMES;
		Point des = eyePos + (stars[selected]->pos - eyePos) * 9 / 10;
		eyestep = (des - eyePos) / FRAMES;
		state = APPROACHING;
	}
}