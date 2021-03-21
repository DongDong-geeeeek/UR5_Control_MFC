
// CtrlURobotDlg.h: 头文件
//

#pragma once
#include "Client.h"

// CCtrlURobotDlg 对话框
class CCtrlURobotDlg : public CDialogEx
{
// 构造
public:
	CCtrlURobotDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTRLUROBOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 界面上手动输入的IP地址,绑定到IP地址输入框
	CString m_strRobortIpAdress;
	// 绑定到界面端口输入框的变量
	UINT m_iRobortPort;
	Client m_digClient;
	
	afx_msg void OnBnClickedButconnect();
	afx_msg void OnBnClickedButtdisconect();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButclrrecv();
	afx_msg void OnBnClickedButclrsend();
	afx_msg void OnBnClickedGetexitcode();
};
