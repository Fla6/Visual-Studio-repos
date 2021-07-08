#include "stdlib.h"
#include "stdio.h"
#include <windows.h>
#include "include\eTPkcs11.h"
#include <iostream>
using namespace std;

//Глобальные переменные 
CK_FUNCTION_LIST_PTR pFunctionList = NULL;
CK_C_GetFunctionList pGFL = 0;
bool wasInit = false;
static HANDLE hThread = 0;

static void leave(const char * message)
{
	if (message) printf("%s ", message);
	if (wasInit)
	{
		// Закрываем библиотеку PKCS#11 
		if (CKR_OK != pFunctionList->C_Finalize(0))
		{
			printf("C_Finalize failed...\n");
		}
		//ждем завершения работы потока, иначе убиваем его. 
		WaitForSingleObject(hThread, 5000);
		if (hThread) { TerminateThread(hThread, 0); CloseHandle(hThread); }
		hThread = 0;
		wasInit = false;
	}
	exit(message ? -1 : 0);
}

void init()
{
	// Загружаем dll 
	HINSTANCE hLib = LoadLibraryA("etpkcs11.DLL"); 
	if (hLib == NULL) 
	{ 
		leave ("Cannot load DLL."); 
	}
	// Ищем точку входа для C_GetFunctionList
	(FARPROC&)pGFL = GetProcAddress(hLib, "C_GetFunctionList");
	if (pGFL == NULL) 
	{ 
		leave("Cannot find GetFunctionList()."); 
	}
	//Берем список функций 
	if (CKR_OK != pGFL(&pFunctionList)) 
	{ 
		leave ("Can't get function list. \n"); 
	}
	// Инициализируем библиотеку PKCS#11
	if (CKR_OK != pFunctionList->C_Initialize(0)) 
	{ 
		leave("C_Initialize failed...\n"); 
	} 
	wasInit = true;
}

void displayLibraryInfo()
{
	CK_INFO* info = new CK_INFO;
	pFunctionList->C_GetInfo(info);
	cout << "PKCS #11 \t\t" << static_cast<int>(info->cryptokiVersion.major) 
			<< "." << static_cast<int>(info->cryptokiVersion.minor) << endl;
	cout << "Description \t\t" << info->libraryDescription <<endl;
	cout << "Library version \t" << static_cast<int>(info->libraryVersion.major) 
			<< "." << static_cast<int>(info->libraryVersion.minor) << endl;
	cout << "Manufacturer \t\t" << info->manufacturerID << endl;
}


void displayTokenInfo(DWORD slotId)
{
	CK_SLOT_INFO* slot_info = new CK_SLOT_INFO;
	CK_TOKEN_INFO* token_info = new CK_TOKEN_INFO;
	pFunctionList->C_GetSlotInfo(slotId, slot_info);
	pFunctionList->C_GetTokenInfo(slotId, token_info);
	cout << "\n\nПрисутствие eToken в слоте \t\t\t\t" << (slot_info->flags & CKF_TOKEN_PRESENT) << endl;
	cout << "К данному слоту подключено извлекаемое устройство \t" << (slot_info->flags & CKF_REMOVABLE_DEVICE) << endl;
	cout << "Слот аппаратный, иначе виртуальный \t\t\t" << (slot_info->flags & CKF_HW_SLOT) << endl;
	
	cout << "\n\n\n" << slot_info->slotDescription << endl;
	
	if (slot_info->flags & CKF_TOKEN_PRESENT)
	{
		cout << "\n\nToken is on" << endl;
		cout << "Manufacturer \t\t\t";
		for (int i = 0; i < 32; i++)
		{
			cout << token_info->manufacturerID[i];
		}
		cout << endl;
		cout << "Serial number \t\t\t" << token_info->serialNumber << endl;
		cout << "ulMaxSessionCount \t\t" << token_info->ulMaxSessionCount << endl;
		cout << "ulMaxRwSessionCount \t\t" << token_info->ulMaxRwSessionCount << endl;
		cout << "ulTotalPrivateMemory \t\t" << token_info->ulTotalPrivateMemory << endl;
		cout << "ulFreePrivateMemory \t\t" << token_info->ulFreePrivateMemory << endl;
		cout << "CKF_WRITE_PROTECTED \t\t" << (token_info->flags & CKF_WRITE_PROTECTED) << endl;
		cout << "CKF_USER_PIN_INITIALIZED \t" << (token_info->flags & CKF_USER_PIN_INITIALIZED) << endl;
	}
	else
	{
		cout << "\n\nToken was removed" << endl;
	}
}

static DWORD __stdcall TokenNotifyThread(void*) 
{
	while (true) 
	{
		DWORD slotId; 
		int res = pFunctionList->C_WaitForSlotEvent(0, &slotId, 0);
		if (res == CKR_OK) displayTokenInfo(slotId); 
		else break;
	} 
	return 0;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	init();
	displayLibraryInfo();
	hThread = CreateThread(NULL, 0, TokenNotifyThread, NULL, 0, NULL);
	getchar();
    return 0;
}