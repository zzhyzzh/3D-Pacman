#pragma once
#include <windows.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include <GL/glut.h>
#include<time.h>

using namespace std;

bool WriteBitmapFile(char * filename, int width, int height, unsigned char * bitmapData)
{
	//���BITMAPFILEHEADER
	BITMAPFILEHEADER bitmapFileHeader;
	memset(&bitmapFileHeader, 0, sizeof(BITMAPFILEHEADER));
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
	bitmapFileHeader.bfType = 0x4d42;	//BM
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//���BITMAPINFOHEADER
	BITMAPINFOHEADER bitmapInfoHeader;
	memset(&bitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = width;
	bitmapInfoHeader.biHeight = height;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = width * abs(height) * 3;

	//////////////////////////////////////////////////////////////////////////
	FILE * filePtr;			//����Ҫ�����bitmap�ļ���
	unsigned char tempRGB;	//��ʱɫ��
	int imageIdx;

	//����R��B������λ��,bitmap���ļ����õ���BGR,�ڴ����RGB
	for (imageIdx = 0; imageIdx < bitmapInfoHeader.biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapData[imageIdx];
		bitmapData[imageIdx] = bitmapData[imageIdx + 2];
		bitmapData[imageIdx + 2] = tempRGB;
	}

	filePtr = fopen(filename, "wb");
	if (NULL == filePtr)
	{
		return FALSE;
	}

	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	fwrite(bitmapData, bitmapInfoHeader.biSizeImage, 1, filePtr);

	fclose(filePtr);
	return TRUE;
}

void SaveScreenShot()
{
	int clnWidth, clnHeight;	//client width and height
	static void * screenData;
	RECT rc;
	int len = 1280 * 720 * 3;
	screenData = malloc(len);
	memset(screenData, 0, len);
	glReadPixels(0, 0, 1280, 720, GL_RGB, GL_UNSIGNED_BYTE, screenData);

	//�����ļ����ַ�������ʱ������
	time_t tm = 0;
	tm = time(NULL);
	char lpstrFilename[256] = { 0 };
	sprintf_s(lpstrFilename, sizeof(lpstrFilename), "test.bmp");

	WriteBitmapFile(lpstrFilename, 1280, 720, (unsigned char*)screenData);
	//�ͷ��ڴ�
	cout << "done" << endl;
	free(screenData);

}
