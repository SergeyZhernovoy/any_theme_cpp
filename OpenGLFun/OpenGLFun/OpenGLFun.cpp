// OpenGLFun.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "glut.h"
#include <cstdio>

void initGL();
void update();
GLuint texture;

#pragma warnings(disable: 4996)
bool loadTexture(const char* filename)
{
	unsigned char header[54];
	unsigned char* data;
	int dataPos, width, heiht, imageSize;

	FILE* file = fopen(filename, "rb");
	if (!file) return false;

}




int main()
{
	glutCreateWindow("GL Fun");
	glutInitWindowSize(320, 320);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(update);
	initGL();
	glutMainLoop();
	return 0;
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	drawQuad();
	glFlush();
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
