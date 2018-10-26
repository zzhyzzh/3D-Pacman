#pragma once
// glutEx1.cpp : 定义控制台应用程序的入口点。  
//  
#include <stdlib.h>  
#include <stdio.h>  
#include "gl\glut.h"
#include <windows.h>
#include"texture.h"
#include "object.h"
#define MAX_CHAR       128
#define SPACELENGTH 30
#define Height 16  
#define Width 16 

extern GLuint textureCollection[8];
extern int matrix[70][60];
extern int point;
extern double dAngle;
extern GLfloat x;
extern GLfloat y;
class sky
{
public:
	static void init()
	{
		glGenTextures(7, textureCollection); // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组  
		textureLoad::texload(0, "texture/floor.bmp");
		textureLoad::texload(1, "texture/wall.bmp");
		textureLoad::texload(2, "texture/floor.bmp");
		textureLoad::texload(3, "texture/floor.bmp");
	}

	static void drawCube(int xRepeat, int yRepeat)
	{
		int i, j;
		const GLfloat x1 = -0.5, x2 = 0.5;
		const GLfloat y1 = -0.5, y2 = 0.5;
		const GLfloat z1 = -0.5, z2 = 0.5;

		//指定六个面的四个顶点，每个顶点用3个坐标值表示    
		GLfloat point[6][4][3] = {
			{ { x1,y1,z1 },{ x2,y1,z1 },{ x2,y2,z1 },{ x1,y2,z1 } },
			{ { x1,y1,z1 },{ x2,y1,z1 },{ x2,y1,z2 },{ x1,y1,z2 } },
			{ { x2,y1,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x2,y1,z2 } },
			{ { x1,y1,z1 },{ x1,y2,z1 },{ x1,y2,z2 },{ x1,y1,z2 } },
			{ { x1,y2,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x1,y2,z2 } },
			{ { x1,y1,z2 },{ x2,y1,z2 },{ x2,y2,z2 },{ x1,y2,z2 } }
		};
		int dir[4][2] = { { xRepeat,yRepeat },{ xRepeat,0 },{ 0,0 },{ 0,yRepeat } };
		//设置正方形绘制模式    

		glBegin(GL_QUADS);
		for (i = 0; i < 6; i++) {
			for (j = 0; j < 4; j++) {
				glTexCoord2iv(dir[j]);
				glVertex3fv(point[i][j]);
			}
		}
		glEnd();
	}

	static void drawSky() // This function draws a triangle with RGB colors  
	{
		//上方
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureCollection[1]);  //选择纹理  

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//设置纹理不受光照影响  
		glPushMatrix();
		glTranslatef(SPACELENGTH, SPACELENGTH, SPACELENGTH / 2);
		glScalef(2 * SPACELENGTH + 2, 2 * SPACELENGTH + 2, 2);
		drawCube(16, 16);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D); //关闭纹理

								  //下方
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureCollection[2]);  //选择纹理  

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//设置纹理不受光照影响  
		glPushMatrix();
		glTranslatef(SPACELENGTH, SPACELENGTH, -2.5);
		glScalef(2 * SPACELENGTH + 2, 2 * SPACELENGTH + 2, 0.5);
		drawCube(60, 60);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D); //关闭纹理

								  //前方
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureCollection[1]);  //选择纹理  

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//设置纹理不受光照影响  
		glPushMatrix();
		glTranslatef(SPACELENGTH, -2, 0);
		glScalef(2 * SPACELENGTH + 2, 2, SPACELENGTH);
		drawCube(8, 16);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D); //关闭纹理		

								  //左方
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureCollection[1]);  //选择纹理  

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//设置纹理不受光照影响  
		glPushMatrix();
		glTranslatef(2 * SPACELENGTH + 2, SPACELENGTH, 0);
		glScalef(2, 2 * SPACELENGTH + 2, SPACELENGTH);
		drawCube(8, 16);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D); //关闭纹理

								  //右方
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureCollection[1]);  //选择纹理  

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//设置纹理不受光照影响  
		glPushMatrix();
		glTranslatef(-2, SPACELENGTH, 0);
		glScalef(2, 2 * SPACELENGTH + 2, SPACELENGTH);
		drawCube(8, 16);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D); //关闭纹理

								  //后方
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureCollection[1]);  //选择纹理  

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//设置纹理不受光照影响  
		glPushMatrix();
		glTranslatef(SPACELENGTH, 2 * SPACELENGTH + 2, 0);
		glScalef(2 * SPACELENGTH + 2, 2, SPACELENGTH);
		drawCube(8, 16);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D); //关闭纹理
	}
};

class maze 
{
public:
	static void init()
	{
		glGenTextures(1, textureCollection); // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
		textureLoad::texload(5, "texture/mazeWall1.bmp");

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //设置像素存储模式控制所读取的图像数据的行对齐方式.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	static void drawMaze()
	{
		int i, j, m, n;
		GLfloat width = 0.5f;
		GLfloat cube[6][4][3] = {
			{ { -width,-width,-width },{ width,-width,-width },{ width,width,-width },{ -width,width,-width } },
			{ { -width,-width,-width },{ width,-width,-width },{ width,-width,width },{ -width,-width,width } },
			{ { width,-width,-width },{ width,width,-width },{ width,width,width },{ width,-width,width } },
			{ { -width,-width,-width },{ -width,width,-width },{ -width,width,width },{ -width,-width,width } },
			{ { -width,width,-width },{ width,width,-width },{ width,width,width },{ -width,width,width } },
			{ { -width,-width,width },{ width,-width,width },{ width,width,width },{ -width,width,width } }
		};
		int text[4][2] = { { 4,1 },{ 4,0 },{ 0,0 },{ 0,1 } };
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureCollection[5]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//设置纹理不受光照影响  
		for (m = 0; m < 61; m++)
		{
			for (n = 0; n < 57; n++)
			{
				if (matrix[m][n] == 1)
				{
					glPushMatrix();
					glTranslatef(m, n, 0);
					glScalef(1.0, 1.0, 4.0);
					glBegin(GL_QUADS);
					for (i = 0; i < 6; i++)
					{
						for (j = 0; j < 4; j++)
						{
							glTexCoord2iv(text[j]);
							glVertex3fv(cube[i][j]);
						}
					}
					glEnd();
					glPopMatrix();
				}
			}
		}
		glDisable(GL_TEXTURE_2D); //关闭纹理 
	}
};

class coin
{
public:

	//画豆子
	static void DrawBean(GLfloat radius)
	{
		int m, n;
		GLfloat mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.0f };

		GLfloat diffuse0[] = { 0.85f, 0.65f, 0.2f, 1.0f };//金黄
		GLfloat diffuse1[] = { 1.0f, 1.0f, 1.0f };//白
		GLfloat diffuse2[] = { 0.0f, 1.0f, 0.0f };//黄
		GLfloat diffuse3[] = { 1.0f, 1.0f, 0.0f };//橙
		GLfloat diffuse4[] = { 0.0f, 1.0f, 1.0f };//绿
		GLfloat diffuse5[] = { 0.0f, 0.0f, 1.0f };//蓝



												  //	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);//多边形正面漫反射为红
		glMaterialfv(GL_FRONT, GL_SPECULAR, diffuse1);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
		for (m = 0; m < 61; m++)
		{
			for (n = 0; n < 57; n++)
			{
				if (matrix[m][n] == 2)
				{
					glPushMatrix();
					glTranslatef(m, n, -1.5);
					glutSolidSphere(0.4, 16, 16);
					glPopMatrix();
				}
			}
		}
	}
};

class score
{
public:


	static void drawString(const char* str) {
		static int isFirstCall = 1;
		static GLuint lists;

		if (isFirstCall) { // 如果是第一次调用，执行初始化
						   // 为每一个ASCII字符产生一个显示列表
			isFirstCall = 0;

			// 申请MAX_CHAR个连续的显示列表编号
			lists = glGenLists(MAX_CHAR);

			// 把每个字符的绘制命令都装到对应的显示列表中
			wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
		}
		// 调用每个字符对应的显示列表，绘制每个字符
		for (; *str != '\0'; ++str)
			glCallList(lists + *str);
	}

	static void selectFont(int size, int charset, const char* face) {
		HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
			charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
		HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
		DeleteObject(hOldFont);
	}

	static void display(void) {
		char *c;
		char buffer[256];
		//selectFont(108, ANSI_CHARSET, "Comic Sans MS");

		//glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0f, 1.0f, 1.0f);
		sprintf(buffer, "Score: %d", point);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
		glPushMatrix();               // 保存原矩阵
		glLoadIdentity();             // 装入单位矩阵
		glOrtho(0, 1280, 0, 720, -1, 1);    // 位置正投影
		glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
		glPushMatrix();               // 保存原矩阵
		glLoadIdentity();             // 装入单位矩阵
		glRasterPos2f(640, 660);
		for (c = buffer; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
		glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
		glPopMatrix();                // 重置为原保存矩阵
		glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
		glPopMatrix();                // 重置为原保存矩阵
		glEnable(GL_DEPTH_TEST);

	}

};

class pacMan
{
public:
	map<string, Object> objmap;
	set<string> objname;
	string cd;
	map<string, Material> matname;
	void init()
	{
		ReadObj(cd, ".\\tank\\chidouren.obj", objmap, objname, matname);
		//glutFullScreen();
		glClearColor(0.93, 0.94, 0.98, 1.0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		//setLight();
	}
	void draw()
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		//glTranslatef(15, 15, 0);
		glRotatef(180, 0.0f, 1.0f, 0.0f);
		glRotatef(-90 + dAngle, 0.0f, 0.0f, 1.0f);

		glScalef(0.3,0.3,0.3);
		for (set<string>::iterator it = objname.begin(); it != objname.end(); ++it)
		{
			Object temp = objmap[*it];
			setMaterial(matname[temp.material]);
			glBindTexture(GL_TEXTURE_2D, matname[temp.material].map);
			if (temp.row == 3)
				glBegin(GL_TRIANGLES);
			else
				glBegin(GL_QUADS);
			vector<int>::iterator iter = temp.faces.begin();
			if (temp.col == 1)
			{
				while (iter != temp.faces.end())
				{
					glVertex3f(temp.vertexs[*iter - 1].x, temp.vertexs[*iter - 1].y, temp.vertexs[*iter - 1].z);
					++iter;
				}
			}
			else if (temp.col == 2)
			{
				while (iter != temp.faces.end())
				{
					glTexCoord2f(temp.texcoords[*(iter + 1) - 1].first, temp.texcoords[*(iter + 1) - 1].second);
					glVertex3f(temp.vertexs[*iter - 1].x, temp.vertexs[*iter - 1].y, temp.vertexs[*iter - 1].z);
					iter += 2;
				}
			}
			else if (temp.col == 3 && !temp.texcoords.empty())
			{
				while (iter != temp.faces.end())
				{
					glNormal3f(temp.normals[*(iter + 2) - 1].x, temp.normals[*(iter + 2) - 1].y, temp.normals[*(iter + 2) - 1].z);
					glTexCoord2f(temp.texcoords[*(iter + 1) - 1].first, temp.texcoords[*(iter + 1) - 1].second);
					glVertex3f(temp.vertexs[*iter - 1].x, temp.vertexs[*iter - 1].y, temp.vertexs[*iter - 1].z);
					iter += 3;
				}
			}
			else
			{
				while (iter != temp.faces.end())
				{
					glNormal3f(temp.normals[*(iter + 2) - 1].x, temp.normals[*(iter + 2) - 1].y, temp.normals[*(iter + 2) - 1].z);
					glVertex3f(temp.vertexs[*iter - 1].x, temp.vertexs[*iter - 1].y, temp.vertexs[*iter - 1].z);
					iter += 3;
				}
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			glEnd();
		}
		glPopMatrix();
	}

	void setLight()
	{
		static const GLfloat light_position[] = { 50.0f,50.0f,50.0f,0.0f };
		static const GLfloat light_ambient[] = { 0.0f,0.0f,0.0f,0.0f };
		static const GLfloat light_diffuse[] = { 1.0f,0.9f,0.9f,0.0f };
		static const GLfloat light_specular[] = { 1.0f,1.0f,1.0f,0.0f };
		static const GLfloat light_direction[] = { -1.0f,-1.0f,-1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 120.0f);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	void setMaterial(Material &mat)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat.emission);
		glMaterialf(GL_FRONT, GL_SHININESS, 100);
	}
};

class over
{
public:
	static void drawScene()
	{
		char *c;
		char buffer[256];
		//selectFont(108, ANSI_CHARSET, "Comic Sans MS");
		glColor3f(1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0f, 1.0f, 1.0f);
		
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
		glPushMatrix();               // 保存原矩阵
		glLoadIdentity();             // 装入单位矩阵
		glOrtho(0, 1280, 0, 720, -1, 1);    // 位置正投影
		glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
		glPushMatrix();               // 保存原矩阵
		glLoadIdentity();             // 装入单位矩阵
		glRasterPos2f(630, 460);
		sprintf(buffer, "Score: %d", point);
		for (c = buffer; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
		glRasterPos2f(630, 260);
		sprintf(buffer, "Game Over");
		for (c = buffer; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
		glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
		glPopMatrix();                // 重置为原保存矩阵
		glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
		glPopMatrix();                // 重置为原保存矩阵
		glEnable(GL_DEPTH_TEST);
	}
};

class success
{
public:
	static void drawScene()
	{
		char *c;
		char buffer[256];
		//selectFont(108, ANSI_CHARSET, "Comic Sans MS");
		glColor3f(1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0f, 1.0f, 1.0f);

		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
		glPushMatrix();               // 保存原矩阵
		glLoadIdentity();             // 装入单位矩阵
		glOrtho(0, 1280, 0, 720, -1, 1);    // 位置正投影
		glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
		glPushMatrix();               // 保存原矩阵
		glLoadIdentity();             // 装入单位矩阵
		glRasterPos2f(630, 460);
		sprintf(buffer, "Score: %d", point);
		for (c = buffer; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
		glRasterPos2f(630, 260);
		sprintf(buffer, "Success");
		for (c = buffer; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
		glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
		glPopMatrix();                // 重置为原保存矩阵
		glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
		glPopMatrix();                // 重置为原保存矩阵
		glEnable(GL_DEPTH_TEST);
	}
};