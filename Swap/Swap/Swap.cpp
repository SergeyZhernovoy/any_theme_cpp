// Swap.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

using namespace std;
void badSwap(int, int);
void goodSwap(int&, int&);
int main()
{
	int myScore = 150;
	int yourScore = 1000;
	cout << "Original values\n";
	cout << "my score: " << myScore << endl;
	cout << "your score: " << yourScore << endl;
	cout << "Calling badSwap()\n";
	badSwap(myScore, yourScore);
	cout << "my score: " << myScore << endl;
	cout << "your score: " << yourScore << endl;
	cout << "Calling goodSwap()\n";
	goodSwap(myScore, yourScore);
	cout << "my score: " << myScore << endl;
	cout << "your score: " << yourScore << endl;
	return 0;
}

void badSwap(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}

void goodSwap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}