
// fivechessView.h : CfivechessView 类的接口
//

#pragma once

class CfivechessView : public CView
{
protected: // 仅从序列化创建
	CfivechessView();
	DECLARE_DYNCREATE(CfivechessView)

// 特性
public:
	CfivechessDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:

	int Tie();
	void Drawchess();
	int Grade(int **Board);
	void computer();
	void Over();
	int CheckLine(int, int);
	bool WoL();
	void GoStep();
	int BSize;
	int i, j, k, l;
	int comcolor;
	int first;



	//树
	typedef struct prechess
	{
		int **preboard;
		int pregrade;
		struct prechess *p;
		struct prechess *child;
		struct prechess *right;
	} prechess;
	typedef struct prechess *tree;
	void InitTree(tree *t);
	void CreatSon(tree *t);
	void disteoytree(tree *t);
	void cuttree(tree *t);




	virtual ~CfivechessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

private:
	int **BackBlack;
	int **BackWhite;

	CBitmap m_White;
	CBitmap m_Black;
	bool ChessColor;
	int **Board;
	bool Start;
	CButton B_Button[4];
	int BModel;
	int BDegree;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void ButStart();
	afx_msg void ButRestart();
	afx_msg void ButBackstep();
	afx_msg void ButSet();
};

#ifndef _DEBUG  // fivechessView.cpp 中的调试版本
inline CfivechessDoc* CfivechessView::GetDocument() const
   { return reinterpret_cast<CfivechessDoc*>(m_pDocument); }
#endif

