#include "stdlib.h"
#include "stdio.h"
#include "include\eTPkcs11.h"
#include <windows.h>
#include <iostream>
using namespace std;

//Глобальные переменные
CK_FUNCTION_LIST_PTR   pFunctionList = NULL;
CK_C_GetFunctionList   pGFL = 0;
bool                   wasInit = false;

static void ImportCertificate(const char* fileName, const char* password);
static bool ReadCertFromFile(const char* fileName, CK_BYTE_PTR* cert, DWORD* certSize);
static void GetX509Subject(CK_BYTE_PTR cert, int certSize, CK_BYTE_PTR* subject, int* subjectSize);
static bool CreateCertFromBlob(CK_SESSION_HANDLE hSession, CK_BYTE_PTR cert, int certSize, CK_BYTE_PTR subject, int subjSize);
static CK_ULONG GetFirstSlotId();

static bool ReadCertFromFile(const char* fileName, CK_BYTE_PTR* cert, DWORD* certSize)
{
	bool output;
	HANDLE hCert;
	hCert = CreateFileA(fileName,
						GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
						OPEN_EXISTING,
						0,
						NULL
						);
	*certSize = GetFileSize(hCert, NULL);
	*cert = new CK_BYTE[*certSize];
	output = ReadFile(hCert, *cert, *certSize, NULL, NULL);
	return output;
}


static bool CreateCertFromBlob(CK_SESSION_HANDLE hSession	// ID сессии
								, CK_BYTE_PTR cert			// сертификат
								, int certSize				// размер сертификата
								, CK_BYTE_PTR subject		// субъект сертификата
								, int subjSize				// размер субъекта
								)
{
	CK_OBJECT_CLASS classAttr = CKO_CERTIFICATE;
	CK_CERTIFICATE_TYPE certType = CKC_X_509;
	unsigned long certCategory = 2;
	CK_BBOOL trueVal = CK_TRUE;
	CK_OBJECT_HANDLE hObject;

	CK_ATTRIBUTE templateArray[] = { {CKA_CLASS, &classAttr, sizeof(classAttr)},
									{CKA_CERTIFICATE_TYPE, &certType, sizeof(certType)},
									{CKA_TOKEN, &trueVal, sizeof(trueVal)},
									{CKA_SUBJECT, subject, subjSize},
									{CKA_VALUE, (void*)cert, certSize},
									{CKA_CERTIFICATE_CATEGORY, (void*)&certCategory, sizeof(certCategory)},
									};
	int sizeOfTemplate = sizeof(templateArray) / sizeof(CK_ATTRIBUTE);
	CK_RV rv = pFunctionList->C_CreateObject(hSession, templateArray, sizeOfTemplate, &hObject);
	if (rv)
	{
		return false;
	}
	return true;
}

static CK_ULONG GetFirstSlotId()
{
	CK_ULONG slotId = -1;
	CK_ULONG ulCount = 0;
	CK_SLOT_ID_PTR pSlotId = NULL_PTR;
	CK_ULONG i;

	if (pFunctionList->C_GetSlotList(TRUE, NULL_PTR, &ulCount) == CKR_OK)
	{
		if (ulCount > 0)
		{
			pSlotId = new CK_SLOT_ID[ulCount];
			if ((pFunctionList->C_GetSlotList(TRUE, pSlotId, &ulCount)) == CKR_OK)
			{
				for (i = 0; i < ulCount; i++)
				{
					CK_SLOT_INFO info;
					if ((pFunctionList->C_GetSlotInfo(pSlotId[i], &info)) == CKR_OK)
					{
						if (info.flags & (CKF_HW_SLOT | CKF_TOKEN_PRESENT))
						{
							slotId = pSlotId[i];
							break;
						}
					}
				}
			}
		}
	}
	if (pSlotId)
	{
		delete[] pSlotId;
		pSlotId = NULL_PTR;
	}
	return slotId;
}

static void ImportCertificate(const char* fileName, const char* password)
{
	CK_BYTE_PTR cert = NULL;
	DWORD certSize;
	CK_BYTE_PTR subject = NULL;
	int subjSize;
	if (!ReadCertFromFile(fileName, &cert, &certSize))
	{
		return;
	}
	GetX509Subject(cert, certSize, &subject, &subjSize);
	CK_SESSION_HANDLE hSession;
	CK_SLOT_ID slotId = GetFirstSlotId();
	pFunctionList->C_OpenSession(slotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL, NULL, &hSession);
	pFunctionList->C_Login(hSession, CKU_USER, (LPBYTE)password, strlen(password));
	CreateCertFromBlob(hSession, cert, certSize, subject, subjSize);
	pFunctionList->C_Logout(hSession);
	pFunctionList->C_CloseSession(hSession);
}

static void GetX509Subject(CK_BYTE_PTR cert				// Сертификат в двоичном представлении
							, int certSize				// Размер сертификата
							, CK_BYTE_PTR* subject		// Указатель на массив информации о субъекте
							, int* subjectSize			// Размер информации о субъекте
							)
{
	unsigned int i;
	unsigned char* current = cert;
	unsigned char* prev;
	unsigned char* end = cert + certSize;
	unsigned char tags[] = { 0x30, 0,		// основная последовательность
							0x30, 0,		// последовательность, подписываемая ЭЦП
							0xa0, 1,		// версия
							0x02, 1,		// серийный номер
							0x30, 1,		// подпись
							0x30, 1,		// издатель
							0x30, 1,		// период действия
							0x30, 1,		// информация о субъекте
							};
	*subject = NULL;
	*subjectSize = 0;
	for (int i = 0; i < sizeof(tags); i+=2)
	{
		unsigned char v;
		unsigned int length = 0;
		prev = current;
		if (current + 2 > end) return;
		if (*current++ != tags[i]) return;
		v = *current++;

		if ((v & 0x80) == 0) length = v;
		else
		{
			unsigned char lenlen = v & 0x7f;
			if (current + lenlen > end) return;
			for (v = 0; v < lenlen; v++) length = (length << 8) + *current++;
		}
		if (tags[i + 1]) current += length;
	}
	*subject = prev;
	*subjectSize = (int)(current - prev);
}


void init();
void leave(const char*);



void init()
{
  // Загружаем dll
  HINSTANCE hLib = LoadLibraryA("etpkcs11.DLL");
  if (hLib == NULL)
  {
    leave ("Cannot load DLL.");
  }
  
  // Ищем точку входа для C_GetFunctionList

  (FARPROC&)pGFL= GetProcAddress(hLib, "C_GetFunctionList");

  if (pGFL == NULL) 
  {
    leave ("Cannot find GetFunctionList().");
  }

	//Берем список функций
  if (CKR_OK != pGFL(&pFunctionList))
  {
    leave ("Can't get function list. \n");
  }

  // Инициализируем библиотеку PKCS#11
  //
  if (CKR_OK != pFunctionList->C_Initialize (0))
  {
    leave ("C_Initialize failed...\n");
  }                 
  wasInit = true;      
}

static void leave(const char * message)
{
  if (message) printf("%s ", message);

	if(wasInit)
  {
		// Закрываем библиотеку PKCS#11
		if (CKR_OK != pFunctionList->C_Finalize(0))
		{
			printf ("C_Finalize failed...\n");
		}

    wasInit = false;
  }

	exit(message ? -1 : 0 );
}



int main()
{
	setlocale(LC_ALL, "Russian");
	init();
	char pathtocert[] = "C:\\Users\\vlad_\\Рабочий стол\\ПСОИБ\\лаб 2\\nvo.cer";
	char passcode[80];
	gets_s(passcode);
	printf("Cert path: %s\n", pathtocert);
	printf("Enter pass: %s\n", passcode);
	ImportCertificate(pathtocert, passcode);
	leave(NULL);
    return 0;
}