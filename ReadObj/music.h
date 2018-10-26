#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include "fmod.h"			// 音频库的头文件
#pragma comment(lib, "fmodvc.lib")	// 把音频库加入到链接器中

FSOUND_STREAM *mp3back;		// 背景音乐 *.mp3格式
FSOUND_STREAM *beanEaten;
FSOUND_STREAM *fail;
FSOUND_STREAM *victory;

GLvoid InitFMOD(void)
{
	// 载入音频文件
	if (FSOUND_Init(44100, 32, 0))		// 把声音初始化为44khz
	{
		// 载入文件bgmusic.mp3
		mp3back = FSOUND_Stream_OpenFile("music/bgm.mp3", FSOUND_LOOP_NORMAL, 0);
		beanEaten = FSOUND_Stream_OpenFile("music/buble.mp3", FSOUND_LOOP_OFF, 0);
		fail = FSOUND_Stream_OpenFile("music/fail.mp3", FSOUND_LOOP_OFF, 0);
		victory = FSOUND_Stream_OpenFile("music/victory.mp3", FSOUND_LOOP_OFF, 0);
	}
}

GLvoid FreeFMOD(void)
{
	// 释放音频文件
	if (mp3back != NULL)
	{
		FSOUND_Stream_Close(mp3back);	// 释放文件bgmusic.mp3
	}
}

