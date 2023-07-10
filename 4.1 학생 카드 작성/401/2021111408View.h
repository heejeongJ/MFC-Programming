﻿
// 2021111408View.h: CMy2021111408View 클래스의 인터페이스
//

#pragma once


class CMy2021111408View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy2021111408View() noexcept;
	DECLARE_DYNCREATE(CMy2021111408View)

// 특성입니다.
public:
	CMy2021111408Doc* GetDocument() const;

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
	virtual ~CMy2021111408View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// 학생 정보 저장하기 위한 변수
	CString m_strDept;		// 학과 저장하기 위한 변수
	CString m_strSex;		// 성별 저장하기 위한 변수
	CString m_strHobby;		// 성별 저장하기 위한 변수
	CString m_strName;		// 이름 저장하기 위한 변수
};

#ifndef _DEBUG  // 2021111408View.cpp의 디버그 버전
inline CMy2021111408Doc* CMy2021111408View::GetDocument() const
   { return reinterpret_cast<CMy2021111408Doc*>(m_pDocument); }
#endif

