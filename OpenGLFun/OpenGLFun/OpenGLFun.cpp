// OpenGLFun.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "glut.h"
#include <stdio.h>


GLuint texture;

#pragma warnings(disable: 4996)
bool loadTexture(const char* filename)
{
	unsigned char header[54];
	unsigned char* data;
	int dataPos;
	int width;
	int height;
	int imageSize;
	FILE * file = fopen(filename, "rb");
	if (!file) return false;
	if (fread(header, 1, 54, file) != 54) return false;
	if (header[0] != 'B' || header[1] != 'M') return false;
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return true;
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV, GL_MODULATE);
}

void draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

void draw2()
{
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.3f, -0.4f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.9f, -0.4f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.6f, -0.9f);

	glEnd();
}

void drawTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(0.0, 0.0);
	glTexCoord2d(1.0, 0.0); glVertex2d(0.5, 0.0);
	glTexCoord2d(1.0, 1.0); glVertex2d(0.5, 0.5);
	glTexCoord2d(0.0, 1.0); glVertex2d(0.0, 0.5);
	glEnd();
}

void drawQuad()
{
	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.1f, -0.1f);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.6f, -0.6f);
	glVertex2f(0.6f, -0.1f);

	glEnd();
}

void update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//draw();
	//draw2();
	//drawQuad();
	drawTexture();
	glFlush();
}


int main()
{
	glutCreateWindow("GL Fun");
	glutInitWindowSize(320, 320);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(update);
	initGL();
	loadTexture("test.bmp");
	glutMainLoop();
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
