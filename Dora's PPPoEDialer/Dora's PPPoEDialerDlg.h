
// Dora's PPPoEDialerDlg.h: 头文件
//

#pragma once


// CDorasPPPoEDialerDlg 对话框
class CDorasPPPoEDialerDlg : public CDialogEx
{
// 构造
public:
	CDorasPPPoEDialerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DORASPPPOEDIALER_DIALOG };
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
private:
    CString sMessage;
    CEdit tcName;
    CEdit tcPass;
    CStatic ctsMessage;
public:
    CString sName;
    CString sPass;
    DWORD ErrCode;
    LPHRASCONN lphRasConn;
    bool msgAlert;
    bool connected;
    CMFCButton btnConnectToggle;
    afx_msg void OnBnClickedConnectToggle();
    void setMessage(const CString &m, bool err = false);
    void appendMessage(const CString &m, bool err = false);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
