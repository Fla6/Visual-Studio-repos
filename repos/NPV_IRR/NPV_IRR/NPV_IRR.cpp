#include "pch.h"
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	setlocale(LC_ALL,"Russian");
	float CF[8] = { -200000, 75000, 76000, 77000, 78000, 0, 0, 0 };
	float ra;
	float rb;
	cout << "Введите ставку дисконтирования: ";
	cin >> ra;
	float npva = 0;
	float npvb = 0;
	float irr = 0;
	float rent = 0;
	float rentlim = 15;
	for (int i = 0; i < 7; i++)
	{
		npva += CF[i] / powf((1 + ra), i);
	}
	cout << "\nNPV: " << npva << "р." << endl;
	cout << "\nПредположите ставку дисконтирования: ";
	cin >> rb;
	for (int i = 0; i < 7; i++)
	{
		npvb += CF[i] / powf((1 + rb), i);
	}
	cout << "\nNPV: " << npvb << "р." << endl;

	while (npvb > 0)
	{
		npvb = 0;
		cout << "\nПредположите другую ставку дисконтирования: ";
		cin >> rb;
		for (int i = 0; i < 7; i++)
		{
			npvb += CF[i] / powf((1 + rb), i);
		}
		cout << "\nNPV: " << npvb << "р." << endl;
	}

	irr = ra + (rb - ra) * (npva / (npva - npvb));
	cout << "\nIRR: " << irr << endl;

	rent = (npva / -CF[0]) * 100;
	cout << "\nRENT: " << rent << endl;
	if (rent >= rentlim)
	{
		cout << "\nИтог: Есть смысл вкладываться в проект" << endl;
	}
	else
	{
		cout << "\nИтог: Нет смысла вкладываться в проект" << endl;
	}
	
	return 0;
}


