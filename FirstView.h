// FirstView.h : CFirstView 类的接口
//

#pragma once


class CFirstView : public CView
{
protected: // 仅从序列化创建
	CFirstView();
	DECLARE_DYNCREATE(CFirstView)

// 特性
public:
	CFirstDoc* GetDocument() const;

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
	virtual ~CFirstView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int m_nCurColor;
	int DrawCircle(int CurColor, CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnStop();
};

#ifndef _DEBUG  // FirstView.cpp 中的调试版本
inline CFirstDoc* CFirstView::GetDocument() const
   { return reinterpret_cast<CFirstDoc*>(m_pDocument); }
#endif
