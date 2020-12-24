
// MiniDrawView.h: интерфейс класса CMiniDrawView
//

#pragma once


class CMiniDrawView : public CView
{
protected:
	CString m_ClassName;
	int m_Dragging;
	HCURSOR m_HCross; // Дескриптор указателя мыши
	CPoint m_PointOld;
	CPoint m_PointOrigin;

	CMiniDrawView() noexcept;
	DECLARE_DYNCREATE(CMiniDrawView)

// Атрибуты
public:
	CMiniDrawDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CMiniDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в MiniDrawView.cpp
inline CMiniDrawDoc* CMiniDrawView::GetDocument() const
   { return reinterpret_cast<CMiniDrawDoc*>(m_pDocument); }
#endif

