
// fivechess.h : fivechess Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CfivechessApp:
// �йش����ʵ�֣������ fivechess.cpp
//

class CfivechessApp : public CWinApp
{
public:
	CfivechessApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CfivechessApp theApp;
