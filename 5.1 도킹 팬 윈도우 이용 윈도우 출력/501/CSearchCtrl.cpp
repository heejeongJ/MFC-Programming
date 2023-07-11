// CSearchCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "2021111408_주희정.h"
#include "afxdialogex.h"
#include "CSearchCtrl.h"


#include "MainFrm.h"
#include "2021111408_주희정Doc.h"
#include "2021111408_주희정View.h"

// CSearchCtrl 대화 상자

IMPLEMENT_DYNAMIC(CSearchCtrl, CDialogEx)

CSearchCtrl::CSearchCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strName(_T(""))
{

}

CSearchCtrl::~CSearchCtrl()
{
}

void CSearchCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRIVE, m_cbDrive);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CSearchCtrl, CDialogEx)
	ON_COMMAND(IDC_RADIO_FILE, &CSearchCtrl::OnRadioFile)
	ON_COMMAND(IDC_RADIO_FOLDER, &CSearchCtrl::OnRadioFolder)
	ON_BN_CLICKED(IDC_CHECK_MFC, &CSearchCtrl::OnClickedCheckMfc)
	ON_BN_CLICKED(IDC_CHECK_MULTI, &CSearchCtrl::OnClickedCheckMulti)
	ON_BN_CLICKED(IDC_CHECK_WORD, &CSearchCtrl::OnClickedCheckWord)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CSearchCtrl::OnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CSearchCtrl::OnClickedButtonSearch)
END_MESSAGE_MAP()


// CSearchCtrl 메시지 처리기


BOOL CSearchCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_cbDrive.AddString(_T("하드 드라이브 C:"));
	m_cbDrive.AddString(_T("하드 드라이브 D:"));
	m_cbDrive.AddString(_T("하드 드라이브 [C: D:]"));

	//m_cbDrive.SetCurSel(0);
	((CButton*)GetDlgItem(IDC_RADIO_FILE))->SetCheck(TRUE);
	m_bTarget = true;			// 여기서 true는 파일을 나타냄
	m_bChecked[0] = m_bChecked[1] = m_bChecked[2] = false;	// 체크 해제된 것으로 초기화

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSearchCtrl::OnRadioFile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bTarget = true;
	((CButton*)GetDlgItem(IDC_CHECK_MFC))->EnableWindow(1);
	((CButton*)GetDlgItem(IDC_CHECK_MULTI))->EnableWindow(1);
	((CButton*)GetDlgItem(IDC_CHECK_WORD))->EnableWindow(1);
}


void CSearchCtrl::OnRadioFolder()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bTarget = false;
	((CButton*)GetDlgItem(IDC_CHECK_MFC))->EnableWindow(0);
	((CButton*)GetDlgItem(IDC_CHECK_MULTI))->EnableWindow(0);
	((CButton*)GetDlgItem(IDC_CHECK_WORD))->EnableWindow(0);

	((CButton*)GetDlgItem(IDC_CHECK_MFC))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_MULTI))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_WORD))->SetCheck(FALSE);
}


void CSearchCtrl::OnClickedCheckMfc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bChecked[0] = !m_bChecked[0];
}


void CSearchCtrl::OnClickedCheckMulti()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bChecked[1] = !m_bChecked[1];
}


void CSearchCtrl::OnClickedCheckWord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bChecked[2] = !m_bChecked[2];
}


void CSearchCtrl::OnClickedButtonNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2021111408주희정View* pView = (CMy2021111408주희정View*)pFrame->GetActiveView();
	UpdateData(TRUE);

	// 대화 상자의 컨트롤 값을 초기화
	m_cbDrive.SetCurSel(-1);
	((CButton*)GetDlgItem(IDC_RADIO_FILE))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_FOLDER))->SetCheck(FALSE);

	((CButton*)GetDlgItem(IDC_CHECK_MFC))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_MULTI))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_WORD))->SetCheck(FALSE);

	// 에디트 텍스트 초기화
	CEdit* pEditName = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	pEditName->SetWindowText(_T(""));

	// 파일 선택으로 초기화되었으므로, 체크	박스 선택 가능하도록 초기화
	m_bTarget = true;
	((CButton*)GetDlgItem(IDC_CHECK_MFC))->EnableWindow(1);
	((CButton*)GetDlgItem(IDC_CHECK_MULTI))->EnableWindow(1);
	((CButton*)GetDlgItem(IDC_CHECK_WORD))->EnableWindow(1);

	m_bChecked[0] = m_bChecked[1] = m_bChecked[2] = false;
	m_strName = _T("");

	// 새검색 클릭 시 화면 초기화
	pView->m_strInfo = _T("다음의 조건으로 검색합니다.");
	pView->m_strTarget.Empty();
	pView->m_strFileType.Empty();
	pView->m_strDrive.Empty();
	pView->m_strName.Empty();
	
	pView->Invalidate();
}


void CSearchCtrl::OnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2021111408주희정View* pView = (CMy2021111408주희정View*)pFrame->GetActiveView();
	UpdateData(TRUE);
	pView->m_strInfo = _T("다음의 조건으로 검색합니다.");
	pView->m_strTarget = _T("검색 대상 : ");
	if (m_bTarget) {
		pView->m_strTarget += _T("파일");
	}
	else {
		pView->m_strTarget += _T("폴더");
	}

	if (m_bTarget) {
		pView->m_strFileType = _T("검색 파일 종류 : ");

		if (m_bChecked[0]) {
			pView->m_strFileType += _T(" Visual C++ 프로젝트 파일 ");
		}
		if (m_bChecked[1]) {
			pView->m_strFileType += _T(" 멀티미디어 파일");
		}
		if (m_bChecked[2]) {
			pView->m_strFileType += _T(" 문서 파일");
		}
		if (!m_bChecked[0] && !m_bChecked[1] && !m_bChecked[2]) {
			AfxMessageBox(_T("검색 파일 종류를 지정해주세요."));
			return;
		}
	}
	else {
		pView->m_strFileType.Empty();
	}
	pView->m_strDrive = _T("검색 위치 : ");
	if (m_cbDrive.GetCurSel() == 0) {
		pView->m_strDrive += _T("하드 드라이브 C:");
	}
	else if (m_cbDrive.GetCurSel() == 1) {
		pView->m_strDrive += _T("하드 드라이브 D:");
	}
	else if (m_cbDrive.GetCurSel() == 2) {
		pView->m_strDrive += _T("하드 드라이브 [C:, D:]");
	}
	if (m_cbDrive.GetCurSel() == -1) {
		AfxMessageBox(_T("콤보 박스에서 검색 위치를 선택해주세요."));
		return;
	}

	if (m_strName.IsEmpty()) {
		AfxMessageBox(_T("검색 대상 전체 또는 일부 이름을 입력하십시오."));
		return;
	}

	pView->m_strName = _T("이름 : ");
	pView->m_strName += m_strName;

	pView->Invalidate();
	
}
