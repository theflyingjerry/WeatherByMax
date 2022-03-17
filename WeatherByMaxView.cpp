
// WeatherByMaxView.cpp : implementation of the CWeatherByMaxView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "WeatherByMax.h"
#endif

#include "WeatherByMaxDoc.h"
#include "WeatherByMaxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeatherByMaxView

IMPLEMENT_DYNCREATE(CWeatherByMaxView, CView)

BEGIN_MESSAGE_MAP(CWeatherByMaxView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWeatherByMaxView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CWeatherByMaxView construction/destruction

CWeatherByMaxView::CWeatherByMaxView() noexcept
{
	// TODO: add construction code here

}

CWeatherByMaxView::~CWeatherByMaxView()
{
}

BOOL CWeatherByMaxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CWeatherByMaxView drawing

void CWeatherByMaxView::OnDraw(CDC* pDC)
{
	CWeatherByMaxDoc* pDoc = GetDocument(); //gets data from doc 
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// array of strings for less redundant code
	const char *Days[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	
	//NEED: Better formatting in view 
		//Move temps further left
		//Make sure the title is different if 
	
	//Output title
	pDC->TextOutW(100, 100, (_T("This Weeks Weather in ")+ pDoc->LocationGetter()+_T("!")));
	int j = 0;
	CString D;
	//output data
	for (int i = 0; i < pDoc->LengthGetter(); i++) {
		CString C = CString(Days[i]);
		pDC->TextOutW(50, (150 + (50 * j)), C);
		if (pDoc->dataRead) {
			D.Format(_T("%d / %d"), pDoc->TempHGetter(i),pDoc->TempLGetter(i));
			pDC->TextOutW(150, (150 + (50 * j)), D);
		}
		j++;
	}
}


// CWeatherByMaxView printing


void CWeatherByMaxView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWeatherByMaxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWeatherByMaxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWeatherByMaxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CWeatherByMaxView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWeatherByMaxView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWeatherByMaxView diagnostics

#ifdef _DEBUG
void CWeatherByMaxView::AssertValid() const
{
	CView::AssertValid();
}

void CWeatherByMaxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWeatherByMaxDoc* CWeatherByMaxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWeatherByMaxDoc)));
	return (CWeatherByMaxDoc*)m_pDocument;
}
#endif //_DEBUG


// CWeatherByMaxView message handlers
