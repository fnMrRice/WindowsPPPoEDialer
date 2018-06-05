
// MyWindowsPPPoEDialerDlg.h: 头文件
//

#pragma once

// CMyWindowsPPPoEDialerDlg 对话框
class CMyWindowsPPPoEDialerDlg : public CDialogEx
{
// 构造
public:
	CMyWindowsPPPoEDialerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYWINDOWSPPPOEDIALER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
    BOOL PreTranslateMessage(MSG *pMsg);
    virtual void OnOK();
    CEdit tcName;
    CEdit tcPass;
    CString sMessage;
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
    CString sName;
    CString sPass;
    DWORD ErrCode;
    LPHRASCONN lphRasConn;
    bool msgAlert;
    int connected;
    afx_msg void OnBnClickedConnectToggle();
    CMFCButton btnConnectToggle;
    void setMessage(const CString &m);
    void appendMessage(const CString &m);
    CStatic stMsg;
};
