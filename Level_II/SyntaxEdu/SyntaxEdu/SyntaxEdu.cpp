// SyntaxEdu.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Sample.h"
#include "PresidentSingleton.h"
#include "BaseData.h"
#include "ComplexData.h"
#include "Fish.h"
#include "Human.h"
using namespace std;

void DoSomething(Human huma);

void SampleSayWothoutCopy(Sample sample)
{
	cout << endl << sample.GetName() << "\t" << sample.GetAge() << endl;
}

int main()
{
	
	{
		Sample sample("Hello Sergey", 40);
		cout << endl << sample.GetName() << "\t" << sample.GetAge() << endl;
	}
	Sample sample("Hello Sergey again - it's me", 40);
	SampleSayWothoutCopy(sample);
	cout << endl <<sample.GetName() << "\t"<<sample.GetAge() <<endl;

	cout << endl << "President of Russia" << endl;
	President& Putin = President::GetInstance();
	Putin.SetName("Putin V.V.");

	cout << Putin.GetName(sample) << endl;

	President& Medvedev = President::GetInstance();

	cout << endl << " President Russia (this is a new instance) = " <<  Medvedev.GetName(sample);

	BigData* pB = new BigData;

	BigData::DestroyBigData(pB);
	pB = nullptr;
	BigData::DestroyBigData(pB);
	//BigData::DestroyBigData(pB);

	cout << "\nComplex type\n";
	SimpleUnion u1, u2;
	u1.num = 1;
	u2.num = 2;
	u1.alphabet = 'C';
	u2.alphabet = 'T';
	cout << u1.alphabet << " " << u1.num << endl;

	ComplexType data1;
	data1.Type = ComplexType::Int;
	data1.value.num = 2017;
	DisplayComplexType(data1);


	// inheritance
	Treska treska;
	treska.SetName("Ann");
	treska.Swim(true);

	int* p_mega = new int(100);
	cout << "\np_mega address is " << p_mega;
	cout << "\ncontent by address is " << *p_mega;
	delete p_mega;

	Human human(10);
	DoSomething(human);

	cout << "\nnext...";

	// Не явный выхов - запрещено с ключевым объявлением конструктора explicit
	//DoSomething(5);


}

void DoSomething(Human human)
{
	cout << "\nHuman translate " << &human << " " << human.GetAge();
}