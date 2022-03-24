#pragma once

#include <vector>
#include "employee.h"
#include "manager.h"

using namespace std;
class cartoteka
{
public:
	int n;
	vector<shared_ptr<employee>> empl;
	cartoteka();
	virtual ~cartoteka();
	/*void addEmployee(shared_ptr<employee> e);
	void addManager();*/
	void output(CDC*dc);
	void fout();
	void fin();
	void ochistka();
	CSize Size(/*CDC*pdc*/);

	char *GetName(int g)
	{
		return empl[g]->name1.GetBuffer();
	}
	char *GetSurName(int g)
	{
		return empl[g]->surname1.GetBuffer();
	}
	char *GetAge(int g)
	{
		return empl[g]->age1.GetBuffer();
	}
	char *GetPosition(int g)
	{
		return empl[g]->position1.GetBuffer();
	}
	char *GetEMP(int g)
	{
		return static_pointer_cast<manager>(empl[g])->emp_inC.GetBuffer();
	}
	char *GetZarp(int g)
	{
		return static_pointer_cast<manager>(empl[g])->zarp.GetBuffer();
	}

	void SetName(int n, char *str)
	{
		empl[n]->name1 = CString(str);
	}
	void SetSurname(int n, char *str)
	{
		empl[n]->surname1 = CString(str);
	}
	void Setage(int n, char *str)
	{
		empl[n]->age1 = CString(str);
	}
	void SetPosition(int n, char *str)
	{
		empl[n]->position1 = CString(str);
	}
	void SetEMP(int n, char *str)
	{
		static_pointer_cast<manager>(empl[n])->emp_inC = CString(str);
	}
	void SetZarp(int n, char *str)
	{
		static_pointer_cast<manager>(empl[n])->zarp = CString(str);
	}
};