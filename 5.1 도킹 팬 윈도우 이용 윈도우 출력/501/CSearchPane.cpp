// CSearchPane.cpp: 구현 파일
//

#include "pch.h"
#include "2021111408_주희정.h"
#include "CSearchPane.h"


// CSearchPane

IMPLEMENT_DYNAMIC(CSearchPane, CDockablePane)

CSearchPane::CSearchPane()
{

}

CSearchPane::~CSearchPane()
{
}


BEGIN_MESSAGE_MAP(CSearchPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CSearchPane 메시지 처리기




int CSearchPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_ctrlSearch.Create(IDD_DIALOG1, this)) {
		TRACE0("검색 윈도우를 만들지 못했습니다.\n");
		return -1;
	}
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_ctrlSearch.ShowWindow(SW_SHOW);

	return 0;
}


void CSearchPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_ctrlSearch.GetSafeHwnd()) {
		m_ctrlSearch.MoveWindow(0, 0, cx, cy);
		m_ctrlSearch.SetFocus();
	}
}
