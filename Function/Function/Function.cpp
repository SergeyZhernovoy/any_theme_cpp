// Function.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int sayMessage(string);

int main()
{
	sayMessage("test");
	
	return 0;
}

int sayMessage(string message = "Please enter number")
{
	int number;
	cout << message << endl;
	cin >> number;
	return number;
}


