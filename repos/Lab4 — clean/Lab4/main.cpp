#include "stdlib.h"
#include "stdio.h"
#include "include\eTPkcs11.h"
#include <windows.h>

#include <iostream>
#include <cstring>


using namespace std;

//#define PATH_FILE "C:\\Users\\vlad_\\1.txt"
#define PATH_FILE "C:\\1.txt"
#define PASSWD "12345"

void init();
void leave(const char*);

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

		wasInit = false;
	}

	exit(message ? -1 : 0);
}



/* Convinience method to retrieve the first PKCS#11 slot of a connected token */
static CK_ULONG GetFirstSlotId() {
	CK_ULONG slotID = -1;
	CK_ULONG ulCount = 0;
	CK_SLOT_ID_PTR pSlotIDs = NULL_PTR;
	CK_ULONG i;

	if (pFunctionList->C_GetSlotList(TRUE, NULL_PTR, &ulCount) == CKR_OK) {
		if (ulCount > 0) {
			pSlotIDs = new CK_SLOT_ID[ulCount];
			if ((pFunctionList->C_GetSlotList(TRUE, pSlotIDs, &ulCount)) == CKR_OK) {
				for (i = 0; i < ulCount; i++) {
					CK_SLOT_INFO info;
					if ((pFunctionList->C_GetSlotInfo(pSlotIDs[i], &info)) == CKR_OK) {
						if (info.flags & (CKF_HW_SLOT | CKF_TOKEN_PRESENT)) {
							slotID = pSlotIDs[i];
							break;
						}
					}
				}
			}
		}
	}

	if (pSlotIDs) {
		delete[] pSlotIDs;
		pSlotIDs = NULL_PTR;
	}

	return slotID;
}

//Читаем файл в массив byte
static bool ReadDataFromFile(const char* fileName, CK_BYTE_PTR* data, DWORD* dataSize)
{
	bool ret = false;


	HANDLE file = CreateFileA(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (file != INVALID_HANDLE_VALUE) {
		DWORD size = GetFileSize(file, NULL);
		if (size != INVALID_FILE_SIZE) {
			*data = new BYTE[size];
			if (ReadFile(file, *data, size, dataSize, NULL)) {
				ret = true;
			}
		}
		CloseHandle(file);
	}
	return true;
}

//записываем массив в файл
static bool SaveDataToFile(const char* fileName, CK_BYTE_PTR* data, DWORD* dataSize)
{
	bool ret = true;


	HANDLE file = CreateFileA(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file != INVALID_HANDLE_VALUE) {

		DWORD tmp = 0;
		if (WriteFile(file, *data, *dataSize, &tmp, NULL)) {
			ret = false;
		}
		CloseHandle(file);
	}
	return ret;
}


CK_OBJECT_CLASS        cko_SecretKey = CKO_SECRET_KEY;
CK_KEY_TYPE            ckk_DES3 = CKK_DES3;
CK_BYTE                ck_False = FALSE;
CK_MECHANISM           ckm_DES3_KEY_GEN = { CKM_DES3_KEY_GEN, NULL, 0 };
CK_MECHANISM           ckm_DES3 = { CKM_DES3_CBC, NULL, 0 };

#define sizeofarray(a) (sizeof(a)/sizeof(a[0]))
// Создаем сессионный ключ шифрования
CK_OBJECT_HANDLE CreateSessionKey(CK_SESSION_HANDLE hSession)
{
	CK_ATTRIBUTE SessionKeyTemplate[] =
	{
		{ CKA_CLASS,      &cko_SecretKey, sizeof(cko_SecretKey)},
		{ CKA_KEY_TYPE,   &ckk_DES3,      sizeof(ckk_DES3)},
		{ CKA_TOKEN,      &ck_False,      sizeof(ck_False)}
	};

	CK_OBJECT_HANDLE hSessionKey = NULL;

	int rv = pFunctionList->C_GenerateKey(
		hSession,
		&ckm_DES3_KEY_GEN,
		SessionKeyTemplate,
		sizeofarray(SessionKeyTemplate),
		&hSessionKey);
	if (rv != CKR_OK) leave("Failed to create session key");

	return hSessionKey;
}

int main()
{
	init();
	char path[100] = PATH_FILE;
	char pass[20] = PASSWD;

	printf("Path to file:%s\n", path);
	printf("Token PIN:%s\n", pass);

	// Находим токен
	CK_ULONG slotID = GetFirstSlotId();
	if (slotID == -1) {
		leave("No token is connected.");
	}


	// Логин
	CK_SESSION_HANDLE hSession;
	if (pFunctionList->C_OpenSession(slotID, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL, NULL, &hSession) != CKR_OK) {
		leave("Unable to open session with the token.");
	}

	if (pFunctionList->C_Login(hSession, CKU_USER, (LPBYTE)pass, strlen(pass)) != CKR_OK) {
		leave("Unable to login to token.");
	}

	CK_BYTE_PTR		file = NULL;
	DWORD					fileSize;

	// Читаем файл
	if (!ReadDataFromFile(path, &file, &fileSize)) {
		leave("Unable to read  file.");
	}

	/*
		Нужно сделать:
		1. Создать ключ шифрования
		2. Зашифровать данные из файла
		3. Расшифровать данные и вывести в консоль.
		При шифровании, необходимо создать буфер длиной 128 байт, в который буду помещаться данные из файла.
	*/

	CK_OBJECT_HANDLE hKey;

	//создайте ключ шифрования

	DWORD encrSize = (fileSize % 128 != 0) ? ((fileSize / 128) + 1) * 128 : fileSize; //вычисляем длину в байтах, с учетом того, на вход шифратора идут блоки по 128 байт


	CK_BYTE_PTR pEncryptedData = new byte[encrSize], pDecrData = new byte[encrSize];
	CK_ULONG_PTR EncrLen = new CK_ULONG, DecrLen = new CK_ULONG;
	CK_BYTE_PTR buffer = new byte[128]; //

	int BLOCK_COUNT = encrSize / 128;
	int FULL_BLOCK = BLOCK_COUNT * encrSize;
	printf("Block size: %u->%u->%u\n", fileSize, encrSize, BLOCK_COUNT);
	CK_BYTE** BuffPtr = new CK_BYTE*[BLOCK_COUNT];
	CK_BYTE** EncBuffPtr = new CK_BYTE*[BLOCK_COUNT];

	CK_BYTE * newEnByte = new CK_BYTE[FULL_BLOCK];
	CK_BYTE * newDnByte = new CK_BYTE[FULL_BLOCK];

	// Show text
	//printf("\n------------------\n%s\n------------------\n", file);
	//block = block2;
	//buffPtr[0] = file;
	int a = 0;
	//strncpy(Block1, Part1, 128 );
	//Block1[128] = 0;
	CK_RV ret;
	char currentBlock[128]; int block_size_plus = (sizeof(currentBlock)); int block_size_dec = (sizeof(currentBlock));
	hKey = CreateSessionKey(hSession);
	CK_BYTE_PTR s1 = new byte[encrSize];
	printf("\tSession Key created\n");
	for (int i = 0; i < BLOCK_COUNT; i++)
	{
		BuffPtr[i] = file + a;
		a += 128;
		strncpy(currentBlock, (char*)BuffPtr[i], 128);
		printf("\n\tBlock: %u\n\n%s\n", i, currentBlock);

		//зашифровываем
		ret = pFunctionList->C_EncryptInit(hSession, &ckm_DES3, hKey);
		if (ret != CKR_OK) {
			printf("\tFailed in C_EncryptInit\n");
			return 1;
		}

		//Do the encryption
		ret = pFunctionList->C_Encrypt(hSession, (CK_BYTE_PTR)currentBlock,
			sizeof(currentBlock), (CK_BYTE_PTR)pEncryptedData, &encrSize);
		if (ret != CKR_OK) {
			printf("\tFailed in C_Encrypt\n");
			return 1;
		}
		
		printf("\n\tEnctypted block: %u\n\n", i);
		memcpy(newEnByte+(block_size_plus), pEncryptedData, sizeof(currentBlock));
		block_size_plus += (sizeof(currentBlock));
		for (int j = 0; j < encrSize; j++)
			printf("%c", pEncryptedData[j]);
		printf("\n\tDecrypted block: %u\n\n", i);
		
		pFunctionList->C_DecryptInit(hSession, &ckm_DES3, hKey);
		pFunctionList->C_Decrypt(hSession, pEncryptedData, 128, pDecrData, DecrLen);
		memcpy(newDnByte + (block_size_dec), pDecrData, sizeof(currentBlock));
		block_size_dec += (sizeof(currentBlock));
		for (int j = 0; j < encrSize; j++)
			printf("%c", pDecrData[j]);
		
	}
	printf("\n\n\n\tEnctypted text\n\n");
	for (int j = 0; j < FULL_BLOCK; j++)
		printf("%c", newEnByte[j]);

	printf("\n\n\n\tDecrypted text\n\n");
	for (int j = 0; j < FULL_BLOCK; j++)
		printf("%c", newDnByte[j]);
	/*
	printf("\nEncrypted Data\n");
	for (int i=0; i<BLOCK_COUNT; i++) {
		printf("\nblock: %u\n",i);
		for (int j=0; j<encrSize; j++)
				printf("%c", EncBuffPtr[i][j]);
	}
	*/
	/*printf("\nDecrypted Data\n");
	for (int i=0; i<BLOCK_COUNT; i++) {
		printf("\nblock: %u\n",i);
		pFunctionList->C_DecryptInit(hSession, &ckm_DES3, hKey);
		pFunctionList->C_Decrypt(hSession, EncBuffPtr[i], 128, pDecrData, DecrLen);
		for (int j=0; j<encrSize; j++)
			printf("%c",pDecrData[j]);
	}
	*/
	//for (int i = 0;i < BLOCK_COUNT;i++)
	//{
	//printf("\n\n\n\nENbBlock: %u\n-------\n%s\n-------\n",i,(char*)EncBuffPtr[i]);
	//}
	//выводим что зашифровали
	//printf("Encrypted data: \n");
	//for (int i=0; i<encrSize; i++) printf("%c",pEncryptedData[i]);

	//расшифровываем



	//выводим что расшифровали
	//printf("\nDecrypted data: \n");
	//for (int i=0; i<encrSize; i++) printf("%c",pDecrData[i]);


	// Закрываем
	pFunctionList->C_Logout(hSession);
	pFunctionList->C_CloseSession(hSession);
	getchar();
	delete[] buffer;
	delete[] pEncryptedData;
	delete[] pDecrData;
	leave(NULL);

	return 0;
}