#pragma once
#include "CSearchCtrl.h"

// CSearchPane

class CSearchPane : public CDockablePane
{
	DECLARE_DYNAMIC(CSearchPane)

public:
	CSearchPane();
	virtual ~CSearchPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CSearchCtrl m_ctrlSearch;	// 도킹팬은 다이알로그와 세트이므로 다이알로그 멤버 변수 추가해줌.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


