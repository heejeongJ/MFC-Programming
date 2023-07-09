
// 2021111408Dlg.h: 헤더 파일
//

#pragma once


// CMy2021111408Dlg 대화 상자
class CMy2021111408Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMy2021111408Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2021111408_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListLeft();
	CListBox m_listLeft;					// Left ListBox(물품 목록) 변수
	CListBox m_listRight;					// Right ListBox(구매 예정 목록) 변수
	// ComboBox 변수
	CComboBox m_cbMove;						// ComboBox 변수
	CString m_strResult;					// EditControl 변수
	afx_msg void OnSelchangeComboMove();
	afx_msg void OnClickedButtonPurchase();
};
