#include "stdafx.h"
#include "employee.h"

IMPLEMENT_SERIAL(employee, CObject, 1 | VERSIONABLE_SCHEMA)

employee::employee()
{
}


employee::~employee()
{
}


void employee::Serialize(CArchive& Archive)
{
	if (Archive.IsStoring())
	{
		Archive << name1;
		Archive << surname1;
		Archive << age1;
		Archive << position1;
	}
	else
	{
		Archive >> name1;
		Archive >> surname1;
		Archive >> age1;
		Archive >> position1;
	}
}

//void Employee::Prov(LR4Dialog * dlg)
//{
//	dlg->name = this->E_Name;
//	dlg->age = this->E_Age;
//	dlg->Edit_deptNum.ShowWindow(false);
//}
//
//void Employee::Prov2(LR4Dialog * dlg)
//{
//	this->E_Name = dlg->Name;
//	this->E_Age = dlg->Age;
//	dlg->Edit_deptNum.ShowWindow(false);
//	dlg->check_man.EnableWindow(false);
//}

//void employee::Prov(Dialog * dlg)
//{
//	dlg->name = this->name1;
//	dlg->surname = this->surname1;
//	dlg->age = this->age1;
//	dlg->position = this->position1;
//	dlg->edit_emp_num.ShowWindow(false);
//	dlg->edit_zarplata.ShowWindow(false);
//	dlg->UpdateData(false);
//}
//
//
//void employee::Prov2(Dialog * dlg)
//{
//	this->name1 = dlg->name;
//	this->surname1 = dlg->surname;
//	this->age1 = dlg->age;
//	this->position1 = dlg->position;
//	dlg->edit_emp_num.ShowWindow(false);
//	dlg->edit_zarplata.ShowWindow(false);
//	dlg->UpdateData();
//}


CString employee::result()
{
	//CString Age;
	//Age.Format(L"%i", age1);
	CString s = name1 + " " + surname1 + " " + position1 + " " + age1;
	return s;

}

void employee::Result(CDC* DC, CSize& size)
{
	DC->TextOut(0, size.cy, result());//координаты места записи
	sm = DC->GetTextExtent(result());
	size.cy += sm.cy;
}

void employee::Size(/*CDC * dc, */CSize& size)
{

	//вызываем эту функцию чтобы рассчитать ширину и высоту текста 
	size.cx = max(size.cx, sm.cx);
	size.cy += sm.cy;
}
