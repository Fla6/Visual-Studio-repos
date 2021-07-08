//#include <iostream>
//#include <iomanip>
//
//using namespace std;
//
//const unsigned int DIM1 = 3;
//const unsigned int DIM2 = 5;
//
//int ary[DIM1][DIM2];
//
//int main() {
//
//	for (int i = 0; i < DIM1; i++) {
//		for (int j = 0; j < DIM2; j++) {
//			ary[i][j] = (i + 1) * 10 + (j + 1);
//		}
//	}
//	for (int i = 0; i < DIM1; i++) {
//		for (int j = 0; j < DIM2; j++) {
//			cout << setw(4) << ary[i][j];
//		}
//		cout << endl;
//	}
//
//	return 0;
//}




//#include <time.h>
//#include <iostream>
//#include <iomanip>
//
//using namespace std;
//
//const int size1 = 4;
//int arr[size1][size1];
//
//void delarr(int n, int a, int b)
//{
//	for (int i = 0; i < size1; i++)
//	{
//		for (int j = b; j < size1 - 1; j++)
//		{
//			arr[i][j] = arr[i][j + 1];
//		}
//	}
//
//	for (int i = a; i < size1 - 1; i++)
//	{
//		for (int j = 0; j < size1 - 1; j++)
//		{
//			arr[i][j] = arr[i + 1][j];
//		}
//	}
//}
//
//
//int main()
//{	
//	int a, b;
//	srand(time(NULL));
//
//	for (int i = 0; i < size1; i++)
//	{
//		for (int j = 0; j < size1; j++)
//		{
//			arr[i][j] = rand() % 10;
//			cout << setw(4) << arr[i][j];
//		}	
//		cout << endl;
//	}
//
//	cout << "\n";
//
//	cout << "1: ";
//	cin >> a;
//	cout << "2: ";
//	cin >> b;
//	
//	delarr(size1, a, b);
//	
//
//	for (int i = 0; i < size1 - 1; i++)
//	{
//		for (int j = 0; j < size1 - 1; j++)
//		{
//			cout << setw(4) << arr[i][j];
//		}
//		cout << endl;
//	}
//	return 0;      	  
//}



#include<stdio.h>
#include<stdlib.h>
#include<time.h>

extern void Ddelarr(int n, int k, int l);

int k, l;
enum num { n = 5 };
int mas[n][n];

void delarr(int n, int k, int l)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = l; j < n - 1; j++)
		{
			mas[i][j] = mas[i][j + 1];
		}
	}

	for (int i = k; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			mas[i][j] = mas[i + 1][j];
		}
	}
}

int main(void)

{

	printf("_____________________________________________\n");

	printf("Enter the number of row: ");
	scanf_s("%d", &k);

	printf("Enter the number of сolumn: ");
	scanf_s("%d", &l);


	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mas[i][j] = rand() % 20;
		}

	}


	printf("The generated array:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", mas[i][j]);
		}
		putchar('\n');
	}

	printf("_____________________________________________\n");

	//вот функция?
	//delarr(n, k, l);
	Ddelarr(n, k, l);

	printf("The new array:\n");

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			printf("%d ", mas[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
