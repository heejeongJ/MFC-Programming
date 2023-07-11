
// Practices6-1View.h: CPractices61View 클래스의 인터페이스
//

#pragma once
enum DRAW_MODE { LINE_MODE, ELLIPSE_MODE, BEZIER_MODE };


class CPractices61View : public CView
{
protected: // serialization에서만 만들어집니다.
	CPractices61View() noexcept;
	DECLARE_DYNCREATE(CPractices61View)

// 특성입니다.
public:
	CPractices61Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CPractices61View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	afx_msg void OnEllipse();
	afx_msg void OnBezier();
	afx_msg void OnLineColor();
	afx_msg void OnFaceColor();
	afx_msg void OnFdiagonal();
	afx_msg void OnCross();
	afx_msg void OnVertical();
	int m_nDrawMode;
	int m_nHatchStyle;
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBezier(CCmdUI* pCmdUI);
	CPoint m_ptStart;		// 시작점을 저장하는 변수
	CPoint m_ptPrev;		// 이전점을 저장하는 변수
	bool m_bFirst;			// 처음 그리는 건지 체크하는 변수
	bool m_bLButtonDown;	// 왼쪽 버튼이 눌렸는지 체크하는 변수
	bool m_bContextMenu;	// 문맥 메뉴의 활성화를 체크하는 변수
	bool m_bHatch;			// 해치 브러쉬를 사용하는 지를 체크하는 변수
	CPoint m_ptData[50];	// 컨트롤 폴리곤의 점을 저장할 배열
	int m_nCount;			// m_ptData 배열의 카운트를 저장하는 변수
	COLORREF m_colorPen;	// 펜 색상을 저장하는 변수
	COLORREF m_colorBrush;	// 브러쉬 색상을 저장하는 변수
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Practices6-1View.cpp의 디버그 버전
inline CPractices61Doc* CPractices61View::GetDocument() const
   { return reinterpret_cast<CPractices61Doc*>(m_pDocument); }
#endif

