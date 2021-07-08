#include <iostream>
#include <string>
using namespace std;

// Возвращается истина, если карта действительна
bool checkLuhn(const string& NumerKart)
{
	int nDigits = NumerKart.length();

	int nSum = 0, isSecond = false;
	for (int i = nDigits - 1; i >= 0; i--) {

		int d = NumerKart[i] - '0';

		if (isSecond == true)
			d = d * 2;
				
		nSum += d / 10;
		nSum += d % 10;

		isSecond = !isSecond;
	}
	return (nSum % 10 == 0);
}

int main()
{
	string NumerKart;
	cout << "Vvedite nomer karty: ";
	cin >> NumerKart;
	//string NumerKart = "6764546214060639"; //valid
	//string NumerKart = "6764546214060631"; //not valid
	if (checkLuhn(NumerKart))
		printf("This is a valid card");
	else
		printf("This is not a valid card");
	return 0;
}