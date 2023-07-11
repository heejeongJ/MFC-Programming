
// 2021111408_주희정View.h: CMy2021111408주희정View 클래스의 인터페이스
//

#pragma once


class CMy2021111408주희정View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy2021111408주희정View() noexcept;
	DECLARE_DYNCREATE(CMy2021111408주희정View)

// 특성입니다.
public:
	CMy2021111408주희정Doc* GetDocument() const;

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
	virtual ~CMy2021111408주희정View();
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
	
	CString m_strFileType;		// 검색 파일 종류를 저장하는 변수
	CString m_strTarget;		// 검색 대상을 저장하는 변수
	CString m_strDrive;			// 검색 위치를 저장하는 변수
	CString m_strName;			// 검색 이름을 저장하는 변수
	CString m_strInfo;			// 검색 전 "다음의 조건으로 검색합니다" 설명하는 변수

};

#ifndef _DEBUG  // 2021111408_주희정View.cpp의 디버그 버전
inline CMy2021111408주희정Doc* CMy2021111408주희정View::GetDocument() const
   { return reinterpret_cast<CMy2021111408주희정Doc*>(m_pDocument); }
#endif

