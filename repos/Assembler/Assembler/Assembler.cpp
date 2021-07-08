#include <iostream>
using namespace std;
int main()
{
	int c = 0;
	int a[10] = {1, 15, 55, 7, 8 , 92, 36, 45, 23, 66};
	for (int i = 0; i < 10; i++)
	{
		int b = a[i] + 107;
		if (b < 128)
		{
			c++;
		}
		
		cout << b << endl;
	}
	cout << "\n" << c << endl;
	return 0;
}