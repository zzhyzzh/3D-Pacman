#pragma once
#include <GL\glut.h>
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "music.h"

//移动参数
GLfloat fMove = 0.2;
GLfloat flyMove = 0.5;
float v = 0.5;
Vertex ver;
GLfloat cos_alpha;
GLfloat sin_theta;
GLfloat cos_theta;
GLfloat sin_phi;

extern int matrix[70][60];
extern int point;
extern GLfloat x;
extern GLfloat y;
extern bool isFirstView;
extern Vertex ghostV[10];
using namespace std;

bool collisionDetection(Vertex v) //碰撞检测
{
	int i, j;
	int vx, vy, vz;
	
	for (i = 0; i < 61; i++)
	{
		for (j = 0; j < 57; j++)
		{
			vx = i;
			vy = j;
			if (matrix[vx][vy] == 2 && fabs(vx - v.x) <= 1.4 && fabs(vy - v.y) <= 1.4)
			{
				matrix[vx][vy] = 0;
				point++;
				FSOUND_Stream_Play(FSOUND_FREE, beanEaten);
			}

			if (matrix[vx][vy] == 1 && fabs(vx - v.x) <= 1.4 && fabs(vy - v.y) <= 1.4)
			{
				return true;
			}
		}



	}
	
	return false;
}
bool overDetection(Vertex v)
{
	int i, j;
	int vx, vy, vz;
	for (i = 0; i < 7; i++)
	{
		if (fabs(ghostV[i].x - v.x) <= 1.8 && fabs(ghostV[i].y - v.y) <= 1.8)
		{
			FSOUND_Stream_Play(FSOUND_FREE, fail);
			return true;			
		}
	}
	return false;
}
bool flyCollision(Vertex v)
{
	int i, j;
	int vx, vy, vz;

	for (i = 0; i < 61; i++)
	{
		for (j = 0; j < 57; j++)
		{
			vx = i;
			vy = j;
			vz = 0;
			if (matrix[vx][vy] == 1 && fabs(vx - v.x) <= 1.6 && fabs(vy - v.y) <= 1.6 && fabs(vz - v.z)<=3.5 || v.z <0 || v.z >12 || v.x <0 || v.y <0 || v.x > 60 || v.y >60)
			{
				return true;
			}
		}



	}

	return false;
}
void flyUp(float &eyePZ, float &viewDZ)
{
	eyePZ += flyMove;
	viewDZ += flyMove;
}
void flyDown(float &eyePZ, float &viewDZ)
{
	eyePZ -= flyMove;
	viewDZ -= flyMove;
}
void flyForward(float &eyePX, float &viewDX, float &eyePY, float &viewDY, float &eyePZ, float &viewDZ)
{
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
	//ver.x = eyePX + fMove*cos_alpha*cos_theta;
	//ver.y = eyePY + fMove*cos_alpha*sin_theta;
	//ver.z = eyePZ + fMove*cos_alpha*sin_phi;

	///*  照相机坐标转世界坐标*/


	//if (!collisionDetection(ver))
	//{
	//	cout << "No collide" << endl;
	//	cout << ver.x << endl;
	//	cout << ver.y << endl;
	//	cout << ver.z << endl;
	/*eyePX += fMove*cos_alpha*cos_theta;
	viewDX += fMove*cos_alpha*cos_theta;
	eyePY += fMove*cos_alpha*sin_theta;
	viewDY += fMove*cos_alpha*sin_theta;
	eyePZ += fMove*cos_alpha*sin_phi;
	viewDZ += fMove*cos_alpha*sin_phi;*/

	Vertex ver;
	ver.x = eyePX + flyMove*cos_alpha*cos_theta;
	ver.y = eyePY + flyMove*cos_alpha*sin_theta;
	ver.z = eyePZ + flyMove*cos_alpha*sin_phi;
	if (!flyCollision(ver))
	{
		eyePX += flyMove*cos_alpha*cos_theta;
		viewDX += flyMove*cos_alpha*cos_theta;
		eyePY += flyMove*cos_alpha*sin_theta;
		viewDY += flyMove*cos_alpha*sin_theta;
		eyePZ += flyMove*cos_alpha*sin_phi;
		viewDZ += flyMove*cos_alpha*sin_phi;
											/*
											eyePZ += fMove*cos_alpha*sin_phi;
											viewDZ += fMove*cos_alpha*sin_phi;*/
	}
	//}
	//else
	//{
	//	cout << "collide" << endl;
	//}
}
void flyBackward(float &eyePX, float &viewDX, float &eyePY, float &viewDY, float &eyePZ, float &viewDZ)
{
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


	Vertex ver;
	ver.x = eyePX - flyMove*cos_alpha*cos_theta;
	ver.y = eyePY - flyMove*cos_alpha*sin_theta;
	ver.z = eyePZ - flyMove*cos_alpha*sin_phi;
	if (!flyCollision(ver))
	{
		eyePX -= flyMove*cos_alpha*cos_theta;
		viewDX -= flyMove*cos_alpha*cos_theta;
		eyePY -= flyMove*cos_alpha*sin_theta;
		viewDY -= flyMove*cos_alpha*sin_theta;
		eyePZ -= flyMove*cos_alpha*sin_phi;
		viewDZ -= flyMove*cos_alpha*sin_phi;
		/*
		eyePZ += fMove*cos_alpha*sin_phi;
		viewDZ += fMove*cos_alpha*sin_phi;*/
	}
}
void moveForward(float &eyePX, float &viewDX, float &eyePY, float &viewDY, float &eyePZ, float &viewDZ)
{
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
	if (isFirstView)
	{
		ver.x = eyePX + fMove*cos_alpha*cos_theta;
		ver.y = eyePY + fMove*cos_alpha*sin_theta;
		//ver.z = eyePZ + fMove*cos_alpha*sin_phi;
	}
	else
	{
		ver.x = x + fMove*cos_alpha*cos_theta;
		ver.y = y + fMove*cos_alpha*sin_theta;
	}


	/*  照相机坐标转世界坐标*/


	if (!collisionDetection(ver))
	{
		eyePX += fMove*cos_alpha*cos_theta;
		viewDX += fMove*cos_alpha*cos_theta;
		eyePY += fMove*cos_alpha*sin_theta;
		viewDY += fMove*cos_alpha*sin_theta;/*
											eyePZ += fMove*cos_alpha*sin_phi;
											viewDZ += fMove*cos_alpha*sin_phi;*/
	}

}
void moveBackward(float &eyePX, float &viewDX, float &eyePY, float &viewDY, float &eyePZ, float &viewDZ)
{
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

	/*eyePZ -= fMove*cos_alpha*sin_phi;
	viewDZ -= fMove*cos_alpha*sin_phi;*/

	if (isFirstView)
	{
		ver.x = eyePX - fMove*cos_alpha*cos_theta;
		ver.y = eyePY - fMove*cos_alpha*sin_theta;
		//ver.z = eyePZ + fMove*cos_alpha*sin_phi;
	}
	else
	{
		ver.x = x - fMove*cos_alpha*cos_theta;
		ver.y = y - fMove*cos_alpha*sin_theta;
	}


	/*  照相机坐标转世界坐标*/


	if (!collisionDetection(ver))
	{
		eyePX -= fMove*cos_alpha*cos_theta;
		viewDX -= fMove*cos_alpha*cos_theta;
		eyePY -= fMove*cos_alpha*sin_theta;
		viewDY -= fMove*cos_alpha*sin_theta;/*
											eyePZ += fMove*cos_alpha*sin_phi;
											viewDZ += fMove*cos_alpha*sin_phi;*/
	}
}
void moveLeftward(float &eyePX, float &viewDX, float &eyePY, float &viewDY)
{
	if ((viewDX - eyePX == 0) && (viewDY - eyePY == 0))
		sin_theta = 0;
	else
		sin_theta = (viewDY - eyePY) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY), v);
	if ((viewDX - eyePX == 0) && (viewDY - eyePY == 0))
		cos_theta = 0;
	else
		cos_theta = (viewDX - eyePX) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY), v);
	/*eyePX -= fMove*sin_theta;
	viewDX -= fMove*sin_theta;
	eyePY += fMove*cos_theta;
	viewDY += fMove*cos_theta;*/

	if (isFirstView)
	{
		ver.x = eyePX - fMove*sin_theta;
		ver.y = eyePY + fMove*cos_theta;
		//ver.z = eyePZ + fMove*cos_alpha*sin_phi;
	}
	else
	{
		ver.x = x - fMove*sin_theta;
		ver.y = y + fMove*cos_theta;
	}


	/*  照相机坐标转世界坐标*/


	if (!collisionDetection(ver))
	{
		eyePX -= fMove*sin_theta;
		viewDX -= fMove*sin_theta;
		eyePY += fMove*cos_theta;
		viewDY += fMove*cos_theta;
											/*eyePZ += fMove*cos_alpha*sin_phi;
											viewDZ += fMove*cos_alpha*sin_phi;*/
	}

}
void moveRightward(float &eyePX, float &viewDX, float &eyePY, float &viewDY)
{
	if ((viewDX - eyePX == 0) && (viewDY - eyePY == 0))
		sin_theta = 0;
	else
		sin_theta = (viewDY - eyePY) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY), v);
	if ((viewDX - eyePX == 0) && (viewDY - eyePY == 0))
		cos_theta = 0;
	else
		cos_theta = (viewDX - eyePX) / pow((viewDX - eyePX)*(viewDX - eyePX) + (viewDY - eyePY)*(viewDY - eyePY), v);
	//eyePX += fMove*sin_theta;
	//viewDX += fMove*sin_theta;
	//eyePY -= fMove*cos_theta;
	//viewDY -= fMove*cos_theta;

	if (isFirstView)
	{
		ver.x = eyePX + fMove*sin_theta;
		ver.y = eyePY - fMove*cos_theta;
		//ver.z = eyePZ + fMove*cos_alpha*sin_phi;
	}
	else
	{
		ver.x = x + fMove*sin_theta;
		ver.y = y - fMove*cos_theta;
	}


	/*  照相机坐标转世界坐标*/


	if (!collisionDetection(ver))
	{
		eyePX += fMove*sin_theta;
		viewDX += fMove*sin_theta;
		eyePY -= fMove*cos_theta;
		viewDY -= fMove*cos_theta;
											/*eyePZ += fMove*cos_alpha*sin_phi;
											viewDZ += fMove*cos_alpha*sin_phi;*/
	}
}