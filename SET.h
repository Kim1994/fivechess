#pragma once


// CSET �Ի���

class CSET : public CDialog
{
	DECLARE_DYNAMIC(CSET)

public:
	CSET(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSET();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };
	int	    m_model;
	int		m_degree;
	int		m_boardsize;
    int     m_first;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	
};
