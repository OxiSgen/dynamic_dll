#include "stdafx.h"
#include "cartoteka.h"
#include "employee.h"
#include "manager.h"

using namespace std::placeholders;

cartoteka::cartoteka()
{
}


cartoteka::~cartoteka()
{
	empl.clear();
}

void cartoteka::ochistka()
{
	empl.clear();
}


CSize cartoteka::Size(/*CDC* PDC*/)
{
	CSize r;
	/*auto b = bind(&employee::Size, _1, ref(r);*/
	for_each(empl.begin(), empl.end(), bind(&employee::Size, _1, ref(r)));  //  _1 
	return r;
}

//void cartoteka::fout(CArchive &ar)
//{
//	ar << empl.size();
//	for_each(empl.begin(), empl.end(), [&](shared_ptr<employee> empll) {ar << empll.get(); });
//}
//
//void cartoteka::fin(CArchive &ar)
//{
//	int n;
//	employee *v;
//	ar >> n;
//	for (int i = 0; i < n; i++)
//	{
//		ar >> v;
//		shared_ptr<employee> x(v);
//		empl.push_back(x);
//	}
//}
void cartoteka::fout() // çô
{
	CFile file("Base.dat", CFile::modeCreate | CFile::modeWrite);
	CArchive Archive(&file, CArchive::store);
	Archive << empl.size();
	for (auto& v : empl)
	{
		Archive << v.get();
	}
}

void cartoteka::fin() //âââ
{
	CFile file("Base.dat", CFile::modeRead);
	CArchive Archive(&file, CArchive::load);
	int n;
	Archive >> n;
	for (int i = 0; i < n; i++)
	{
		employee* x;
		Archive >> x;
		shared_ptr<employee> v(x);
		empl.push_back(v);
	}
}

void cartoteka::output(CDC* PDC)
{
	CSize s(0, 0);
	for_each(empl.begin(), empl.end(), bind(&employee::Result, _1, PDC, ref(s)));
}


