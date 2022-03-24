#pragma once
//class Dialog;
class employee :public CObject
{
public:
	DECLARE_SERIAL(employee)
	employee();
	virtual ~employee();
	CString age1;
	CString name1;
	CString surname1;
	CString position1;
	/*void input();
	void output();*/
	void Serialize(CArchive& Archive);
	void Result(CDC*, CSize &t);
	void Size(/*CDC * dc,*/ CSize &);
	CSize sm;
	virtual CString result();
	/*virtual void Prov(Dialog *);
	virtual void Prov2(Dialog *);*/

};

