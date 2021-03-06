// MFCLibrary1.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "stdafx.h"
#include "MFCLibrary1.h"
#include "cartoteka.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable : 4996)







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

// CMFCLibrary1App

BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()


// Создание CMFCLibrary1App

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CMFCLibrary1App

CMFCLibrary1App theApp;


// Инициализация CMFCLibrary1App

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

vector<shared_ptr<employee>> empl;
cartoteka cartoteka1;

extern "C"
{
	_declspec(dllexport) void From_file()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		cartoteka1.fin();
	}

	_declspec(dllexport) void OFname(int i, char *str)
	{
		strcpy(str, cartoteka1.GetName(i));
	}

	_declspec(dllexport) void OFsurname(int i, char *str)
	{
		strcpy(str, cartoteka1.GetSurName(i));
	}
	_declspec(dllexport) void OFage(int i, char *str)
	{
		strcpy(str, cartoteka1.GetAge(i));
	}
	_declspec(dllexport) void OFposishion(int i, char *str)
	{
		strcpy(str, cartoteka1.GetPosition(i));
	}
	_declspec(dllexport) void OFempl(int i, char *str)
	{
		strcpy(str, cartoteka1.GetEMP(i));
	}
	_declspec(dllexport) void OFzarp(int i, char *str)
	{
		strcpy(str, cartoteka1.GetZarp(i));
	}

	_declspec(dllexport) void To_file()
	{
		cartoteka1.fin();
	}
	//_declspec(dllexport) void ochist()
	//{
	//	cartoteka1.ochistka();
	//}
	_declspec(dllexport) void InFname(int i, char *str)
	{
		cartoteka1.SetName(i, str);
	}
	_declspec(dllexport) void InFsurname(int i, char *str)
	{
		cartoteka1.SetSurname(i, str);
	}
	_declspec(dllexport) void InFage(int i, char *str)
	{
		cartoteka1.Setage(i, str);
	}
	_declspec(dllexport) void InFposishion(int i, char *str)
	{
		cartoteka1.SetPosition(i, str);
	}
	_declspec(dllexport) void InFempl(int i, char *str)
	{
		cartoteka1.SetEMP(i, str);
	}
	_declspec(dllexport) void InFzarp(int i, char *str)
	{
		cartoteka1.SetZarp(i, str);
	}

	//}
	//_declspec(dllexport) void OutFempl()
	//{

	//}
	//_declspec(dllexport) void OutFzarp()
	//{

	//}
	_declspec(dllexport) void Fdel(int n)
	{
		for (int i = n; i < cartoteka1.empl.size() - 1; i++)
			cartoteka1.empl[i] = cartoteka1.empl[i + 1];
		cartoteka1.empl.pop_back();
	}
	_declspec(dllexport) void FinsertEMPL(int i)
	{
		cartoteka1.empl[i];
	}
	//_declspec(dllexport) void FinsertMANAGER()
	//{

	//}

}