#pragma once
#include<GL\glut.h>
#include <map>
#include <set>
#include "object.h"
#include "stdafx.h"
vector <Vertex> border;
extern int num[100];
bool judge[8][6] = { true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true
};
//每个幽灵每一圈的初始只有一次
bool initVer[8][6] = { true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true,
true,true,true,true,true,true
};

GLfloat ty[10] = { 0,0,0,0,0,0,0,0,0,0 };

int signal = 0;
extern Vertex ghostV[10];

map<string, Object> objmap;
set<string> objname;
string cd;
map<string, Material> matname;
void setMaterial(Material &mat)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat.emission);
	glMaterialf(GL_FRONT, GL_SHININESS, 100);
}

void obj(map<string, Object> &objmap, set<string> &objname, map<string, Material> &matname)
{
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
				if (!signal)
				{
					Vertex v;
					v.x = temp.vertexs[*iter - 1].x;
					v.y = temp.vertexs[*iter - 1].y;
					v.z = temp.vertexs[*iter - 1].z;
					v.x += 4.0;
					v.y += 5.0;
					v.z += 5.5;

					border.push_back(v);
					signal = 1;
				}


				//	cout << temp.vertexs[*iter - 1].x << " " << temp.vertexs[*iter - 1].y << " " << temp.vertexs[*iter - 1].z << endl;
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
}
void ghost1Move()
{
	if (num[0]--)
	{
		ty[0] += 0.02;
		ghostV[0].y -= 0.02*2.3;
	}
	else
	{
		if (judge[0][0])
		{
			ty[0] = 0;
			judge[0][0] = false;
		}
		num[0] = 0;
		if (num[1]--)
		{
			ty[0] += 0.02;
			ghostV[0].x -= 0.02*2.3;
		}
		else
		{
			if (judge[0][1])
			{
				ty[0] = 0;
				judge[0][1] = false;
			}
			num[1] = 0;
			if (num[2]--)
			{
				ty[0] += 0.02;
				ghostV[0].y += 0.02*2.3;
			}	
			else
			{
				if (judge[0][2])
				{
					ty[0] = 0;
					judge[0][2] = false;
				}
				num[2] = 0;
				if (num[3]--)
				{
					ty[0] += 0.02;
					ghostV[0].x += 0.02*2.3;
				}	
				else
				{
					num[3] = 0;
					ty[0] = 0;
				}
			}
		}
	}
}
void ghost2Move()
{
	if (num[4]--)
	{
		ty[1] += 0.02;
		ghostV[1].y -= 0.02*2.3;
	}

	else
	{

		if (judge[1][0])
		{
			ty[1] = 0;
			//ghostV[1].y = 2.3;
			judge[1][0] = false;
		}
		num[4] = 0;
		if (num[5]--)
		{
			ty[1] += 0.02;
			ghostV[1].y += 0.02*2.3;
		}
		else
		{
			num[5] = 0;
			ty[1] = 0;
			//ghostV[1].y = 8.5*2.3;
		}
	}
}
void ghost3Move()
{
	if (num[6]--)
	{
		ty[2] += 0.02;
		ghostV[2].y += 0.02*2.3;
	}
	else
	{
		if (judge[2][0])
		{
			ty[2] = 0;
			judge[2][0] = false;
		}
		num[6] = 0;
		if (num[7]--)
		{
			ty[2] += 0.02;
			ghostV[2].x -= 0.02*2.3;
		}
		else
		{
			if (judge[2][1])
			{
				ty[2] = 0;
				judge[2][1] = false;
			}
			num[7] = 0;
			if (num[8]--)
			{
				ty[2] += 0.02;
				ghostV[2].y -= 0.02*2.3;
			}
			else
			{
				if (judge[2][2])
				{
					ty[2] = 0;
					judge[2][2] = false;
				}
				num[8] = 0;
				if (num[9]--)
				{
					ty[2] += 0.02;
					ghostV[2].x += 0.02*2.3;
				}
				else
				{
					num[9] = 0;
					ty[2] = 0;
				}
			}
		}
	}
}
void ghost4Move()
{
	if (num[10]--)
	{
		ty[3] += 0.02;
		ghostV[3].x += 0.02*2.3;
	}
	else
	{
		if (judge[3][0])
		{
			ty[3] = 0;
			judge[3][0] = false;
		}
		num[10] = 0;
		if (num[11]--)
		{
			ty[3] += 0.02;
			ghostV[3].y -= 0.02*2.3;
		}
		else
		{
			if (judge[3][1])
			{
				ty[3] = 0;
				judge[3][1] = false;
			}
			num[11] = 0;
			if (num[12]--)
			{
				ty[3] += 0.02; 
				ghostV[3].y += 0.02*2.3;
			}	
			else
			{
				if (judge[3][2])
				{
					ty[3] = 0;
					judge[3][2] = false;
				}
				num[12] = 0;
				if (num[13]--)
				{
					ty[3] += 0.02; 
					ghostV[3].x -= 0.02*2.3;
				}
				else
				{
					num[13] = 0;
					ty[3] = 0;
				}
			}
		}
	}
}
void ghost5Move()
{
	if (num[14]--)
	{
		ty[4] += 0.04;
		ghostV[4].y -= 0.04*2.3;
	}

	else
	{

		if (judge[4][0])
		{
			ty[4] = 0;
			judge[4][0] = false;
		}
		num[14] = 0;
		if (num[15]--)
		{
			ty[4] += 0.04;
			ghostV[4].y += 0.04*2.3;
		}
		else
		{
			num[15] = 0;
			ty[4] = 0;
		}
	}
}
void ghost6Move()
{
	if (num[16]--)
	{
		ty[5] += 0.02;
		ghostV[5].x -= 0.02*2.3;
	}
	else
	{
		if (judge[5][0])
		{
			ty[5] = 0;
			judge[5][0] = false;
		}
		num[16] = 0;
		if (num[17]--)
		{
			ty[5] += 0.02;
			ghostV[5].y -= 0.02*2.3;
		}
		else
		{
			if (judge[5][1])
			{
				ty[5] = 0;
				judge[5][1] = false;
			}
			num[17] = 0;
			if (num[18]--)
			{
				ty[5] += 0.02;
				ghostV[5].y += 0.02*2.3;
			}
			else
			{
				if (judge[5][2])
				{
					ty[5] = 0;
					judge[5][2] = false;
				}
				num[18] = 0;
				if (num[19]--)
				{
					ty[5] += 0.02;
					ghostV[5].x += 0.02*2.3;
				}
				else
				{
					num[19] = 0;
					ty[5] = 0;
				}
			}
		}
	}
}
void ghost7Move()
{
	if (num[20]--)
	{
		ty[6] += 0.02;
		ghostV[6].x -= 0.02*2.3;
	}
	else
	{
		if (judge[6][0])
		{
			ty[6] = 0;
			judge[6][0] = false;
		}
		num[20] = 0;
		if (num[21]--)
		{
			ty[6] += 0.02;
			ghostV[6].y -= 0.02*2.3;
		}
		else
		{
			if (judge[6][1])
			{
				ty[6] = 0;
				judge[6][1] = false;
			}
			num[21] = 0;
			if (num[22]--)
			{
				ty[6] += 0.02;
				ghostV[6].y += 0.02*2.3;
			}
			else
			{
				if (judge[6][2])
				{
					ty[6] = 0;
					judge[6][2] = false;
				}
				num[22] = 0;
				if (num[23]--)
				{
					ty[6] += 0.02;
					ghostV[6].x += 0.02*2.3;
				}
				else
				{
					num[23] = 0;
					ty[6] = 0;
				}
			}
		}
	}
}
void ghostloop1(int n1, int n2, int n3, int n4)
{
	if (num[0])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼背
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(4, 0, -23);

		if (initVer[0][0])
		{
			ghostV[0].x = 4*2.3;
			ghostV[0].y = 23*2.3;
			initVer[0][0] = false;
		}
	}
	else if (num[1])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向右
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-15.5, 0, -4);
		if (initVer[0][1])
		{
			ghostV[0].x = 4 * 2.3;
			ghostV[0].y = 15.5 * 2.3;
			initVer[0][1] = false;
		}
	}
	else if (num[2])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-1, 0, 15.75);

		if (initVer[0][2])
		{
			ghostV[0].x =  2.3;
			ghostV[0].y = 15.5 * 2.3;
			initVer[0][2] = false;
		}
	}
	else if (num[3])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向左
		glRotatef(90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(23, 0, 1.25);
		if (initVer[0][3])
		{
			ghostV[0].x = 2.3;
			ghostV[0].y = 23 * 2.3;
			initVer[0][3] = false;
		}
	}
	else//如果走完一个循环 初始化路线信息
	{
		num[0] = n1;
		num[1] = n2;
		num[2] = n3;
		num[3] = n4;
		ty[0] = 0;
		judge[0][0] = true;
		judge[0][1] = true;
		judge[0][2] = true;
		initVer[0][0] = true;
		initVer[0][1] = true;
		initVer[0][2] = true;
		initVer[0][3] = true;
		ghost1Move();
	}
}
void ghostloop2(int n1, int n2)
{
	if (num[4])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);

		glTranslatef(1.5, 0, -8.5);
		if (initVer[1][0])
		{
			ghostV[1].x = 2.3;
			ghostV[1].y = 8.5*2.3;
			initVer[1][0] = false;
		}

	}
	else if (num[5])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);

		glTranslatef(-1, 0, 1);
		if (initVer[1][1])
		{
			ghostV[1].x = 2.3;
			ghostV[1].y = 2.3;
			initVer[1][1] = false;
		}
	}
	else
	{
		num[4] = n1;
		num[5] = n2;
		ty[1] = 0;
		judge[1][0] = true;
		initVer[1][0] = true;
		initVer[1][1] = true;
		ghost2Move();
	}

}
void ghostloop3(int n1, int n2, int n3, int n4)
{
	if (num[6])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-14, 0, 8.4);
		if (initVer[2][0])
		{
			ghostV[2].x = 14*2.3;
			ghostV[2].y = 8.5*2.3;
			initVer[2][0] = false;
		}
	}
	else if (num[7])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向右
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-16, 0, -14.1);
		if (initVer[2][1])
		{
			ghostV[2].x = 14*2.3;
			ghostV[2].y =16*2.3;
			initVer[2][1] = false;
		}
	}
	else if (num[8])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼背
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(9.5, 0, -16.1);
		if (initVer[2][2])
		{
			ghostV[2].x = 9.5*2.3;
			ghostV[2].y = 16*2.3;
			initVer[2][2] = false;
		}
	}
	else if (num[9])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向左
		glRotatef(90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(8.5, 0, 9.4);
		if (initVer[2][3])
		{
			ghostV[2].x = 9.5*2.3;
			ghostV[2].y = 8.5*2.3;
			initVer[2][3] = false;
		}
	}
	else
	{
		num[6] = n1;
		num[7] = n2;
		num[8] = n3;
		num[9] = n4;
		ty[2] = 0;
		judge[2][0] = true;
		judge[2][1] = true;
		judge[2][2] = true;
		initVer[2][0] = true;
		initVer[2][1] = true;
		initVer[2][2] = true;
		initVer[2][3] = true;
		ghost3Move();
	}
}
void ghostloop4(int n1, int n2, int n3, int n4)
{
	if (num[10])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向左
		glRotatef(90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(3, 0, 3.5);
		if (initVer[3][0])
		{
			ghostV[3].x = 3.5 * 2.3;
			ghostV[3].y = 3*2.3;
			initVer[3][0] = false;
		}
	}
	else if (num[11])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼背
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(11.75, 0, -3);
		if (initVer[3][1])
		{
			ghostV[3].x = 11.75 * 2.3;
			ghostV[3].y = 3*2.3;
			initVer[3][1] = false;
		}
	}
	else if (num[12])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-11.75, 0, 1);
		if (initVer[3][2])
		{
			ghostV[3].x = 11.75 * 2.3;
			ghostV[3].y = 2.3;
			initVer[3][2] = false;
		}
	}
	else if (num[13])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向右
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-3, 0, -11.75);
		if (initVer[3][3])
		{
			ghostV[3].x = 11.75 * 2.3;
			ghostV[3].y = 3*2.3;
			initVer[3][3] = false;
		}
	}
	else
	{
		num[10] = n1;
		num[11] = n2;
		num[12] = n3;
		num[13] = n4;
		ty[3] = 0;
		judge[3][0] = true;
		judge[3][1] = true;
		judge[3][2] = true;
		initVer[3][0] = true;
		initVer[3][1] = true;
		initVer[3][2] = true;
		initVer[3][3] = true;
		ghost4Move();
	}
}
void ghostloop5(int n1, int n2)
{
	if (num[14])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼背
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(17.25,0,-21.5);
		if (initVer[4][0])
		{
			ghostV[4].x = 17.25*2.3;
			ghostV[4].y = 21.5*2.3;
			initVer[4][0] = false;
		}

	}
	else if (num[15])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);

		glTranslatef(-17, 0, 3);
		if (initVer[4][1])
		{
			ghostV[4].x = 17*2.3;
			ghostV[4].y = 3*2.3;
			initVer[4][1] = false;
		}
	}
	else
	{
		num[14] = n1;
		num[15] = n2;
		ty[4] = 0;
		judge[4][0] = true;
		initVer[4][0] = true;
		initVer[4][1] = true;
		ghost5Move();
	}
}
void ghostloop6(int n1, int n2, int n3, int n4)
{
	if (num[16])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向右
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);

		glTranslatef(-5.5, 0, -24.5);
		if (initVer[5][0])
		{
			ghostV[5].x = 24.5 * 2.3;
			ghostV[5].y = 5.5*2.3;
			initVer[5][0] = false;
		}
	}
	else if (num[17])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼背
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(19.5, 0, -5.5);
		if (initVer[5][1])
		{
			ghostV[5].x = 19.5 * 2.3;
			ghostV[5].y = 5.5 * 2.3;
			initVer[5][1] = false;
		}
	}
	else if (num[18])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);

		glTranslatef(-19.25, 0, 3);
		if (initVer[5][2])
		{
			ghostV[5].x = 19.25*2.3;
			ghostV[5].y = 3* 2.3;
			initVer[5][2] = false;
		}
	}
	else if (num[19])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向左
		glRotatef(90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(6, 0,19.5);
		if (initVer[5][3])
		{
			ghostV[5].x = 19.5*2.3;
			ghostV[5].y = 6*2.3;
			initVer[5][3] = false;
		}
	}
	else
	{
		num[16] = n1;
		num[17] = n2;
		num[18] = n3;
		num[19] = n4;
		ty[5] = 0;
		judge[5][0] = true;
		judge[5][1] = true;
		judge[5][2] = true;
		initVer[5][0] = true;
		initVer[5][1] = true;
		initVer[5][2] = true;
		initVer[5][3] = true;
		ghost6Move();
	}
}
void ghostloop7(int n1, int n2, int n3, int n4)
{
	if (num[20])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向右
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-16, 0, -24.5);
		if (initVer[6][0])
		{
			ghostV[6].x = 24.5 * 2.3;
			ghostV[6].y = 16*2.3;
			initVer[6][0] = false;
		}
	}
	else if (num[21])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼背
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(22, 0, -16);
		if (initVer[6][1])
		{
			ghostV[6].x = 22 * 2.3;
			ghostV[6].y = 16 * 2.3;
			initVer[6][1] = false;
		}
	}
	else if (num[22])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(-22, 0, 8);
		if (initVer[6][2])
		{
			ghostV[6].x = 22*2.3;
			ghostV[6].y = 8 * 2.3;
			initVer[6][2] = false;
		}
	}
	else if (num[23])
	{
		glScalef(2.3, 2.3, 2.3);
		glRotatef(90, 1, 0, 0);//眼向左
		glRotatef(90, 0, 1, 0);
		glTranslatef(0.5, 0, -11.4);
		glTranslatef(16, 0, 22);
		if (initVer[6][3])
		{
			ghostV[6].x = 22*2.3;
			ghostV[6].y = 16*2.3;
			initVer[6][3] = false;
		}
	}
	else
	{
		num[20] = n1;
		num[21] = n2;
		num[22] = n3;
		num[23] = n4;
		ty[6] = 0;
		judge[6][0] = true;
		judge[6][1] = true;
		judge[6][2] = true;
		initVer[6][0] = true;
		initVer[6][1] = true;
		initVer[6][2] = true;
		initVer[6][3] = true;
		ghost7Move();
	}
}
void drawGhost()
{
	//第一只幽灵
	glPushMatrix();
	ghostloop1(375, 150, 375, 150);
	glTranslatef(0, 0, ty[0]);
	obj(objmap, objname, matname);
	glPopMatrix();

	//第二只幽灵
	glPushMatrix();
	ghostloop2(375, 375);
	glTranslatef(0, 0, ty[1]);
	obj(objmap, objname, matname);
	glPopMatrix();

	//第三只幽灵
	glPushMatrix();
	ghostloop3(375, 250, 375, 250);
	glTranslatef(0, 0, ty[2]);
	obj(objmap, objname, matname);
	glPopMatrix();

	//第四只幽灵
	glPushMatrix();
	ghostloop4(425, 100, 100, 425);
	glTranslatef(0, 0, ty[3]);
	obj(objmap, objname, matname);
	glPopMatrix();

	//第五只幽灵 速度比前五只快一倍
	glPushMatrix();
	ghostloop5(462, 462);
	glTranslatef(0, 0, ty[4]);
	obj(objmap, objname, matname);
	glPopMatrix();

	//第六只
	glPushMatrix();
	ghostloop6(250, 125, 125, 250);
	glTranslatef(0, 0, ty[5]);
	obj(objmap, objname, matname);
	glPopMatrix();

	//第七只
	glPushMatrix();
	ghostloop7(125, 400, 400, 125);
	glTranslatef(0, 0, ty[6]);
	obj(objmap, objname, matname);
	glPopMatrix();
}