#pragma once


// CSET 对话框

class CSET : public CDialog
{
	DECLARE_DYNAMIC(CSET)

public:
	CSET(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSET();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };
	int	    m_model;
	int		m_degree;
	int		m_boardsize;
    int     m_first;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	
};
