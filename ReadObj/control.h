#pragma once
#include<math.h>
#include<iostream>
#include"gl\glut.h"
#include"move.h"
#include"screenShot.h"

using namespace std;
//定义滚轮操作 
#define  GLUT_WHEEL_UP 3            
#define  GLUT_WHEEL_DOWN 4 

float eyePX = 100;
float eyePY = 100;
float eyePZ = 40;
float viewDX = 30;
float viewDY = 30;
float viewDZ = 0;

GLint MouseDown = 0;
bool gameEntering = false;
bool gameStart = false;
bool capableToFly = false;
extern bool isFirstView;
extern double dAngle;
extern int isOver;
extern int isSuccess;
extern int restart;
extern int colorState;
GLfloat dx = 0, dy = 0, dz = -1.0f;
GLfloat ax = 0, ay = 0, az = 0;
GLint mx = 640, my = 360;

float DEG_TO_RAD = 0.017453f;
float tmpx, tmpy,tmpz;

POINT mousePos;
extern GLfloat dx1, dy1, dz1;
extern void myDisplay();
extern GLfloat light_position[];
extern GLfloat light_direction[];
extern GLfloat lightExp;

int mazeWall = 1;

void myKeyboard(unsigned char key, int x, int y)
{
	Vertex ver;
	double tx, ty, tz;

	//游戏开场画面部分
	if (key)
	{
		gameEntering = true;
	}
	if (key == 27)
	{
		exit(0);
	}//退出
	if (gameStart && !isOver && !isSuccess)//游戏开始
	{
		switch (key)
		{
			//切换移动方式
		case 'p':
		{
			capableToFly = !capableToFly;
			if (capableToFly)
			{
				tmpx = eyePX;
				tmpy = eyePY;
				tmpz = eyePZ;
			}
			else
			{
				eyePX = tmpx;
				eyePY = tmpy;
				eyePZ = tmpz;
			}
			break;
		}
		//向上移动
		case 'h':
		{
			isFirstView = !isFirstView;
			if (isFirstView)
			{
				eyePZ -= 2.5;
			}
				
			else
			{
				eyePZ += 2.5;
			}
				
		}
		case 'z':
		{
			if (capableToFly)
				flyUp(eyePZ, viewDZ);
			break;
		}
		//向下移动
		case 'c':
		{
			flyDown(eyePZ, viewDZ);
			break;
		}
		//向前移动
		case 'w':
		{
			if (capableToFly)
				flyForward(eyePX, viewDX, eyePY, viewDY, eyePZ, viewDZ);
			else moveForward(eyePX, viewDX, eyePY, viewDY, eyePZ, viewDZ);
			break;			
		}
		//向后移动
		case 's':
		{
			if (capableToFly)
				flyBackward(eyePX, viewDX, eyePY, viewDY, eyePZ, viewDZ);
			else moveBackward(eyePX, viewDX, eyePY, viewDY, eyePZ, viewDZ);
			break;
		}
		//向左移动
		case 'a':
		{
			moveLeftward(eyePX, viewDX, eyePY, viewDY);
			break;
		}
		//向右移动
		case 'd':
		{
			moveRightward(eyePX, viewDX, eyePY, viewDY);
			break;
		}
		case 'j': {
			light_position[0] -= 5.0f;
			break;
		}
		case 'l': {
			light_position[0] += 5.0f;
			break;
		}
		case 'i': {
			light_position[1] += 5.0f;
			break;
		}
		case 'k': {
			light_position[1] -= 5.0f;
			break;
		}
		case 'u': {
			light_position[2] += 10.0f;
			break;
		}
		case 'o': {
			light_position[2] -= 10.0f;
			break;
		}
		case 'm': {
			lightExp -= 1.0f;
			break;
		}
		case 'n': {
			lightExp += 1.0f;
			break;
		}
		case 'b': {
			SaveScreenShot();
		}
		case 't': {
			colorState = (colorState + 1) % 3;
		}
		case ',':
		{
			mazeWall++;
			if (mazeWall == 9)
				mazeWall = 1;

			string selection = "";
			stringstream ss;
			ss << mazeWall;
			ss >> selection;
			string temp = "";
			temp = "texture/mazeWall" + selection + ".bmp";
			char *fileName = new char[21];	
			memcpy(fileName, temp.c_str(), 21);
			textureLoad::texload(5, fileName);
		}
		}
	}
	else if (isOver || isSuccess)
	{
		switch (key) 
		{
			case 'r':
			{
				restart = 1;
			}
				
		}
		
	}
}
void myMouse(int button, int state, int x, int y)
{
	if (gameStart && !isOver && !isSuccess)
	{
		//if(button==GLUT_DOWN) MouseDown = 1;

		if (button == GLUT_WHEEL_UP)
		{
			//if ((eyePY - 2.0f) > -24)
			eyePY -= 2.0f;
			viewDX = eyePX + dx;
			viewDY = eyePY + dy;
			viewDZ = eyePZ + dz;
			//myDisplay();
		}
		if (button == GLUT_WHEEL_DOWN)
		{
			//if ((eyePY + 2.0f) <24)
			eyePY += 2.0f;
			viewDX = eyePX + dx;
			viewDY = eyePY + dy;
			viewDZ = eyePZ + dz;
			//myDisplay();
		}
	}
}
void SetCamera(GLfloat x, GLfloat y)
{
	ax += x*0.05;
	ay -= y*0.08;
	float r = 1000;
	if (ay >= 90) ay = 90;
	if (ay <= -90) ay = -90;
	GLfloat dx, dy, dz;
	dy = -r*cos(ax*DEG_TO_RAD);
	dx = -r*sin(ax*DEG_TO_RAD);
	dz = -r*sin(ay);

	dz = r*sin(ay*DEG_TO_RAD);


	dx = dx * cos(ay*DEG_TO_RAD);
	dy = dy * cos(ay*DEG_TO_RAD);
	if(!capableToFly)
		dAngle = ax*DEG_TO_RAD * 180 / 3.1415926;
	viewDX = eyePX + dx;
	viewDY = eyePY + dy;
	viewDZ = eyePZ + dz;
	//myDisplay();
}
void MouseMove(int x, int y)		//无点击鼠标移动
{
	if (gameStart && !isOver && !isSuccess)
	{
		GetCursorPos(&mousePos);
		if ((mousePos.x != 1280 / 2) || (mousePos.y != 720 / 2))
		{
			SetCamera(float(mousePos.x) - float(1280 / 2), float(mousePos.y) - float(720 / 2));
			SetCursorPos(1280 / 2, 720 / 2);
		}
	}
}
void myMotion(int x, int y)
{
	if (gameStart && !isOver && !isSuccess)
	{
		if (MouseDown)
		{
			SetCamera(float(x - mx), float(y - my));
			mx = x;
			my = y;
		}
	}
}