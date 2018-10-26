#pragma once
#include<iostream>
#include<stdio.h>
#include<math.h>
#include"gl\glut.h"
#include "stdafx.h"

using namespace std;

//��������
GLfloat angle = 0;
GLfloat groundAngle = 0;
GLfloat fRotate = 0.005f;



//������תЧ��
void openning(float &eyePX, float &eyePY)
{
	GLfloat radius = pow((eyePX - 30)*(eyePX - 30) + (eyePY - 30)*(eyePY - 30), 0.5);

	eyePX = 30 + radius * sin(angle);
	eyePY = 30 + radius * cos(angle);

	angle += fRotate;
}

//��������Ч��
void entering(float &eyePX, float &eyePY, float &eyePZ, bool &gameStart)
{
	if (eyePZ > 0.0f)
	{
		GLfloat radius = pow((eyePX - 30)*(eyePX - 30) + (eyePY - 30)*(eyePY - 30), 0.5) - 0.08f;

		eyePX = 30 + radius * sin(angle);
		eyePY = 30 + radius * cos(angle);

		angle += 4 * fRotate;

		eyePZ -= 0.5f;
	}
	else
	{
		if (eyePX <= 30.0f && eyePX >= 26.0f && eyePY > 0)
		{
			if (eyePY > 53.0f)
			{
				eyePY -= 0.5f;
			}
			else
			{
				gameStart = true;
			}
		}
		else
		{
			GLfloat radius = pow((eyePX - 30)*(eyePX - 30) + (eyePY - 30)*(eyePY - 30), 0.5) - 0.04f;

			eyePX = 30 + radius * sin(angle);
			eyePY = 30 + radius * cos(angle);
			
			angle += 4 * fRotate;
		}
	}
}
