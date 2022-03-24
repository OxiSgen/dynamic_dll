// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "framework.h"
#include <string>
#include <vector>


using namespace std;


HANDLE hPipe;

extern "C"
{

	_declspec(dllexport) void _stdcall InitializationTransportTec()
	{

	}
	_declspec(dllexport) void _stdcall Disconnect()
	{
		CloseHandle(hPipe);
	}
	_declspec(dllexport) void _stdcall ConnectToServer() 
	{
		if (WaitNamedPipe("\\\\.\\pipe\\MyPipe", 3000))
		{
			hPipe = CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		}
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
		hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe",
		PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
			1024, 1024, 0, NULL);
	}

	_declspec(dllexport) int  GetInt() 
	{
		DWORD dwDone;
		int n;
		ReadFile(hPipe, &n, sizeof(int), &dwDone, NULL);
		return n;
	}

	_declspec(dllexport) void SendInt(int n) 
	{
		DWORD dwDone;
		WriteFile(hPipe, &n, sizeof(int), &dwDone, NULL);
		FlushFileBuffers(hPipe);
	}

	_declspec(dllexport) inline void _stdcall SendString(int numOfThread, char* str)
	{
		DWORD dwDone;
		int n = strlen(str) + 1;
		WriteFile(hPipe, &numOfThread, sizeof(numOfThread), &dwDone, NULL);
		WriteFile(hPipe, &n, sizeof(n), &dwDone, NULL);
		WriteFile(hPipe, str, n, &dwDone, NULL);
		FlushFileBuffers(hPipe);
	}

	_declspec(dllexport) inline int _stdcall Confirm() 
	{
		while (true) {
			int response = GetInt();
			if (response != 0) {
				return response;
			}
		}
	}

	_declspec(dllexport) void Connect() 
	{
		ConnectNamedPipe(hPipe, NULL);
	}

	_declspec(dllexport) int ServerDisconnect() 
	{
		DisconnectNamedPipe(hPipe); 
			return 1;
	}

	_declspec(dllexport) void GetString(char* message, int size) 
	{
		//DWORD dwDone;
		//int size = 0;
		//size = GetInt();
		//vector <char> message(size);
		//ReadFile(hPipe, &message[0], size, &dwDone, NULL); ???
		//char* mes = reinterpret_cast<char*>(message.data());
		//return mes;
		DWORD dwDone;
		ReadFile(hPipe, message, size, &dwDone, NULL);
	}
	//_declspec(dllexport) bool Bool4lab() {
	//	return flagd4();
	//}
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH: 
		break;
	}
	return TRUE;
}
