// OverridingBoss.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;
class Enemy
{
protected: 
	int *pDamage;
public:
	Enemy(int damage = 10);
	virtual ~Enemy();
	void virtual Taunt() const;
	void virtual Attack() const;
};

Enemy::Enemy(int damage)
{
	pDamage = new int(damage);
}

Enemy::~Enemy()
{
	cout << "In Enemy destructor pDamage.\n";
	delete pDamage;
	pDamage = 0;
}

void Enemy::Taunt() const
{
	cout << "The enemy says he will fight you.\n";
}

void Enemy::Attack() const
{
	cout << "Attack !!! Inflicts " << *pDamage << " damage points.";
}

class Boss : public Enemy
{
private: 
	int* pMultiplayer;
public:
	Boss(int multi = 3);
	virtual ~Boss();
	void virtual Taunt() const;
	void virtual Attack() const;
};

Boss::Boss(int multi)
{
	pMultiplayer = new int(multi);
}

Boss::~Boss()
{
	cout << "In Boss destructor pMulti.\n";
	delete pMultiplayer;
	pMultiplayer = 0;
}

void Boss::Taunt() const
{
	cout << "The boss says he will end your pitiful existence.\n";
}

void Boss::Attack() const
{
	Enemy::Attack();
	cout << "А boss attacks and inflicts " << (*pDamage) * (*pMultiplayer)
		<< " damage poi nts.";
	cout << "And laughs heartily at you.\n";
}

int main()
{
	/**cout << "Enemy object:\n";
	Enemy anEnemy;
	anEnemy.Taunt();
	anEnemy.Attack();
	cout << "\n\nBoss object:\n";
	Boss aBoss(100);
	aBoss.Taunt();
	aBoss.Attack();*/

	Enemy* pBadGuy = new Boss();
	pBadGuy->Attack();
	delete pBadGuy;
	pBadGuy = 0;
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
