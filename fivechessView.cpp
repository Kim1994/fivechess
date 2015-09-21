
// fivechessView.cpp : CfivechessView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "fivechess.h"
#endif
#include "SET.h"   //���ô���
#include "mainfrm.h"  //����������
#include "fivechessDoc.h"
#include "fivechessView.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")  //�Ÿ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PVC 1
#define PVP 0
#define black 0
#define white 1
#define blank 2

// CfivechessView



IMPLEMENT_DYNCREATE(CfivechessView, CView)

BEGIN_MESSAGE_MAP(CfivechessView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_START, ButStart)
	ON_BN_CLICKED(IDC_RESTART, ButRestart)
	ON_BN_CLICKED(IDC_BACKSTEP, ButBackstep)
	ON_BN_CLICKED(IDC_SET, ButSet)
END_MESSAGE_MAP()

// CfivechessView ����/����

CfivechessView::CfivechessView()
{
	// TODO:  �ڴ˴���ӹ������
	//��ʼ����ֵ
	BSize = 14;
	BDegree = 1;
	BModel = PVP;
	Start = 0;
	first = 1;
	//���úڰ���ͼƬ
	m_Black.LoadBitmap(IDB_BLACK);
	m_White.LoadBitmap(IDB_WHITE);
}

CfivechessView::~CfivechessView()
{
}

BOOL CfivechessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CfivechessView ����

void CfivechessView::OnDraw(CDC* /*pDC*/)
{
	CfivechessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CfivechessView ��ӡ

BOOL CfivechessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CfivechessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CfivechessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CfivechessView ���

#ifdef _DEBUG
void CfivechessView::AssertValid() const
{
	CView::AssertValid();
}

void CfivechessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CfivechessDoc* CfivechessView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CfivechessDoc)));
	return (CfivechessDoc*)m_pDocument;
}
#endif //_DEBUG


// CfivechessView ��Ϣ�������


int CfivechessView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect_buttonstart(550, 90, 700, 130);   //���ư�ť��С��λ��
	B_Button[0].Create(_T("��    ʼ"), WS_CHILD | WS_VISIBLE, rect_buttonstart, this, IDC_START);


	CRect rect_buttonrestart(550, 150, 700, 190);   //���ư�ť��С��λ��
	B_Button[1].Create(_T("���¿�ʼ"), WS_CHILD | WS_VISIBLE, rect_buttonrestart, this, IDC_RESTART);


	CRect rect_buttonbackstep(550, 210, 700, 250);   //���ư�ť��С��λ��
	B_Button[2].Create(_T("��    ��"), WS_CHILD | WS_VISIBLE, rect_buttonbackstep, this, IDC_BACKSTEP);


	CRect rect_buttonset(550, 270, 700, 310);   //���ư�ť��С��λ��
	B_Button[3].Create(_T("��    ��"), WS_CHILD | WS_VISIBLE, rect_buttonset, this, IDC_SET);

	return 0;
}


void CfivechessView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int px = 0;
	int py = 0;
	if (true == Start)
	{
		if (point.x>260 - (BSize - 1) * 12 - 12 && point.x<260 + (BSize - 1) * 12 + 12 &&    //�жϵ���Ƿ���������
			point.y>260 - (BSize - 1) * 12 - 12 && point.y<260 + (BSize - 1) * 12 + 12)
		{
			px = (point.x - 248 + (BSize - 1) * 12) / 24;          //��������껻�ɶ�ά��������
			py = (point.y - 248 + (BSize - 1) * 12) / 24;
			if (blank == Board[px][py])
			{
				if (black == ChessColor)                //�º���
				{
					for (i = 0; i<BSize; i++)             //Ϊ�����¼����
					for (j = 0; j<BSize; j++)
						BackWhite[i][j] = Board[i][j];
					Board[px][py] = black;
					ChessColor = white;//������ɫ
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetResourceHandle(),
						SND_ASYNC | SND_RESOURCE);//�ڿ�ʼ���ź���������|��ʱҪ�õ�hmod����
				}
				else if (white == ChessColor)
				{
					for (i = 0; i<BSize; i++)
					for (j = 0; j<BSize; j++)
						BackBlack[i][j] = Board[i][j];
					Board[px][py] = white;
					ChessColor = black;
					PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetResourceHandle(),
						SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);

				}
			}
		}

		Drawchess();                  //������
		GoStep();
	}
	CView::OnLButtonDown(nFlags, point);
}


void CfivechessView::OnPaint()
{
	// TODO:  �ڴ˴������Ϣ����������
	CPaintDC dc(this); // device context for painting
	CDC memdc;         //cdc��
	memdc.CreateCompatibleDC(&dc);
	CBitmap bmp, *pbmpold;         //λͼ����
	bmp.LoadBitmap(IDB_BITMAP1);  //ָ��λͼ
	pbmpold = memdc.SelectObject(&bmp);    //memdc����

	SetBkMode(memdc, TRANSPARENT);         //����͸��

	CPen bi, *jbi;
	bi.CreatePen(PS_SOLID, 2, RGB(190, 150, 100)); //������ɫ����
	jbi = memdc.SelectObject(&bi);         //ѡ�񻭱�
	//���̱߿�����
	char Title[19][4] = { "1","2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19" };
	//��������
	if (0 == BSize % 2 || 1 == BSize % 2)
	{
		for (i = 0; i<BSize; i++)
		{
		//	memdc.TextOut(235 - (BSize - 1) * 12, 250 - (BSize - 1) * 12 + 24 * i, Title[i]);
			memdc.MoveTo(260 - (BSize - 1) * 12, 260 - (BSize - 1) * 12 + 24 * i);
			memdc.LineTo(260 + (BSize - 1) * 12, 260 - (BSize - 1) * 12 + 24 * i);
		}

		for (i = 0; i<BSize; i++)
		{
		//	memdc.TextOut(255 - (BSize - 1) * 12 + 24 * i, 235 - (BSize - 1) * 12,  Title[i]);
			memdc.MoveTo(260 - (BSize - 1) * 12 + 24 * i, 260 - (BSize - 1) * 12);
			memdc.LineTo(260 - (BSize - 1) * 12 + 24 * i, 260 + (BSize - 1) * 12);
		}
	}
	memdc.TextOut(550, 400, _T("�����ߣ� �𺺣�����˶"));

	dc.BitBlt(0, 0, 800, 550, &memdc, 0, 0, SRCCOPY);

	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
}
void CfivechessView::GoStep()          //���岽��
{
	//�ж����˻����˻�
    //CString str;
	//str.Format(_T("%d"), Grade(Board));
	//MessageBox(str);
	if (PVP == BModel)     //����
	{
		if (0 == Tie())  //�ж�ƽ��
		{
			MessageBox(_T("��Ȼƽ����  ����һ�ְ�"));
			ButRestart();
		}
		else if (true == WoL())  //�ж���Ӯ
			Over();
	}
	if (PVC == BModel)      //�˻�
	{
		if (0 == Tie())
		{
			MessageBox(_T("��Ȼƽ����  ����һ�ְ�"));
			ButRestart();
		}
		else
		{
			if (true == WoL())
				Over();
			if (white == ChessColor)
				computer();         //���ü�����㷨
		}
	}
}
bool CfivechessView::WoL()               //�ж���Ӯ����
{

	for (i = 0; i<BSize; i++)
	for (j = 0; j<BSize; j++)
	{
		if (CheckLine(i, j) >= 5)
			return true;                    //Ӯ�� 
	}
	return false;
}

int CfivechessView::CheckLine(int i, int j)           //������������
{
	int maxline[4] = { 1, 1, 1, 1 };
	if (black == Board[i][j] || white == Board[i][j])
	{
		for (k = 1; k<BSize - i; k++)                    //����
		if (Board[i][j] == Board[i + k][j])
			maxline[0]++;
		else break;
		for (l = 1; l<BSize - j; l++)                    //����
		if (Board[i][j] == Board[i][j + l])
			maxline[1]++;
		else break;
		for (k = 1, l = 1; k<BSize - i&&l<BSize - j; k++, l++)   //���ϡ����·���
		if (Board[i][j] == Board[i + k][j + l])
			maxline[2]++;
		else break;
		for (k = 1, l = 1; k<i&&l<BSize - j; k++, l++)         //���ϵ����·���
		if (Board[i][j] == Board[i - k][j + l])
			maxline[3]++;
		else break;
	}
	if (maxline[1]>maxline[0])  maxline[0] = maxline[1];
	if (maxline[2]>maxline[0])  maxline[0] = maxline[2];
	if (maxline[3]>maxline[0])  maxline[0] = maxline[3];
	return maxline[0];
}

void CfivechessView::Over()                    //��������
{
	if (black == ChessColor)
		MessageBox(_T("��ϲ  ����Ӯ��"));
	else if (white == ChessColor)
		MessageBox(_T("��ϲ  ����Ӯ��"));

	for (i = 0; i<BSize; i++)                   //ɾ������
		delete[] Board[i];
	delete[] Board;

	ButRestart();                           //���¿�ʼ
}



int CfivechessView::Grade(int **Board)      //Ȩֵ   �ߺߺߣ�����
{
	//������10�����    �ֱ����������Ȩֵ
	int DGrade[3][10] = { { 0, 5, 20, 5000, 10000, 2, 5, 10, 50000, 1000000 }, { 0, 5, 20, 20000, 50000, 2, 5, 10, 5000, 1000000 }, { 0, 5, 20, 20000, 50000, 2, 5, 10, 20000, 1000000 }};

	int Linenum;      //������
	int grade = 0;      //Ȩֵ��

	int Ccolor = 0;
	for (i = 0; i<BSize; i++)             //ɨ��ȫ����
	for (j = 0; j<BSize; j++)
	{
		if (white == Board[i][j] || black == Board[i][j])
		{
			if (white == Board[i][j])       //�ڰ��Ӹ�����Ȩֵ  ���ù���Ȩ��
				Ccolor = 1;
			if (black == Board[i][j])
				Ccolor = -10;


			//����
			if (i != 0 && Board[i - 1][j] == Board[i][j])      //�׳������Ѿ���������
				grade += Ccolor*DGrade[BDegree][0];
			else
			{
				Linenum = 1;
				for (k = 1; k < BSize - i; k++)
				if (Board[i][j] == Board[i + k][j])
				{
					Linenum++;
				}
				else break;
				if (5 <= Linenum)                //����������
					grade += Ccolor*DGrade[BDegree][9];
				//���߶�û��ǽ  û�жԷ��ӵ����
				if (i != 0 && blank == Board[i - 1][j] && i + Linenum != BSize&&blank == Board[i + Linenum][j])
					grade += Ccolor*DGrade[BDegree][Linenum];    //�ֱ��1��4�����Ȩֵ
				//���߶����ӻ���ǽ�����
				else
				{
					if ((i == 0 && blank != Board[i + Linenum][j]) ||
						(i + Linenum == BSize&&blank != Board[i - 1][j]))
						grade += Ccolor*DGrade[BDegree][0];
					else if (i != 0 && i + Linenum != BSize)
					if (blank != Board[i + Linenum][j] && blank != Board[i - 1][j])
					{
						grade += Ccolor*DGrade[BDegree][0];
					}
					else grade += Ccolor*DGrade[BDegree][Linenum + 4];  //�ֱ��5��8��Ȩֵ
					else grade += Ccolor*DGrade[BDegree][Linenum + 4];
				}
			}




			//����
			if (j != 0 && Board[i][j - 1] == Board[i][j])
				grade += Ccolor*DGrade[BDegree][0];
			else
			{
				Linenum = 1;
				for (l = 1; l < BSize - j; l++)
				if (Board[i][j] == Board[i][j + l])
				{
					Linenum++;
				}
				else break;
				if (5 <= Linenum)
					grade += Ccolor*DGrade[BDegree][9];
				if (j != 0 && blank == Board[i][j - 1] && j + Linenum != BSize&&blank == Board[i][j + Linenum])
					grade += Ccolor*DGrade[BDegree][Linenum];
				else
				{
					if ((j == 0 && blank != Board[i][j + Linenum]) ||
						(blank != Board[i][j - 1] && j + Linenum == BSize) ||
						((j != 0 || j + Linenum == BSize) && (blank != Board[i][j + Linenum] && blank != Board[i][j - 1])))
						grade += Ccolor*DGrade[BDegree][0];
					else grade += Ccolor*DGrade[BDegree][Linenum + 4];
				}
			}


			//��������

			if (j != 0 && i != 0 && Board[i - 1][j - 1] == Board[i][j])
				grade += Ccolor*DGrade[BDegree][0];
			else
			{
				Linenum = 1;
				for (k = 1, l = 1; k < BSize - i&&l < BSize - j; k++, l++)
				if (Board[i][j] == Board[i + k][j + l])
				{
					Linenum++;
				}
				else break;
				if (5 <= Linenum)
					grade += Ccolor*DGrade[BDegree][9];
				if (j != 0  && i != 0 && blank == Board[i - 1][j - 1] && i + Linenum != BSize&&j + Linenum != BSize && blank == Board[i + k][j + l])
					grade += Ccolor*DGrade[BDegree][Linenum];
				else
				{
					if (((j == 0 || i == 0) && (i + Linenum == BSize || j + Linenum == BSize)) ||
						((j == 0 || i == 0) && blank != Board[i + k][j + l]) ||
						((i + Linenum == BSize || j + Linenum == BSize) && blank != Board[i - 1][j - 1]))
						grade += Ccolor*DGrade[BDegree][0];
					else if (j != 0 && i != 0 && i + Linenum != BSize && j + Linenum != BSize)
					if (blank != Board[i + k][j + l] && blank != Board[i - 1][j - 1])
						grade += Ccolor*DGrade[BDegree][0];
					else grade += Ccolor*DGrade[BDegree][Linenum + 4];
					else grade += Ccolor*DGrade[BDegree][Linenum + 4];
				}
			}


			//��������

			if (j != 0 && i != BSize - 1 && Board[i + 1][j - 1] == Board[i][j])
				grade += Ccolor*DGrade[BDegree][0];
			else
			{
				Linenum = 1;
				for (k = 1, l = 1; k < i&&l < BSize - j; k++, l++)
				if (Board[i][j] == Board[i - k][j + l])
				{
					Linenum++;
				}
				else break;
				if (5 <= Linenum)
					grade += Ccolor*DGrade[BDegree][9];
				if (j != 0 && i + 1 != BSize && i - Linenum + 1 != 0 && j + Linenum != BSize&&blank == Board[i - k][j + l] && blank == Board[i + 1][j - 1])
					grade += Ccolor*DGrade[BDegree][Linenum];
				else
				{
					if (((j == 0 || i + 1 == BSize) && (i - Linenum + 1 == 0 || j + Linenum == BSize)) ||
						((j == 0 || i + 1 == BSize) && blank != Board[i - k][j + l]) ||
						((i - Linenum + 1 == 0 || j + Linenum == BSize) && blank != Board[i + 1][j - 1]))
						grade += Ccolor*DGrade[BDegree][0];
					else if (j != 0 && i + 1 != BSize && i - Linenum + 1 != 0 && j + Linenum != BSize)
					if (blank != Board[i - k][j + l] && blank != Board[i + 1][j - 1])
						grade += Ccolor*DGrade[BDegree][0];
					else grade += Ccolor*DGrade[BDegree][Linenum + 4];
					else grade += Ccolor*DGrade[BDegree][Linenum + 4];
				}
			}
		}
	}

	return grade;          //����ȫ������Ȩֵ
}

void CfivechessView::Drawchess()     //����
{
	CDC *pDC = GetDC();
	CDC Dc;
	Dc.CreateCompatibleDC(pDC);
	for (i = 0; i<BSize; i++)         //ȫ�����ػ�
	for (j = 0; j<BSize; j++)
	{
		if (black == Board[i][j])
		{
			Dc.SelectObject(m_Black);
			pDC->BitBlt(250 - (BSize - 1) * 12 + i * 24, 250 - (BSize - 1) * 12 + j * 24, 20, 20, &Dc, 0, 0, SRCCOPY);
		}
		if (white == Board[i][j])
		{
			Dc.SelectObject(m_White);
			pDC->BitBlt(250 - (BSize - 1) * 12 + i * 24, 250 - (BSize - 1) * 12 + j * 24, 20, 20, &Dc, 0, 0, SRCCOPY);
		}
	}
}



int CfivechessView::Tie()        //�ж�ƽ��
{
	for (i = 0; i<BSize; i++)
	for (j = 0; j<BSize; j++)
	if (blank == Board[i][j])
		return 1;         //��ƽ��
	return 0;          //ƽ��
}



void CfivechessView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	str.Format(_T("x=%d y=%d "), point.x, point.y);
	((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(str);
	CView::OnMouseMove(nFlags, point);
}
void CfivechessView::ButStart()
{	//�ж��Ƿ��Ѿ�����  ��ʼ������  ��������
	if (true == Start)
		MessageBox(_T("������Ϸ  ���¿����������¿�ʼ"));
	if (false == Start)
	{
		Start = true;
		ChessColor = black;     //��������
		Board = new int*[BSize];
		for (i = 0; i<BSize; i++)
			Board[i] = new int[BSize];
		for (i = 0; i<BSize; i++)
		for (j = 0; j<BSize; j++)
			Board[i][j] = 2;
		if (first==0)
		    Board[7][7] = white;
		

		BackBlack = new int*[BSize];
		for (i = 0; i<BSize; i++)
			BackBlack[i] = new int[BSize];
		for (i = 0; i<BSize; i++)
		for (j = 0; j<BSize; j++)
			BackBlack[i][j] = 2;

		BackWhite = new int*[BSize];
		for (i = 0; i<BSize; i++)
			BackWhite[i] = new int[BSize];
		for (i = 0; i<BSize; i++)
		for (j = 0; j<BSize; j++)
			BackWhite[i][j] = 2;
	}
	Drawchess();                  //������
}
void CfivechessView::ButRestart()
{
	RedrawWindow();     //�ػ洰��
	Start = false;
	ButStart();         //���¿�ʼ
}
void CfivechessView::ButBackstep()
{
	RedrawWindow();     //�ػ洰��
	//���û�������
	if (white == ChessColor)
	{
		for (i = 0; i<BSize; i++)
		for (j = 0; j<BSize; j++)
			Board[i][j] = BackBlack[i][j];
	}
	if (black == ChessColor)
	{
		for (i = 0; i<BSize; i++)
		for (j = 0; j<BSize; j++)
			Board[i][j] = BackWhite[i][j];
	}
	Drawchess();    //�ػ�����
}
void CfivechessView::ButSet()
{
	CSET setlist;     //���ڶ���
	setlist.DoModal();    //���ô���
	//��ȡ����
	BDegree = setlist.m_degree;
	BModel = setlist.m_model;
	BSize = setlist.m_boardsize;
	first = setlist.m_first;
	ButRestart();

}

void CfivechessView::InitTree(tree *t)
{
	int i, j;
	*t = (tree)malloc(sizeof(prechess));
	(*t)->p = NULL;
	(*t)->child = NULL;
	(*t)->right = NULL;
	(*t)->preboard = new int*[BSize];
	for (i = 0; i < BSize; i++)
		(*t)->preboard[i] = new int[BSize];
	for (i = 0; i < BSize; i++)
	for (j = 0; j < BSize; j++)
		(*t)->preboard[i][j] = Board[i][j];
	(*t)->pregrade = Grade((*t)->preboard);
}

void CfivechessView::CreatSon(tree *t)
{
	int i, j;
	tree next;
	next = (tree)malloc(sizeof(prechess));
	next->right = NULL;
    for (i = 0; i < BSize;i++)
	for (j = 0; j < BSize;j++)
	{
		int value[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
		if (i == 0){ value[0] = 0; value[1] = 0; value[2] = 0; }
		if (j == 0){ value[0] = 0; value[3] = 0; value[5] = 0; }
		if (i == BSize - 1){ value[5] = 0; value[6] = 0; value[7] = 0; }
		if (j == BSize - 1){ value[2] = 0; value[4] = 0; value[7] = 0; }
		if (value[0] == 2)if (Board[i - 1][j - 1] != blank){ value[0] = 1; }
		if (value[1] == 2)if (Board[i - 1][j] != blank){ value[1] = 1; }
		if (value[2] == 2)if (Board[i - 1][j + 1] != blank){ value[2] = 1; }
		if (value[3] == 2)if (Board[i][j - 1] != blank){ value[3] = 1; }
		if (value[4] == 2)if (Board[i][j + 1] != blank){ value[4] = 1; }
		if (value[5] == 2)if (Board[i + 1][j - 1] != blank){ value[5] = 1; }
		if (value[6] == 2)if (Board[i + 1][j] != blank){ value[6] = 1; }
		if (value[7] == 2)if (Board[i + 1][j + 1] != blank){ value[7] = 1; }
		if (Board[i][j] == blank)
		if (value[0] == 1 || value[1] == 1 || value[2] == 1 || value[3] == 1 || value[4] == 1 || value[5] == 1 || value[6] == 1 || value[7] == 1)
		{
			tree son = (tree)malloc(sizeof(prechess));
        	son->p = *t;
			son->child = NULL;
			son->preboard = new int*[BSize];
			for (k = 0; k < BSize; k++)
				son->preboard[k] = new int[BSize];
			for (k = 0; k < BSize; k++)
			for (l = 0; l < BSize; l++)
			son->preboard[k][l] = (*t)->preboard[k][l];
			son->preboard[i][j] = comcolor;
			son->pregrade = Grade(son->preboard) + (*t)->pregrade;

			son->right = next->right;
			next->right = son;
			(*t)->child = son;

		}
	}
	free(next);
}
void CfivechessView::disteoytree(tree *t)
{
	int i;
	tree del1,del2,delp;
	del1 = *t;
	while (del1->child != NULL)
	{
		del1 = del1->child;
	}
	delp = del1->p;
	while (delp->p != NULL)
	{	
		while (delp->right!=NULL)
		{
			while (del1 != NULL)
			{
				del2 = del1->right;
				for (i = 0; i < BSize; i++)
					delete[] del1->preboard[i];
				delete[] del1->preboard;
				free(del1);
				del1 = NULL;
				del1 = del2;
			}
			delp = delp->right;
			del1 = delp->child;
		}
		while (del1 != NULL)
		{
			del2 = del1->right;
			for (i = 0; i < BSize; i++)
				delete[] del1->preboard[i];
			delete[] del1->preboard;
			free(del1);
			del1 = NULL;
			del1 = del2;
		}
		delp = delp->p;
		del1 = delp->child;
	}
	del1 = delp->child;
	while (del1 != NULL)
	{
		del2 = del1->right;
		for (i = 0; i < BSize; i++)
			delete[] del1->preboard[i];
		delete[] del1->preboard;
		free(del1);
		del1 = NULL;
		del1 = del2;
	}
}
void CfivechessView::cuttree(tree *t)
{
	int maxgrade[500],i=0,a,b=0;
	tree cut,change;
	cut = *t;
	while (cut->right != NULL)
	{
		maxgrade[i] = cut->pregrade;
		i++;
		cut = cut->right;
		b++;
	}maxgrade[i] = cut->pregrade;
	cut = *t;
	if (comcolor == white)
	{
		for (i = 0; i < b+1; i++)
		for (j = i; j < b+1; j++)
		{
			if (maxgrade[j]>maxgrade[i])
			{
				a = maxgrade[j];
				maxgrade[j] = maxgrade[i];
				maxgrade[i] = a;
			}
		}
		while (cut->right!=NULL)
		{
			
			if (cut->p->child==cut)
			{
				while (cut->pregrade < maxgrade[4])
				{
					cut->p->child = cut->right;
					change = cut->right;
					for (i = 0; i < BSize; i++)
						free(cut->preboard[i]);
					free(cut);
					cut = change;
				}
				
			}
			else while (cut->right->pregrade < maxgrade[4])
			{
				if (cut->right->right == NULL)
				{
					for (i = 0; i < BSize; i++)
						free(cut->right->preboard[i]);
					free(cut->right);
					cut->right = NULL;
					break;
				}
				else
				{
					change = cut->right->right;
					for (i = 0; i < BSize; i++)
						free(cut->right->preboard[i]);

					free(cut->right);
					cut->right = change;
				}
			}
			if (cut->right != NULL)
				cut = cut->right;
		}
	}
	if (comcolor == black)
	{
		for (i = 0; i < b + 1; i++)
		for (j = i; j < b + 1; j++)
		{
			if (maxgrade[j]<maxgrade[i])
			{
				a = maxgrade[j];
				maxgrade[j] = maxgrade[i];
				maxgrade[i] = a;
			}
		}
		while (cut->right != NULL)
		{

			if (cut->p->child == cut)
			{
				while (cut->pregrade > maxgrade[0])
				{
					cut->p->child = cut->right;
					change = cut->right;
					for (i = 0; i < BSize; i++)
						free(cut->preboard[i]);
					free(cut);
					cut = change;
				}

			}
			else while (cut->right->pregrade > maxgrade[4])
			{
				if (cut->right->right == NULL)
				{
					for (i = 0; i < BSize; i++)
						free(cut->right->preboard[i]);
					free(cut->right);
					cut->right = NULL;
					break;
				}
				else
				{
					change = cut->right->right;
					for (i = 0; i < BSize; i++)
						free(cut->right->preboard[i]);

					free(cut->right);
					cut->right = change;
				}
			}
			if (cut->right != NULL)
				cut = cut->right;
		}
	}
	*t = cut->p->child;
}

void CfivechessView::computer()                //�����㷨
{
	int i,j,Maxgrade = -2000000000,degree=BDegree,x=-1,y=-1;                  //��ʼ��Ȩֵ
	tree root = NULL, T = NULL, T1 = NULL, T2 = NULL, T3 = NULL, T4 = NULL, max = NULL,spe=NULL;
	if(degree==0)
	{
		comcolor = white;
		InitTree(&root);
		CreatSon(&root);
		T = root->child;
		cuttree(&T);
		max = T;
		while(T != NULL)
		{
			if (max->pregrade < T->pregrade)
				max = T;
			T = T->right;
		}
		for (i = 0; i < BSize; i++)
		for (j = 0; j < BSize; j++)
		if (Board[i][j] != max->preboard[i][j])
		{
			x = i; y = j;
		}
	}
	
	if (degree == 1)
	{
		comcolor = white;
		InitTree(&root);
		CreatSon(&root);
		T = root->child;
		cuttree(&T);
		while (T != NULL)
		{
			comcolor = black;
			CreatSon(&T);
			T1 = T->child;
			cuttree(&T1);
			while (T1 != NULL)
			{
				comcolor = white;
				CreatSon(&T1);
				T2 = T1->child;
				cuttree(&T2);
				T1 = T1->right;
			}
			T = T->right;
		}
		T = root->child;
		T1 = T->child;
		T2 = T1->child;
		max = T2;
		while (T != NULL)
		{
			T1 = T->child;
			while (T1 != NULL)
			{
				T2 = T1->child;
				while (T2 != NULL)
				{
					if (max->pregrade < T2->pregrade)
						max = T2;
					T2 = T2->right;
				}
				if (T->pregrade - T1->pregrade > 450000)
				{
					spe = T1;
					max->pregrade = T->pregrade + 1000000;
				}
				T1 = T1->right;
			}
			T = T->right;
		}
		if (spe != NULL)
		{
			for (i = 0; i < BSize; i++)
			for (j = 0; j < BSize; j++)
			if (Board[i][j] != spe->preboard[i][j])
			{
				x = i; y = j;
			}
		}
		else
		{
			for (i = 0; i < BSize; i++)
			for (j = 0; j < BSize; j++)
			if (Board[i][j] != max->p->p->preboard[i][j])
			{
				x = i; y = j;
			}
		}
	}
	if (degree == 2)
	{
		comcolor = white;
		InitTree(&root);
		CreatSon(&root);
		T = root->child;
		cuttree(&T);
		T = root->child;
		while (T != NULL)
		{
			comcolor = black;
			CreatSon(&T);
			T1 = T->child;
			cuttree(&T1);
			while (T1 != NULL)
			{
				comcolor = white;
				CreatSon(&T1);
				T2 = T1->child;
				cuttree(&T2);
				while (T2 != NULL)
				{
					comcolor = black;
					CreatSon(&T2);
					T3 = T2->child;
					cuttree(&T3);				
					while (T3 != NULL)
					{
						comcolor = white;
						CreatSon(&T3);
						T4 = T3->child;
						cuttree(&T4);
						T3 = T3->right;
					}T2 = T2->right;
				}T1 = T1->right;
			}T = T->right;
		}
		T = root->child;
		T1 = T->child;
		T2 = T1->child;
		T3 = T2->child;
		T4 = T3->child;
		max = T4;
		while (T != NULL)
		{
			T1 = T->child;
			while (T1 != NULL)
			{
				T2 = T1->child;
				while (T2 != NULL)
				{
					T3 = T2->child;
					while (T3 != NULL)
					{
						T4 = T3->child;
						while (T4 != NULL)
						{
							if (max->pregrade < T4->pregrade)
								max = T4;
							T4 = T4->right;
						}
						T3 = T3->right;
					}
					T2 = T2->right;
				}
				if (T->pregrade - T1->pregrade > 500000)
				{
					spe = T1;
					max->pregrade = T->pregrade + 2000000;
				}
				T1 = T1->right;
			}
			T = T->right;
		}
		if (spe != NULL)
		{
			for (i = 0; i < BSize; i++)
			for (j = 0; j < BSize; j++)
			if (Board[i][j] != spe->preboard[i][j])
			{
				x = i; y = j;
			}
		}
		else
		{
			for (i = 0; i < BSize; i++)
			for (j = 0; j < BSize; j++)
			if (Board[i][j] != max->p->p->p->p->preboard[i][j])
			{
				x = i; y = j;
			}
		}
	}
	disteoytree(&root);
	for (i = 0; i < BSize; i++)
		delete[] root->preboard[i];
	delete[] root->preboard;
	free(root);
	CPoint Mpoint(260 - (BSize - 1) * 12 + 24 * x, 260 - (BSize - 1) * 12 + 24 * y);    //����Ҫ�µ�����
	OnLButtonDown(MK_LBUTTON, Mpoint);
}