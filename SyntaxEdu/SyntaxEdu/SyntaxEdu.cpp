// SyntaxEdu.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Sample.h"
#include "PresidentSingleton.h"
#include "BaseData.h"
using namespace std;

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

	cout << Putin.GetName() << endl;

	President& Medvedev = President::GetInstance();

	cout << endl << " President Russia (this is a new instance) = " <<  Medvedev.GetName();

	BigData* pB = new BigData;

	BigData::DestroyBigData(pB);
	pB = nullptr;
	BigData::DestroyBigData(pB);
	//BigData::DestroyBigData(pB);


}
