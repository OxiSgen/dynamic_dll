// Gladkov5_DLL.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "Gladkov5_DLL.h"
#include <afxsock.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CSocket* Socket;
CSocket Server;

extern "C"
{

	_declspec(dllexport) void _stdcall InitializationTransportTec()
	{
		AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
		AfxSocketInit();
	}
	_declspec(dllexport) void  Connect()
	{
		Socket = new CSocket;
		Server.Listen();
		Server.Accept(*Socket);
	}
	_declspec(dllexport) void  LaunchClient() 
	{
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		CreateProcessA(NULL, (LPSTR)"Gladkov_form.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	_declspec(dllexport) void  StartServerService() 
	{
		AfxSocketInit();
		Server.Create(8000);
	}

	_declspec(dllexport)  int  GetInt() 
	{
		int n;
		Socket->Receive(&n, sizeof(int));
		return n;
	}

	_declspec(dllexport)  void  SendInt(int n) 
	{
		Socket->Send(&n, sizeof(int));
	}

	_declspec(dllexport)  void  GetString(char* message, int size) 
	{
		//int n;
		//Socket->Receive(&n, sizeof(int));
		//char* h = new char[n];
		//Socket->Receive(h, n);
		//return h;
		Socket->Receive(message, sizeof(int));
	}

	_declspec(dllexport) void _stdcall SendString(int n, char* str) 
	{
		Socket->Send(&n, sizeof(int));
		int nLength = strlen(str) + 1;
		Socket->Send(&nLength, sizeof(int));
		Socket->Send(str, nLength);
	}

	_declspec(dllexport) int _stdcall Confirm()
	{
		while (true) {
			int response = GetInt();
			if (response != 0) {
				return response;
			}
		}
	}

	_declspec(dllexport) void _stdcall ConnectToServer() 
	{
		Socket = new CSocket;
		Socket->Create();

		Socket->Connect("127.0.0.1", 8000);
	}
	_declspec(dllexport) inline void _stdcall Disconnect() 
	{
		Socket->Close();
		delete Socket;
	}
	_declspec(dllexport) void ServerDisconnect() 
	{
		Socket->Close();
		delete Socket;
	}
	//_declspec(dllexport) bool Bool5lab() {
	//	return flag();
	//}
}


//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		должен стоять в качестве первого оператора в
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CGladkov5DLLApp

BEGIN_MESSAGE_MAP(CGladkov5DLLApp, CWinApp)
END_MESSAGE_MAP()


// Создание CGladkov5DLLApp

CGladkov5DLLApp::CGladkov5DLLApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CGladkov5DLLApp

CGladkov5DLLApp theApp;


// Инициализация CGladkov5DLLApp

BOOL CGladkov5DLLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
