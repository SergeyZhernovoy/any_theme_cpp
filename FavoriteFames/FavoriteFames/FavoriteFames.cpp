// FavoriteFames.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
	vector<string> favouriteGames;
	vector<string>::iterator iter;
	char direction = '1';
	while (direction != '4')
	{
		cout << "\n\nList your favourite games\n";
		cout << "***********************\n";
		cout << "* 1. Add game         *\n";
		cout << "* 2. Delete game      *\n";
		cout << "* 3. Print list game  *\n";
		cout << "* 4. Exit             *\n";
		cout << "***********************\n";
		cout << ":>";
		cin >> direction;
		string gameTitle;
		if (direction == '1')
		{
			cout << "\n\nEnter game name for add:>";
			cin >> gameTitle;
			favouriteGames.push_back(gameTitle);
		}
		else if (direction == '2')
		{
			cout << "\n\nEnter game name for delete:>";
			cin >> gameTitle;
			iter = find(favouriteGames.begin(), favouriteGames.end(), gameTitle);
			while ( iter != favouriteGames.end())
			{
				favouriteGames.erase(iter);
				iter = find(favouriteGames.begin(), favouriteGames.end(), gameTitle);
			}
		}
		else if (direction == '3')
		{
			cout << "\nYou list favourite games\n";
			for (iter = favouriteGames.begin(); iter != favouriteGames.end(); iter++)
			{
				cout << *iter << endl;
			}
		}
	}
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
