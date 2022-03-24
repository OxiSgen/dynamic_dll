// Gladkov_console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//#include "resource.h"
//#include "pch.h"
#include "framework.h"
#include <vector>
#include <fstream>
#include <vector>
#include <thread>
#include <string>
#include <iostream>
#include <windows.h>
#include <valarray>
#include <afxsock.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


///////////////////////////////////////////////////////////////////////
typedef void (WINAPI* PFN_FtOfS)(void);
typedef int (WINAPI* PFN_IntSh)(void);
typedef void (*PFN_sendIntSh)(int);
typedef void (* PFN_StringSh)(char* , int);
//////////////////////////////////////////////////////////////////////

CWinApp theApp;


HANDLE gotovo = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

int sendThreadID = -2;
int count_thread = 1;

char* message;

vector<HANDLE> SendEvents;
vector<HANDLE> MessageEvents;

HINSTANCE hDll45;

PFN_FtOfS LaunchClient;
PFN_FtOfS StartServerService;
PFN_IntSh GetInt;
PFN_sendIntSh SendInt;
PFN_FtOfS Connect;
PFN_IntSh ServerDisconnect;
PFN_StringSh GetString;

void LibConect()
{
	short TransportChannel = 1;
	LPCSTR dllname;
	printf("Choose your fighter\n1.Named pipes.\n2.Socket\n");
	while (!(cin >> TransportChannel) || TransportChannel < 1 || TransportChannel > 2)
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Oops, that input is invalid.  Please try again.\n";
	}
	if (TransportChannel == 1)
		dllname = "C:\\Users\\vipda\\Desktop\\l3\\Debug\\Gladkov_DLL";
	else
		dllname = "C:\\Users\\vipda\\Desktop\\l3\\Debug\\Gladkov5_DLL";
	if ((hDll45 = AfxLoadLibrary(dllname)) == NULL) cout << "Ne udalos' zagruxit'\n";

	LaunchClient = (PFN_FtOfS)GetProcAddress(hDll45, "LaunchClient");
	StartServerService = (PFN_FtOfS)GetProcAddress(hDll45, "StartServerService");
	GetInt = (PFN_IntSh)GetProcAddress(hDll45, "GetInt");
	SendInt = (PFN_sendIntSh)GetProcAddress(hDll45, "SendInt");
	Connect = (PFN_FtOfS)GetProcAddress(hDll45, "Connect");
	ServerDisconnect = (PFN_IntSh)GetProcAddress(hDll45, "ServerDisconnect");
	GetString = (PFN_StringSh)GetProcAddress(hDll45, "GetString");
}



UINT ThreadStart(LPVOID lpParameter)
{
	int id = (int)lpParameter - 1;
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Thread " << id << " created" << endl;
	ReleaseMutex(hMutex);


	HANDLE Events[2] = { SendEvents[id], MessageEvents[id] };
	while (1) {
		DWORD evNum = WaitForMultipleObjects(2, Events, FALSE, INFINITE) - WAIT_OBJECT_0;
		switch (evNum) {
		case 0:
		{
			WaitForSingleObject(hMutex, INFINITE);
			SendEvents.pop_back();
			MessageEvents.pop_back();
			cout << "Thread " << id << " done" << endl;
			ReleaseMutex(hMutex);
			SetEvent(gotovo);
			return 0;
		}
		case 1:
		{
			ResetEvent(Events[1]);
			WaitForSingleObject(hMutex, INFINITE);
			ofstream f(to_string(id) + ".txt");
			f << message;
			f.close();
			ReleaseMutex(hMutex);
			SetEvent(gotovo);
			break;
		}
		}
	}
	return 0;
}

void start()
{

	while (1)
	{
		Connect();
		int evNum = GetInt();
		switch (evNum)
		{
		case 0: //start
		{
			SendEvents.push_back(CreateEvent(NULL, FALSE, FALSE, NULL));
			MessageEvents.push_back(CreateEvent(NULL, FALSE, FALSE, NULL));
			thread MT(ThreadStart, (LPVOID)count_thread++);
			MT.native_handle();
			MT.detach();
			break;
		}
		case 1: //stop
		{
			SetEvent(SendEvents.back());
			SetEvent(SendEvents.back());
			WaitForSingleObject(gotovo, INFINITE);
			count_thread--;
			break;
		}
		//case 2: //quite
		//{
		//	//SendEvents.clear();
		// //   MessageEvents.clear();
		//	//count_thread = 0;
		//	//exit(0);
		//	break;
		//}
		case 2: //send
		{
			sendThreadID =GetInt();
			int size = 0;
			size = GetInt();
			message = new char[size];
			GetString(message, size);

			if (sendThreadID == -1) {

				cout << "Main Thread: " << message << endl;

			}
			else if (sendThreadID == -2) {
				cout << "All Thread poluchili messagi" << endl;
				for (auto MessEv : MessageEvents) {
					SetEvent(MessEv);
					WaitForSingleObject(gotovo, INFINITE);
				}
			}
			else if (sendThreadID >= 0) {
				cout << "You can send message only for main thred and all threas\n";
			}
			delete[] message;
			break;
		}
		}
		SendInt(SendEvents.size());
		ServerDisconnect();
	}
}



int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// инициализировать MFC, а также печать и сообщения об ошибках про сбое
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: вставьте сюда код для приложения.
			wprintf(L"Критическая ошибка: сбой при инициализации MFC\n");
			nRetCode = 1;
		}
		else
		{
			LibConect();
			cout << ("Number of clients:\n");
			int a;
			cin >> a;
			for (int i = 0; i < a; i++)
			{
				LaunchClient();
			}
			StartServerService();
			start();
		}
	}
	else
	{
		// TODO: измените код ошибки в соответствии с потребностями
		wprintf(L"Критическая ошибка: сбой GetModuleHandle\n");
		nRetCode = 1;
	}
	/*AfxFreeLibrary(hDll45);*/
	AfxFreeLibrary(hDll45);
	return nRetCode;
}
