#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include "fmod.h"			// ��Ƶ���ͷ�ļ�
#pragma comment(lib, "fmodvc.lib")	// ����Ƶ����뵽��������

FSOUND_STREAM *mp3back;		// �������� *.mp3��ʽ
FSOUND_STREAM *beanEaten;
FSOUND_STREAM *fail;
FSOUND_STREAM *victory;

GLvoid InitFMOD(void)
{
	// ������Ƶ�ļ�
	if (FSOUND_Init(44100, 32, 0))		// ��������ʼ��Ϊ44khz
	{
		// �����ļ�bgmusic.mp3
		mp3back = FSOUND_Stream_OpenFile("music/bgm.mp3", FSOUND_LOOP_NORMAL, 0);
		beanEaten = FSOUND_Stream_OpenFile("music/buble.mp3", FSOUND_LOOP_OFF, 0);
		fail = FSOUND_Stream_OpenFile("music/fail.mp3", FSOUND_LOOP_OFF, 0);
		victory = FSOUND_Stream_OpenFile("music/victory.mp3", FSOUND_LOOP_OFF, 0);
	}
}

GLvoid FreeFMOD(void)
{
	// �ͷ���Ƶ�ļ�
	if (mp3back != NULL)
	{
		FSOUND_Stream_Close(mp3back);	// �ͷ��ļ�bgmusic.mp3
	}
}

