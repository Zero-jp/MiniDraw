
// MiniDrawView.cpp: реализация класса CMiniDrawView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MiniDraw.h"
#endif

#include "MiniDrawDoc.h"
#include "MiniDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniDrawView

IMPLEMENT_DYNCREATE(CMiniDrawView, CView)

BEGIN_MESSAGE_MAP(CMiniDrawView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CMiniDrawView

CMiniDrawView::CMiniDrawView() noexcept
{
	// TODO: добавьте код создания
	m_Dragging = 0;
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}

CMiniDrawView::~CMiniDrawView()
{
}

BOOL CMiniDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	m_ClassName = AfxRegisterWndClass
	(CS_HREDRAW | CS_VREDRAW,                // стили окна
		0,                                      // без курсора
		(HBRUSH)::GetStockObject(WHITE_BRUSH), // белый фон 
		0);                                     // без значка
	cs.lpszClass = m_ClassName;

	return CView::PreCreateWindow(cs);
}

// Рисование CMiniDrawView

void CMiniDrawView::OnDraw(CDC* /*pDC*/)
{
	CMiniDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Диагностика CMiniDrawView

#ifdef _DEBUG
void CMiniDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMiniDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMiniDrawDoc* CMiniDrawView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMiniDrawDoc)));
	return (CMiniDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMiniDrawView


void CMiniDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	m_PointOrigin = point; 	// Начало линии
	m_PointOld = point; 		// Используют другие обработчики
	SetCapture(); 				// "Захват" сообщений от мыши окном
	m_Dragging = 1; 			// Идет рисование

	RECT Rect;
	GetClientRect(&Rect); 	// Координаты окна представления
	ClientToScreen(&Rect);	// Преобразуем в экранные 
									// (от верхнего левого угла)
	::ClipCursor(&Rect);		// Огр.перемещ.курс.пределами окна

	CView::OnLButtonDown(nFlags, point);
}


void CMiniDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	::SetCursor(m_HCross); // Установка типа курсора
	if (m_Dragging)
	{
		CClientDC ClientDC(this);
		ClientDC.SetROP2(R2_NOT);
		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(m_PointOld); 	// Стирание линии
		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(point); 	// Рисование новой линии
		m_PointOld = point;
	}

	CView::OnMouseMove(nFlags, point);
}


void CMiniDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (m_Dragging)
	{
		m_Dragging = 0;
		::ReleaseCapture(); // Отменить захват сообщений мыши
		::ClipCursor(NULL); // Курсор двигается по всему экрану
		CClientDC ClientDC(this);
		ClientDC.SetROP2(R2_NOT);
		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(m_PointOld);
		ClientDC.SetROP2(R2_COPYPEN);
		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.LineTo(point);
	}

	CView::OnLButtonUp(nFlags, point);
}
