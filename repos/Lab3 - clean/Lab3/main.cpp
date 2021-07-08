#include "stdlib.h"
#include "stdio.h"
#include "include\eTPkcs11.h"
#include <windows.h>
#include "base64.h"
#include <iostream>
#include "fstream"
#include "stdlib.h"
#include "stdio.h"
#include "iostream"
#include "include\eTPkcs11.h"
#include <windows.h>
#include <vector>
#include "base64.h"
#include <string>
#include <conio.h>


using namespace std;


void init();
void leave(const char*);
static void ImportPrivateKey(const char* fileName, const char* password);
static void GetPKBlob(CK_BYTE_PTR pk, int pkSize, CK_BYTE_PTR* subject, int* subjectSize);
static bool CreatePKFromBlob(CK_SESSION_HANDLE hSession, CK_BYTE_PTR key, int keySize);
static void ImportFile(const char* fileName, const char* label, const char* password);
static void ExportFile(const char* fileName, const char* password);
static void ReadLabel(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hLabel, CK_BYTE_PTR* label, DWORD* labelSize);
static void ReadValue(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hLabel, CK_BYTE_PTR* value, DWORD* valueSize);
static bool ExportFileA(CK_SESSION_HANDLE hSession, CK_BYTE_PTR* file, DWORD* fileSize, const char* fileName);
static bool DeletDataA(CK_SESSION_HANDLE hSession, const char* password);
static bool ReadFromFile(const char* fileName, CK_BYTE_PTR* file, DWORD* fileSize);
static bool CreatePKFromBlob(CK_SESSION_HANDLE hSession, CK_BYTE_PTR key, int keySize);



//Глобальные переменные
CK_FUNCTION_LIST_PTR   pFunctionList = NULL;
CK_C_GetFunctionList   pGFL = 0;
bool                   wasInit = false;

void init()
{
	// Загружаем dll
	HINSTANCE hLib = LoadLibraryA("etpkcs11.DLL");
	if (hLib == NULL)
	{
		leave("Cannot load DLL.");
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
		leave("Can't get function list. \n");
	}

	// Инициализируем библиотеку PKCS#11
	//
	if (CKR_OK != pFunctionList->C_Initialize(0))
	{
		leave("C_Initialize failed...\n");
	}
	wasInit = true;
}

static void leave(const char* message)
{
	if (message) printf("%s ", message);

	if (wasInit)
	{
		// Закрываем библиотеку PKCS#11
		if (CKR_OK != pFunctionList->C_Finalize(0))
		{
			printf("C_Finalize failed...\n");
		}

		wasInit = false;
	}

	exit(message ? -1 : 0);
}



/* Extracts the private key blob from pem */
static void GetPKBlob(CK_BYTE_PTR pk		// pem файл
	, int pkSize					// Размер файла
	, CK_BYTE_PTR* subject			// Указатель на раскодированный закр. ключ
	, int* subjectSize				// Размер закр. ключа
)
{
	unsigned int i, size = 0, count = 0;
	unsigned char* current = pk;
	unsigned char* start;
	unsigned char* end;

	*subject = NULL;
	*subjectSize = 0;
	//находим начало base64 данных
	while (current[0] != '-') *current++;
	while (current[0] == '-') *current++;
	while (current[0] != '-') *current++;
	while (current[0] == '-') *current++;
	start = ++current;
	while (current[0] != '-')
	{
		if ((current[0] == '\n') || (current[0] == '-')) count++;
		*current++;
	}
	end = current;
	size = (int)(end - start) - count;
	//создаем новый массив, без мешуры

	BYTE* newbyte = new BYTE[size];


	current = start;
	for (i = 0; i < size; i++)
	{
		if (current[0] == '\n') *current++;
		newbyte[i] = (BYTE)current[0];
		*current++;
	}

	*subject = base64_decode((char*)newbyte, size, (unsigned int*)subjectSize);

}

static CK_ULONG GetFirstSlotId()
{
	CK_ULONG slotID = -1;
	CK_ULONG ulCount = 0;
	CK_SLOT_ID_PTR pSlotIDs = NULL_PTR;
	CK_ULONG i;
	if (pFunctionList->C_GetSlotList(TRUE, NULL_PTR, &ulCount) == CKR_OK)
	{
		if (ulCount > 0)
		{
			pSlotIDs = new CK_SLOT_ID[ulCount];
			if ((pFunctionList->C_GetSlotList(TRUE, pSlotIDs, &ulCount)) == CKR_OK)
			{
				for (i = 0; i < ulCount; i++)
				{
					CK_SLOT_INFO info;
					if ((pFunctionList->C_GetSlotInfo(pSlotIDs[i], &info)) == CKR_OK)
					{
						if (info.flags & (CKF_HW_SLOT | CKF_TOKEN_PRESENT))
						{
							slotID = pSlotIDs[i];
							break;
						}
					}
				}
			}
		}
	}
	if (pSlotIDs)
	{
		delete[] pSlotIDs;
		pSlotIDs = NULL_PTR;
	}
	return slotID;
}

static bool ReadFromFile(const char* fileName, CK_BYTE_PTR* file, DWORD* fileSize)
{
	HANDLE hCert;
	hCert = CreateFileA(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	*fileSize = GetFileSize(hCert, NULL);
	*file = new byte[*fileSize];
	ReadFile(hCert, *file, *fileSize, NULL, NULL);
	CloseHandle(hCert);
	return true;
}

static bool CreatePKFromBlob(CK_SESSION_HANDLE hSession, CK_BYTE_PTR key, int keySize)
{
	CK_OBJECT_CLASS classAttr = CKO_PRIVATE_KEY;
	CK_KEY_TYPE keyType = CKK_RSA;
	unsigned long certCategory = 2;
	CK_BBOOL trueVal = CK_TRUE;
	CK_OBJECT_HANDLE hObject;


	if (key[0] != 0x30) return false; //РЅРµРІРµСЂРЅС‹Р№ С„РѕСЂРјР°С‚
	BYTE* modulus, *pubE, *privE, *p1, *p2, *e1, *e2, *coeff; //РєРѕРјРїРѕРЅРµРЅС‚С‹ Р·Р°РєСЂ. РєР»СЋС‡Р° 
	int modulusL, pubEL, privEL, p1L, p2L, e1L, e2L, coeffL; //РґР»РёРЅС‹ РєРѕРјРїРѕРЅРµРЅС‚РѕРІ  
	int cur = 0; while ((key[cur] != 0x02) || ((key[cur + 1] != 0x81) && (key[cur + 1] != 0x82))) { cur++; } cur++; 
	if (key[cur] == 0x81) { modulusL = key[cur + 1]; modulus = key + cur + 2; 
	if (key[cur + 2] == 0) { modulusL--; modulus++; cur++; } cur = cur + 2 + modulusL; } 
	if (key[cur] == 0x82) { modulusL = key[cur + 1] << 8 | key[cur + 2]; modulus = key + cur + 3; 
	if (key[cur + 3] == 0) { modulusL--; modulus++; cur++; } cur = cur + 3 + modulusL; }
	if (key[cur] != 0x02) return false; cur++; pubEL = key[cur]; pubE = key + cur + 1; cur = cur + 1 + pubEL;
	if (key[cur] != 0x02) return false; cur++;
	if (key[cur] == 0x81) { privEL = key[cur + 1]; privE = key + cur + 2; 
	if (key[cur + 2] == 0) { privEL--; privE++; cur++; } cur = cur + 2 + privEL; } 
	if (key[cur] == 0x82) { privEL = key[cur + 1] << 8 | key[cur + 2]; privE = key + cur + 3; 
	if (key[cur + 3] == 0) { privEL--; privE++; cur++; } cur = cur + 3 + privEL; }
	if (key[cur] != 0x02) return false; cur++; 
	if ((key[cur] == 0x81) || (key[cur] == 0x80)) cur++; p1L = key[cur]; p1 = key + cur + 1; 
	if (key[cur + 1] == 0) { p1L--; p1++; cur++; } cur = cur + 1 + p1L;
	if (key[cur] != 0x02) return false; cur++; 
	if ((key[cur] == 0x81) || (key[cur] == 0x80)) cur++; p2L = key[cur]; p2 = key + cur + 1; 
	if (key[cur + 1] == 0) { p2L--; p2++; cur++; } cur = cur + 1 + p2L;
	if (key[cur] != 0x02) return false; cur++; 
	if ((key[cur] == 0x81) || (key[cur] == 0x80)) cur++; e1L = key[cur]; e1 = key + cur + 1; 
	if (key[cur + 1] == 0) { e1L--; e1++; cur++; } cur = cur + 1 + e1L;
	if (key[cur] != 0x02) return false; cur++; 
	if ((key[cur] == 0x81) || (key[cur] == 0x80)) cur++; e2L = key[cur]; e2 = key + cur + 1; 
	if (key[cur + 1] == 0) { e2L--; e2++; cur++; } cur = cur + 1 + e2L;
	if (key[cur] != 0x02) return false; cur++; 
	if ((key[cur] == 0x81) || (key[cur] == 0x80)) cur++; coeffL = key[cur]; coeff = key + cur + 1; 
	if (key[cur + 1] == 0) { coeffL--; coeff++; }


	CK_ATTRIBUTE templateArray[] =
	{
	{CKA_CLASS, &classAttr, sizeof(classAttr)},
	{CKA_TOKEN, &trueVal, sizeof(trueVal)},
	{CKA_KEY_TYPE, &keyType, sizeof(keyType)},
	{CKA_MODULUS, modulus, modulusL},
	{CKA_PUBLIC_EXPONENT, pubE, pubEL},
	{CKA_PRIVATE_EXPONENT, privE, privEL},
	{CKA_PRIME_1, p1, p1L},
	{CKA_PRIME_2, p2, p2L},
	{CKA_EXPONENT_1, e1, e1L},
	{CKA_EXPONENT_2, e2, e2L},
	{CKA_COEFFICIENT, coeff, coeffL}
	};
	int sizeOfTemplate = sizeof(templateArray) / sizeof(CK_ATTRIBUTE);
	CK_RV rv = pFunctionList->C_CreateObject(hSession, templateArray,
		sizeOfTemplate, &hObject);
	if (rv) {
		return false;
	}
	return true;
}

static bool CreateFileFromBlob(CK_SESSION_HANDLE hSession, CK_BYTE_PTR file, int fileSize, const char* label)
{
	CK_OBJECT_HANDLE hObject;
	CK_OBJECT_CLASS your_class = CKO_DATA;
	CK_BBOOL token = CK_TRUE;
	CK_ATTRIBUTE templateArray[] = {
		{ CKA_CLASS, &your_class, sizeof(your_class) },
	{ CKA_TOKEN, &token, sizeof(token) },
	{ CKA_LABEL, (void*)label, 40},
	{ CKA_APPLICATION, NULL, NULL },
	{ CKA_VALUE, file, fileSize }
	};
	int sizeOfTemplate = sizeof(templateArray) / sizeof(CK_ATTRIBUTE);
	CK_RV rv = pFunctionList->C_CreateObject(hSession, templateArray,
		sizeOfTemplate, &hObject);
	if (rv) {
		return false;
	}
	return true;
}

static void ImportPrivateKey(const char* fileName, const char* password)
{
	CK_BYTE_PTR	pkfile = NULL;
	DWORD pkfileSize;
	CK_BYTE_PTR subject = NULL;
	int	subjSize;

	// Для работы с WinApi (запись)
	CK_SLOT_ID slotId;
	CK_SESSION_HANDLE hSession;
	cout << "Подождите, идет загрузка..." << endl;

	// Read the pem file
	ReadFromFile(fileName, &pkfile, &pkfileSize);
	cout << "PEM-файл прочитан!" << endl;

	// decode base64 and extract the private key blob
	GetPKBlob((unsigned char*)pkfile, pkfileSize, &subject, &subjSize);
	cout << "Файл декодирован и извлечен закрытый ключ." << endl;

	// Find connected token
	slotId = GetFirstSlotId();
	pFunctionList->C_OpenSession(slotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL, NULL, &hSession);
	cout << "Токен найден." << endl;

	// login to token
	pFunctionList->C_Login(hSession, CKU_USER, (LPBYTE)password, strlen(password));
	cout << "Успешная авторизация на токине!" << endl;

	// Import the private key to the token
	CreatePKFromBlob(hSession, subject, subjSize);
	cout << "Ключ импортирован!" << endl;

	// Close session
	pFunctionList->C_Logout(hSession);
	pFunctionList->C_CloseSession(hSession);
	cout << "Сессия закрыта." << endl;
	if (pkfile) {
		delete[] pkfile;
	}

}

static void ImportFile(const char* fileName, const char* label, const char* password)
{
	CK_BYTE_PTR		file = NULL;
	DWORD			fileSize;
	// Для работы с WinApi (запись)
	CK_SLOT_ID slotId;
	CK_SESSION_HANDLE hSession;

	// Read the pem file
	cout << "Подождите, идет чтение файла..." << endl;

	ReadFromFile(fileName, &file, &fileSize);

	// Find connected token
	cout << "Поиск токена..." << endl;
	slotId = GetFirstSlotId();
	pFunctionList->C_OpenSession(slotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL, NULL, &hSession);


	// login to token
	cout << "Авторизация..." << endl;
	pFunctionList->C_Login(hSession, CKU_USER, (LPBYTE)password, strlen(password));


	// Import the private key to the token
	cout << "Импорт файла..." << endl;
	CreateFileFromBlob(hSession, file, fileSize, label);
	cout << "Файл успешно импортирован!" << endl;

	// Close session
	pFunctionList->C_Logout(hSession);
	pFunctionList->C_CloseSession(hSession);
	cout << "Сессия закрыта." << endl;
	cout << "_____________________________________________________________________" << endl;
	if (file) {
		delete[] file;
	}
}

static void ExportFile(const char* fileName, const char* password)
{
	CK_BYTE_PTR		file = NULL;
	DWORD			fileSize;
	// Для работы с WinApi (запись)
	CK_SLOT_ID slotId;
	CK_SESSION_HANDLE hSession;

	// Find connected token
	cout << "Поиск токена..." << endl;
	slotId = GetFirstSlotId();
	pFunctionList->C_OpenSession(slotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL, NULL, &hSession);

	// login to token
	cout << "Авторизация..." << endl;
	pFunctionList->C_Login(hSession, CKU_USER, (LPBYTE)password, strlen(password));

	ExportFileA(hSession, &file, &fileSize, fileName);

	pFunctionList->C_Logout(hSession);
	pFunctionList->C_CloseSession(hSession);
	cout << "Сессия закрыта." << endl;
	cout << "_____________________________________________________________________" << endl;

	if (file) {
		delete[] file;
	}
}

static bool ExportFileA(CK_SESSION_HANDLE hSession, CK_BYTE_PTR* file, DWORD* fileSize, const char* fileName) {
	CK_OBJECT_HANDLE phObject[10];
	CK_ULONG objCount;
	CK_OBJECT_CLASS classAttr = CKO_DATA;
	CK_BBOOL trueVal = CK_TRUE;
	CK_ATTRIBUTE Template[] =
	{
		{ CKA_CLASS, &classAttr, sizeof(classAttr) },
		{ CKA_TOKEN, &trueVal, sizeof(trueVal) },
	};
	int rv = pFunctionList->C_FindObjectsInit(hSession, Template, (sizeof(Template) / sizeof(CK_ATTRIBUTE)));
	if (rv) leave("Cannot find data");
	pFunctionList->C_FindObjects(hSession, phObject, 10, &objCount);

	for (int i = 0; i < objCount; i++) {
		CK_BYTE_PTR label = NULL;
		DWORD labelsize;
		char buf[10];
		ReadLabel(hSession, phObject[i], &label, &labelsize);
		cout << "Получить объект " << label << "?\n";
		cin >> buf;
		if (buf[0] == 'y') {
			ReadValue(hSession, phObject[i], file, fileSize);
		}
	}

	HANDLE hFile;
	hFile = CreateFileA(fileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
	WriteFile(hFile, *file, *fileSize, 0, NULL);
	CloseHandle(hFile);
	return true;
}

static void ReadLabel(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hLabel, CK_BYTE_PTR* label, DWORD* labelSize) {
	CK_ATTRIBUTE ValueTemplate = { CKA_LABEL, NULL, 0 };
	int rv = pFunctionList->C_GetAttributeValue(hSession, hLabel, &ValueTemplate, 1);
	if (rv) leave("Cannot read data from the eToken");

	*labelSize = ValueTemplate.ulValueLen;
	*label = new BYTE[*labelSize];
	ValueTemplate.pValue = *label;
	rv = pFunctionList->C_GetAttributeValue(hSession, hLabel, &ValueTemplate, 1);
	if (rv) leave("Cannot read data from the eToken");
}

static void ReadValue(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hLabel, CK_BYTE_PTR* value, DWORD* valueSize) {
	CK_ATTRIBUTE ValueTemplate = { CKA_VALUE, NULL, 0 };
	int rv = pFunctionList->C_GetAttributeValue(hSession, hLabel, &ValueTemplate, 1);
	if (rv) leave("Cannot read data from the eToken");

	*valueSize = ValueTemplate.ulValueLen;
	*value = new BYTE[*valueSize];
	ValueTemplate.pValue = *value;
	rv = pFunctionList->C_GetAttributeValue(hSession, hLabel, &ValueTemplate, 1);
	if (rv) leave("Cannot read data from the eToken");
}

static void DeleteData(const char* password)
{

	CK_SLOT_ID slotId;
	CK_SESSION_HANDLE hSession;

	// Find connected token
	cout << "Поиск токена..." << endl;
	slotId = GetFirstSlotId();
	pFunctionList->C_OpenSession(slotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL, NULL, &hSession);

	// login to token
	cout << "Авторизация..." << endl;
	pFunctionList->C_Login(hSession, CKU_USER, (LPBYTE)password, strlen(password));


	DeletDataA(hSession, password);
	cout << "Данные удалены" << endl;

	// Close session
	pFunctionList->C_Logout(hSession);
	pFunctionList->C_CloseSession(hSession);
	cout << "Сессия закрыта." << endl;
	cout << "_____________________________________________________________________" << endl;

}

static bool DeletDataA(CK_SESSION_HANDLE hSession, const char* password)
{
	CK_OBJECT_HANDLE phObject[10];
	CK_ULONG objCount;
	CK_OBJECT_CLASS classAttr = CKO_DATA;
	CK_BBOOL trueVal = CK_TRUE;
	CK_ATTRIBUTE Template[] =
	{
		{ CKA_CLASS, &classAttr, sizeof(classAttr) },
		{ CKA_TOKEN, &trueVal, sizeof(trueVal) },
	};
	int rv = pFunctionList->C_FindObjectsInit(hSession, Template, (sizeof(Template) / sizeof(CK_ATTRIBUTE)));
	if (rv) leave("Cannot find data");
	pFunctionList->C_FindObjects(hSession, phObject, 10, &objCount);
	for (int i = 0; i < objCount; i++) {
		CK_BYTE_PTR label = NULL;
		DWORD labelsize;
		char buf[10];
		ReadLabel(hSession, phObject[i], &label, &labelsize);
		cout << "Удалить объект " << label << "?\n";
		cin >> buf;
		if (buf[0] == 'y') {
			pFunctionList->C_DestroyObject(hSession, phObject[i]);
		}


	}
	return true;
}



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	init();


	char path[100];
	char filepath[100];
	char filepath_export[100];
	char label[40];
	while (1) {
		if (argc > 1) {
			strncpy(path, argv[1], 99);
		}
		else {
			cout << "Введите путь к файлу с закрытым ключем и нажмите ENTER: ";
			cin.getline(path, 99);
		}
		ifstream file_in(path);

		if (!file_in) {
			cout << "Файл не найден " << endl;

		}
		else { break; }
	}



	while (1) {
		if (argc > 1) {
			strncpy(filepath_export, argv[1], 99);
		}
		else {
			cout << "Введите путь к файлу для экспорта и нажмите ENTER: ";
			cin.getline(filepath_export, 99);
		}
		ifstream file_in(filepath_export);

		if (!file_in) {
			cout << "Файл не найден " << endl;

		}
		else { break; }
	}
	char c;
	char password[20];
	cout << "Введите пароль:";
	gets_s(password);



	int key = 0;
	while (key >= 0 && key < 5)
	{
		cout << "Выбрете действие, которое хоите совершить: \n" <<
			"1 - Импорт закрытого ключа. \n" <<
			"2 - Импорт файла. \n" <<
			"3 - Экспорт файла. \n" <<
			"4 - Удаление файла. \n" <<
			"Для выхода - любое другое значение \n" <<
			"Ваш выбор: ";
		cin >> key;
		cout << "_____________________________________________________________________" << endl;
		switch (key)
		{
		case 1:
			ImportPrivateKey(path, password); break;
		case 2:
			while (1) {
				if (argc > 1) {
					strncpy(filepath, argv[1], 99);
				}
				else {
					cout << "Введите путь к файлу для импорта и нажмите ENTER: ";
					cin.getline(filepath, 99);
				}
				ifstream file_in(filepath);

				if (!file_in) {
					cout << "Файл не найден " << endl;

				}
				else { break; }
			}
			cout << "Введите название файла (лейбл): ";
			gets_s(label);

			ImportFile(filepath, label, password); break;
		case 3:
			ExportFile(filepath_export, password); break;
		case 4:
			DeleteData(password); break;
		}
	}



	getchar();
	leave(NULL);
	return 0;
}


