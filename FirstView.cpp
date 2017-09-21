// FirstView.cpp : CFirstView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "First.h"
#endif

#include "FirstDoc.h"
#include "FirstView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFirstView

IMPLEMENT_DYNCREATE(CFirstView, CView)

BEGIN_MESSAGE_MAP(CFirstView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFirstView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_START, &CFirstView::OnStart)
	ON_COMMAND(ID_STOP, &CFirstView::OnStop)
END_MESSAGE_MAP()

// CFirstView 构造/析构

CFirstView::CFirstView()
	: m_nCurColor(0)
{
	// TODO: 在此处添加构造代码

}

CFirstView::~CFirstView()
{
}

BOOL CFirstView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFirstView 绘制

void CFirstView::OnDraw(CDC* pDC/*pDC*/)
{
	CFirstDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DrawCircle(m_nCurColor,pDC);
	// TODO: 在此处为本机数据添加绘制代码
}


// CFirstView 打印


void CFirstView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFirstView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFirstView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFirstView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CFirstView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFirstView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFirstView 诊断

#ifdef _DEBUG
void CFirstView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstDoc* CFirstView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstDoc)));
	return (CFirstDoc*)m_pDocument;
}
#endif //_DEBUG


// CFirstView 消息处理程序


int CFirstView::DrawCircle(int CurColor, CDC* pDC)
{
	pDC->Rectangle(80,80,220,440);
	CRect rRect(100,100,200,200);
	CRect gRect(100,210,200,310);
	CRect yRect(100,320,200,420);
	CBrush rBrush(RGB(255,0,0));
	CBrush gBrush(RGB(0,255,0));
	CBrush yBrush(RGB(255,255,0));
	CBrush wBrush(RGB(255,255,255));
	CBrush *pOldBrush;
	if(CurColor==0)//红灯亮
	{
		pDC->Ellipse(&gRect);
		pDC->Ellipse(&yRect);
		pOldBrush=pDC->SelectObject(&rBrush);
		pDC->Ellipse(&rRect);
	}
	else if(CurColor==1)//绿灯亮
	{
		pDC->Ellipse(&rRect);
		pDC->Ellipse(&yRect);
		pOldBrush=pDC->SelectObject(&gBrush);
		pDC->Ellipse(&gRect);
	}
	else if(CurColor==2)//黄灯亮
	{
		pDC->Ellipse(&gRect);
		pDC->Ellipse(&rRect);
		pOldBrush=pDC->SelectObject(&yBrush);
		pDC->Ellipse(&yRect);
	}
	else
	{
		pOldBrush=pDC->SelectObject(&wBrush);
		pDC->Ellipse(&gRect);
		pDC->Ellipse(&rRect);
		pDC->Ellipse(&yRect);
	}
	pDC->SelectObject(pOldBrush);
	return 0;
}



void CFirstView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_nCurColor=(++m_nCurColor)%3;
	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CFirstView::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1,1000,NULL);
}


void CFirstView::OnStop()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
	m_nCurColor=-1;
	Invalidate();
}
