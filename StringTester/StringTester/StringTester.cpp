// StringTester.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string word1 = "Game";
	string word2("Over");
	string word3(3, '!');
	string phrase = word1 + " " + word2 + word3;
	cout << "The phrase is " << phrase << endl << endl; 
	cout << "The phrase has " << phrase.size() << " characters in it.\n\n"; 
	cout << "The character at position 0 is:  " << phrase[0] << "\n\n";
	cout << "Changing the character at position 0 \n";
	phrase[0] = 'L';
	cout << "The phrase is now:" << phrase << endl << endl;
	for (unsigned int index = 0; index < phrase.size(); index++)
	{
		cout << "The character at position " << index << " is " << phrase[index] << "\n";
	}
	cout << "\nThe sequience 'Over' begins at location ";
	cout << phrase.find("Over") << endl;
	if (phrase.find("eggplant") == string::npos)
	{
		cout << "'eggplant' is not int the phrase.\n\n";
	}
	phrase.erase(4, 5);
	cout << "The phrase is now:" << phrase << endl;
	phrase.erase(4);
	cout << "The phrase is now:" << phrase << endl;
	phrase.erase();
	cout << "The phrase is now:" << phrase << endl;
	if (phrase.empty())
	{
		cout << "\nThe phrase is no more.\n";
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
