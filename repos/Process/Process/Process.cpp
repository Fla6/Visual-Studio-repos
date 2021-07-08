#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	if (CreateProcess(L"C:\\Windows\\notepad.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi) == TRUE)
	{
		cout << "process " << pi.dwProcessId << endl;
		cout << "Handle " << pi.hProcess << endl;
		Sleep(1000);
		TerminateProcess(pi.hProcess, NO_ERROR);
	}
	return 0;
}
