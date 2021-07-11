#pragma once
#ifndef _Point_ITEM___
#define _Point_ITEM___

#include <Windows.h>

struct MyPoint
{
	int x;
	int y;
};
class CPointItem
{
public:
	CPointItem(void);
	~CPointItem(void);


void SetPoint(MyPoint point);  //���ô�ItemPoint������
MyPoint GetPoint() const;		//��ȡ ����;

void SetIndex(int nIndex);	//���ô�ItemPoint�����;
int GetIndex() const;

void SetNext(CPointItem *pnext);
CPointItem* GetNext(void) const;
void SetPointValue(int nvalue);
int GetPointValue();


bool			m_link_to_next;//��������һ����;

protected:
	MyPoint			m_point;
	int				m_index;
	CPointItem		*m_pNextItem;
	int				m_value;

};

#endif

