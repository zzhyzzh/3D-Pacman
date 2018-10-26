#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include "stdafx.h"
#include "object.h" 
#include "move.h"
#include "openAnima.h"
#include "draw.h"
#include "control.h"
#include "ghost.h"
#include "music.h"

GLfloat light_position[] = { 30.0f,30.0f,25.0f,0.0f };
GLfloat light_direction[] = { 30.0f,30.0f,0.0f };
GLfloat light_diffuse[] = { 1.0f,0.9f,0.9f,0.0f };

int point = 0;
GLfloat x = 30.0;
GLfloat y = 50.0;
GLfloat z = 0;
GLfloat lightExp = 10.0;
bool isFirstView = true;
int isOver = 0;
int restart = 0;
int isSuccess = 0;
int colorState = 0;
double dAngle = 0.0;
using namespace std;
pacMan pac;

Vertex ghostV[10];
int num[100] = { 
375,150, 375,150,  
375,375,  
375,250,375,250,  
425,100,100,425,   
462,462,  
250,125,125,250,  
125,400,400,125 };
GLfloat dx1 = 0, dy1 = 0, dz1 = 0;

//float eyePX = 0.0f;
//float eyePY = 0.0f;
//float eyePZ = 0.0f;
//float viewDX = 1.0f;
//float viewDY = 0.0f;
//float viewDZ = 0.0f;

void myDisplay();

void myIdle()
{
	Sleep(10);
	//cout <<dx <<dy <<dz <<endl;
	glutPostRedisplay();
}

void myReshape(int width, int height)
{
	aspect = (float)width / (height ? height : 1);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, aspect, 1, 10000);
}

void setLight()
{
	GLfloat light_ambient[] = { 0.0f,0.0f,0.0f,0.0f };

	GLfloat light_specular[] = { 1.0f,1.0f,1.0f,0.0f };


	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, lightExp);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 120.0f);


	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
void init()
{
	for (int i = 0; i <= 69; i++)
	{
		for (int j = 0; j <= 59; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
	ShowCursor(FALSE);
	pac.init();
	ReadObj(cd, ".\\youling\\youling.obj", objmap, objname, matname);
	setLight();

}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyePX, eyePY, eyePZ, viewDX, viewDY, viewDZ, 0, 0, 1);
	//glMatrixMode(GL_MODELVIEW);

	if (!gameEntering)//开场动画播放
	{
		openning(eyePX, eyePY);
	}
	else if (!gameStart)
	{
		entering(eyePX, eyePY, eyePZ, gameStart);
	}

	if (colorState == 0)
	{
		light_diffuse[2] = 0.9;
		light_diffuse[1] = 0.9;
		setLight();
	}
	else if (colorState == 1)
	{
		light_diffuse[2] = 0.5;
		light_diffuse[1] = 0.5;
		setLight();
	}
	else if (colorState == 2)
	{
		light_diffuse[2] = 0;
		light_diffuse[1] = 0;
		setLight();
	}
	cos_alpha = pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY), v) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY) + (viewDZ - eyePZ)*(viewDZ - eyePZ), v);
	if ((viewDX - eyePX == 0) && (viewDY - eyePY == 0))
		sin_theta = 0;
	else
		sin_theta = (viewDY - eyePY) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY), v);
	if ((viewDX - eyePX == 0) && (viewDY - eyePY == 0))
		cos_theta = 0;
	else
		cos_theta = (viewDX - eyePX) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY), v);
	if ((viewDX - eyePX == 0) && (viewDZ - eyePZ == 0))
		sin_phi = 0;
	else
		sin_phi = (viewDZ - eyePZ) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDZ - eyePZ)*(viewDZ - eyePZ), v);
	if (!capableToFly)
	{
		x = eyePX + 2.0*cos_alpha*cos_theta;
		y = eyePY + 2.0*cos_alpha*sin_theta;
	}
	Vertex v;
	if (isFirstView)
	{
		v.x = eyePX;
		v.y = eyePY;
	}
	else
	{
		v.x = x;
		v.y = y;
	}
	if (overDetection(v))   //检测是否游戏结束
	{
		isOver = 1;
	}
	if (point == 273)
	{
		FSOUND_Stream_Play(FSOUND_FREE, victory);
		isSuccess = 1;
	}
	if (!isOver && !isSuccess)
	{
		if (gameStart && !capableToFly)
		{
			ghost1Move();
			ghost2Move();
			ghost3Move();
			ghost4Move();
			ghost5Move();
			ghost6Move();
			ghost7Move();
		}

		maze::drawMaze();
		drawGhost();
		sky::drawSky();
		coin::DrawBean(0.5);
		score::display();
		if (!isFirstView || capableToFly)
			pac.draw();
	}
	else
	{
		if (isSuccess)
		{
			success::drawScene();
		}
		else if(isOver)
			over::drawScene();
		if (restart)
		{
			eyePX = 100;
			eyePY = 100;
			eyePZ = 40;
			viewDX = 30;
			viewDY = 30;
			viewDZ = 0;
			point = 0;
			gameEntering = false;
			gameStart = false;
			for (int i = 0; i <= 69; i++)
			{
				for (int j = 0; j <= 59; j++)
				{
					matrix[i][j] = mat[i][j];
				}
			}
			isOver = 0;
			isSuccess = 0;
			restart = 0;
			isFirstView = true;
		}
	}
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);	//对glut的初始化   

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);	//初始化显示模式:RGB颜色模型，深度测试，双缓冲     
																//glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

	glutInitWindowSize(1280, 720);//设置窗口大小   

	int windowHandle = glutCreateWindow("Simple GLUT App");//设置窗口标题
	SetCursorPos(1280 / 2, 720 / 2);//鼠标在界面中心
									//SetCamera(0, 0);
	glutReshapeFunc(&myReshape); // 注册重绘回调函数

	glutDisplayFunc(&myDisplay);//注册绘制回调函数   
	glutKeyboardFunc(&myKeyboard);//注册按键回调函数 

	glutMouseFunc(&myMouse);
	glutPassiveMotionFunc(&MouseMove);//鼠标移动
	glutMotionFunc(&myMotion);


	glutIdleFunc(&myIdle);//注册全局回调函数：空闲时调用  

	init();
	sky::init();
	maze::init();
	InitFMOD();
	FSOUND_Stream_Play(FSOUND_FREE, mp3back);
	glutMainLoop();// glut事件处理循环

	return 0;
}
