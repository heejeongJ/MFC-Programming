
// Practices6-1View.cpp: CPractices61View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practices6-1.h"
#endif

#include "Practices6-1Doc.h"
#include "Practices6-1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractices61View

IMPLEMENT_DYNCREATE(CPractices61View, CView)

BEGIN_MESSAGE_MAP(CPractices61View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractices61View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CPractices61View::OnLine)
	ON_COMMAND(ID_ELLIPSE, &CPractices61View::OnEllipse)
	ON_COMMAND(ID_BEZIER, &CPractices61View::OnBezier)
	ON_COMMAND(ID_LINE_COLOR, &CPractices61View::OnLineColor)
	ON_COMMAND(ID_FACE_COLOR, &CPractices61View::OnFaceColor)
	ON_COMMAND(ID_FDIAGONAL, &CPractices61View::OnFdiagonal)
	ON_COMMAND(ID_CROSS, &CPractices61View::OnCross)
	ON_COMMAND(ID_VERTICAL, &CPractices61View::OnVertical)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CPractices61View::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CPractices61View::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_BEZIER, &CPractices61View::OnUpdateBezier)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPractices61View 생성/소멸

CPractices61View::CPractices61View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_nDrawMode = LINE_MODE;
	m_bContextMenu = true;
	m_bFirst = true;
	m_bLButtonDown = false;
	m_nCount = 0;
	for (int i = 0; i < 50; i++) {
		m_ptData[i] = 0;
	}
	m_bHatch = false;
	m_nHatchStyle = HS_CROSS;
	m_colorPen = RGB(0, 0, 0);
	m_colorBrush = RGB(255, 255, 255);

}

CPractices61View::~CPractices61View()
{
}

BOOL CPractices61View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractices61View 그리기

void CPractices61View::OnDraw(CDC* pDC)
{
	CPractices61Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CPen pen, bezierpen, * oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);
	bezierpen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldpen = pDC->SelectObject(&pen);
	pDC->SetROP2(R2_COPYPEN);
	CBrush brush, * oldbrush;
	if (m_bHatch) {
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);
	}
	else
		brush.CreateSolidBrush(m_colorBrush);

	oldbrush = pDC->SelectObject(&brush);

	switch (m_nDrawMode)
	{
	case LINE_MODE :
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;

	case ELLIPSE_MODE :
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;

	case BEZIER_MODE :
		pDC->SelectObject(GetStockObject(GRAY_BRUSH));

		pDC->MoveTo(m_ptData[0]);
		for (int i = 0; i < m_nCount; i++) {
			pDC->Ellipse(m_ptData[i].x - 4, m_ptData[i].y - 4, m_ptData[i].x + 4, m_ptData[i].y + 4);
		}
		pDC->Polyline(m_ptData, m_nCount);

		pDC->SelectObject(bezierpen);
		pDC->PolyBezier(m_ptData, m_nCount);
		break;
	}
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
}


// CPractices61View 인쇄


void CPractices61View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractices61View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractices61View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractices61View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CPractices61View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractices61View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	if (m_bContextMenu == true) {
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	}
	m_bContextMenu = true;
#endif
}


// CPractices61View 진단

#ifdef _DEBUG
void CPractices61View::AssertValid() const
{
	CView::AssertValid();
}

void CPractices61View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractices61Doc* CPractices61View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractices61Doc)));
	return (CPractices61Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractices61View 메시지 처리기


void CPractices61View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 직선그리기 모드 변경
	m_nDrawMode = LINE_MODE;
}

void CPractices61View::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 원 그리기 모드 변경 
	m_nDrawMode = ELLIPSE_MODE;
}

void CPractices61View::OnBezier()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 베지어 곡선 그리기 모드 변경 
	m_nDrawMode = BEZIER_MODE;
}

void CPractices61View::OnLineColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;
	if (dlgColor.DoModal() == IDOK) {
		m_colorPen = dlgColor.GetColor();
	}
	Invalidate(true);
}

void CPractices61View::OnFaceColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;
	if (dlgColor.DoModal() == IDOK) {
		m_colorBrush = dlgColor.GetColor();
	}
	m_bHatch = false;
	Invalidate(true);
}

void CPractices61View::OnFdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 오른쪽 45도 빗금 변경
	m_nHatchStyle = HS_FDIAGONAL;
	m_bHatch = true;
	Invalidate(true);
}

void CPractices61View::OnCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 십자가 빗금 변경
	m_nHatchStyle = HS_CROSS;
	m_bHatch = true;
	Invalidate(true);
}

void CPractices61View::OnVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 수직 빗금 변경
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractices61View::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}

void CPractices61View::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);
}

void CPractices61View::OnUpdateBezier(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == BEZIER_MODE ? 1 : 0);
}


void CPractices61View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bFirst) {
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_bFirst = true;
		m_nCount = 0;
		for (int i = 0; i < 50; i++)
			m_ptData[i] = 0;
		Invalidate();
	}
		switch (m_nDrawMode)
		{
		case LINE_MODE:
			
		case ELLIPSE_MODE:
			m_bLButtonDown = true;
			m_ptStart = m_ptPrev = point;
			m_bFirst = false;
			break;

		case BEZIER_MODE:
			CClientDC dc(this);
			dc.SelectObject(GetStockObject(GRAY_BRUSH));
			m_ptStart = m_ptPrev = point;
			dc.Ellipse(point.x - 4, point.y - 4, point.x + 4, point.y + 4);
			if (m_bFirst == true) 
				m_bFirst = false;
			m_ptData[m_nCount] = point;
			m_nCount++;
			break;
		}

		RECT rectClient;
		SetCapture();
		GetClientRect(&rectClient);
		ClientToScreen(&rectClient);
		::ClipCursor(&rectClient);
	CView::OnLButtonDown(nFlags, point);
}


void CPractices61View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CPen pen,*oldPen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);
	oldPen = dc.SelectObject(&pen);

	dc.SetROP2(R2_NOTXORPEN);

	CBrush brush, * oldBrush;
	if (m_bHatch) {
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);
	}
	else {
		brush.CreateSolidBrush(m_colorBrush);
	}

	oldBrush = dc.SelectObject(&brush);

	switch (m_nDrawMode)
	{
	case LINE_MODE:
		if (m_bLButtonDown) {
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;
		}
		break;
	case ELLIPSE_MODE :
		if (m_bLButtonDown) {
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;
		}
		break;

	case BEZIER_MODE :
		if (!m_bFirst) {
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;
		}
		break;
	}
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();


	CView::OnMouseMove(nFlags, point);
}


void CPractices61View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bLButtonDown) {
		if (m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE) {
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();
			::ClipCursor(NULL);
			Invalidate(true);
		}
	}
	CView::OnLButtonUp(nFlags, point);
}


void CPractices61View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);

	if (m_nDrawMode == BEZIER_MODE) 
	{
		if (!m_bFirst) {
			m_bContextMenu = FALSE;
			dc.SelectObject(GetStockObject(GRAY_BRUSH));
			dc.Ellipse(point.x - 4, point.y - 4, point.x + 4, point.y + 4);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptStart = point;
			m_ptData[m_nCount] = point;
			m_nCount++;
			int num = (m_nCount - 1) % 3;
			if (num == 0) {
				m_bFirst - true;
				ReleaseCapture();
				::ClipCursor(NULL);
				Invalidate(TRUE);
			}
			else {
				AfxMessageBox(_T("점의 수 오류 < 점의수 = 베지어 곡선 수 * 3"));
			}
		}
	}
	CView::OnRButtonDown(nFlags, point);
}
