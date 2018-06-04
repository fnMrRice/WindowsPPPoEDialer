
// Dora's PPPoEDialerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Dora's PPPoEDialer.h"
#include "Dora's PPPoEDialerDlg.h"
#include "afxdialogex.h"

#include <raserror.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDorasPPPoEDialerDlg 对话框



CDorasPPPoEDialerDlg::CDorasPPPoEDialerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DORASPPPOEDIALER_DIALOG, pParent)
    , sName(_T(""))
    , sPass(_T(""))
    , sMessage(_T(""))
    , connected(false)
{
    //tcName.SetLimitText(20);
    //tcPass.SetLimitText(20);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDorasPPPoEDialerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, TEXT_NAME, tcName);
    DDX_Control(pDX, TEXT_PASS, tcPass);
    DDX_Control(pDX, MFCBUTTON_CONNECT_TOGGLE, btnConnectToggle);
    DDX_Control(pDX, STATIC_MESSAGE, ctsMessage);
}

BEGIN_MESSAGE_MAP(CDorasPPPoEDialerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(MFCBUTTON_CONNECT_TOGGLE, &CDorasPPPoEDialerDlg::OnBnClickedConnectToggle)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDorasPPPoEDialerDlg 消息处理程序

BOOL CDorasPPPoEDialerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDorasPPPoEDialerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
    tcName.LimitText(20);
    tcPass.LimitText(20);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDorasPPPoEDialerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDorasPPPoEDialerDlg::setMessage(const CString &m, bool err ) {
    SetDlgItemText(STATIC_MESSAGE, m);
}
void CDorasPPPoEDialerDlg::appendMessage(const CString &m, bool err ) {
    GetDlgItemText(STATIC_MESSAGE, sMessage);
    SetDlgItemText(STATIC_MESSAGE, sMessage + m);
}

HBRUSH CDorasPPPoEDialerDlg::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == STATIC_MESSAGE) {
        pDC->SetTextColor(msgAlert ? RGB(0xFF, 0x00, 0x00) : RGB(0x00, 0x00, 0x00));
    }
    return hbr;
}

void CDorasPPPoEDialerDlg::OnBnClickedConnectToggle()
{
    // TODO: 在此添加控件通知处理程序代码
    if (!connected) {
        GetDlgItemText(TEXT_NAME, sName);
        GetDlgItemText(TEXT_PASS, sPass);
        sName = handleString(sName);
        sPass = handleString(sPass);
        if (L"" == sName || L"" == sPass) {
            msgAlert = TRUE;
            setMessage(L"请输入用户名和密码!");
            return;
        }
        
        HANDLE h;
        h = CreateThread(NULL, 0, Thread_Connect, this, 0, NULL);
        btnConnectToggle.EnableWindow(FALSE);
        h = CreateThread(NULL, 0, Thread_checkConnection, this, 0, NULL);
        return;
    }
    else if (connected) {
        DWORD ErrCode = RasHangUp(*lphRasConn);
        if (ERROR_SUCCESS == ErrCode) {
            msgAlert = FALSE;
            setMessage(L"断开成功!");
            connected = false;
        }
        else {
            msgAlert = TRUE;
            setMessage(L"断开错误! Error Code: ");
            appendMessage(int2str(ErrCode));
            return;
        }
        UpdateData(TRUE);
        btnConnectToggle.SetWindowTextW(L"连接");
        UpdateData(FALSE);
        return;
    }
}
void CDorasPPPoEDialerDlg::OnOK() {
    //UpdateData(FALSE);
};

BOOL CDorasPPPoEDialerDlg::PreTranslateMessage(MSG *pMsg)
{
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        if (GetFocus() == &tcName) {
            tcPass.SetFocus();
        }
        else {
            OnBnClickedConnectToggle();
        }
        return true;
    }
    return CDialog::PreTranslateMessage(pMsg);

}
