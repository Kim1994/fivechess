// SET.cpp : 实现文件
//

#include "stdafx.h"
#include "fivechess.h"
#include "SET.h"
#include "afxdialogex.h"


// CSET 对话框

IMPLEMENT_DYNAMIC(CSET, CDialog)

CSET::CSET(CWnd* pParent /*=NULL*/)
	: CDialog(CSET::IDD, pParent)
	, m_first(0)
{
	m_model = 1;
	m_degree = 1;
	m_boardsize = 14;
	m_first = 1;
}

CSET::~CSET()
{
}

void CSET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_PVP, m_model);
	DDX_Radio(pDX, IDC_DEGREE1, m_degree);
	DDX_Text(pDX, IDC_SIZENUM, m_boardsize);
	DDX_Radio(pDX, IDC_RADIO1, m_first);
	DDV_MinMaxInt(pDX, m_first, 0, 1);
}


BEGIN_MESSAGE_MAP(CSET, CDialog)
END_MESSAGE_MAP()


// CSET 消息处理程序


void CSET::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CWnd::UpdateData(TRUE);
	if (m_boardsize>19)
	{
		MessageBox(_T("棋盘最大为19*19"));
		m_boardsize = 19;
	}
	if (m_boardsize<9)
	{
		MessageBox(_T("棋盘最小为9*9"));
		m_boardsize = 9;
	}
	CWnd::UpdateData(FALSE);
	CDialog::OnOK();
}
