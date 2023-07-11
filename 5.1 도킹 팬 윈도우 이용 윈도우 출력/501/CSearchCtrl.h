#pragma once
#include "afxdialogex.h"


// CSearchCtrl 대화 상자

class CSearchCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchCtrl)

public:
	CSearchCtrl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSearchCtrl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbDrive;
	CString m_strName;
	virtual BOOL OnInitDialog();
	bool m_bTarget;		// 라디오 버튼 선택을 나타내는 변수
	bool m_bChecked[3];	// 체크 박스 선택을 나태니는 변수
	
	afx_msg void OnRadioFile();
	afx_msg void OnRadioFolder();
	afx_msg void OnClickedCheckMfc();
	afx_msg void OnClickedCheckMulti();
	afx_msg void OnClickedCheckWord();
	afx_msg void OnClickedButtonNew();
	afx_msg void OnClickedButtonSearch();
};
