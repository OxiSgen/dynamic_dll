// Gladkov5_DLL.h: основной файл заголовка для библиотеки DLL Gladkov5_DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CGladkov5DLLApp
// Реализацию этого класса см. в файле Gladkov5_DLL.cpp
//

class CGladkov5DLLApp : public CWinApp
{
public:
	CGladkov5DLLApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
