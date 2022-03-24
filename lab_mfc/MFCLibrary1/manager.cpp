#include "stdafx.h"
#include "manager.h"


IMPLEMENT_SERIAL(manager, employee, 1 | VERSIONABLE_SCHEMA)

manager::manager()
{
}


manager::~manager()
{
}

//void manager::Prov(Dialog * dlg)
//{
//	dlg->name = this->name1;
//	dlg->surname = this->surname1;
//	dlg->age = this->age1;
//	dlg->position = this->position1;
//	dlg->emp_num = this->emp_inC;
//	dlg->zarplata = this->zarp;
//	dlg->edit_emp_num.ShowWindow(true);
//	dlg->edit_zarplata.ShowWindow(true);
//	dlg->UpdateData(false);
//}
//
//
//void manager::Prov2(Dialog * dlg)
//{
//	dlg->UpdateData();
//	this->name1 = dlg->name;
//	this->surname1 = dlg->surname;
//	this->age1 = dlg->age;
//	this->position1 = dlg->position;
//	dlg->edit_emp_num.ShowWindow(true);
//	dlg->edit_zarplata.ShowWindow(true);
//	this->emp_inC = dlg->emp_num;
//	this->zarp = dlg->zarplata;
//}

void manager::Serialize(CArchive& Archive)
{
	if (Archive.IsStoring())
	{
		Archive << name1;
		Archive << surname1;
		Archive << age1;
		Archive << position1;
		Archive << emp_inC;
		Archive << zarp;
	}
	else
	{
		Archive >> name1;
		Archive >> surname1;
		Archive >> age1;
		Archive >> position1;
		Archive >> emp_inC;
		Archive >> zarp;
	}
}

CString manager::result()
{
	/*CString num;
	CString Age;
	CString emp;
	Age.Format("%i", age1);
	num.Format("%i", zarp);
	emp.Format("%i", emp_inC);*/
	CString s = name1 + " " + surname1 + " " + position1 + " " + age1 + " " + zarp + /*L*/" " + emp_inC;
	return s;

}

void manager::printRes(CDC * DC, int& y)
{
	DC->TextOut(4, y, result());
	y += 20;
}
