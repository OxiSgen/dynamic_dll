#pragma once
#include "employee.h"
//class Dialog;
class manager : public employee
{
public:
	DECLARE_SERIAL(manager)
	manager();
	~manager();
	CString emp_inC;
	CString zarp;
	/*virtual void input();
	virtual void output();*/
	void Serialize(CArchive& ar);
	void printRes(CDC * dc, int& y);
	CString result();
	
	//virtual void Prov(Dialog *);
	//virtual void Prov2(Dialog *);
};
