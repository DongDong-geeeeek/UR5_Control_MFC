
// CtrlURobotDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CtrlURobot.h"
#include "CtrlURobotDlg.h"
#include "afxdialogex.h"
#include <WS2tcpip.h>
#include "Common.h"
#include "Client.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define  FIRST_PACKAGE  1105
#define  SECON_PACKAGE	1395
#define  PACKAGESIZE	725

UINT __cdecl MyControllingFunction(LPVOID pParam);

/***********************************************************************************/
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

/***********************************************************************************/
// CCtrlURobotDlg 对话框



CCtrlURobotDlg::CCtrlURobotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTRLUROBOT_DIALOG, pParent)
	, m_strRobortIpAdress(_T("192.168.1.11"))	/*初始化列表*/
	, m_iRobortPort(30001)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCtrlURobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITIPADDR, m_strRobortIpAdress);
	DDX_Text(pDX, IDC_EDITPORT, m_iRobortPort);
}

BEGIN_MESSAGE_MAP(CCtrlURobotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTCONNECT, &CCtrlURobotDlg::OnBnClickedButconnect)
	ON_BN_CLICKED(IDC_BUTTDISCONECT, &CCtrlURobotDlg::OnBnClickedButtdisconect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTCLRRECV, &CCtrlURobotDlg::OnBnClickedButclrrecv)
	ON_BN_CLICKED(IDC_BUTCLRSEND, &CCtrlURobotDlg::OnBnClickedButclrsend)
END_MESSAGE_MAP()


// CCtrlURobotDlg 消息处理程序

BOOL CCtrlURobotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	/*打开对话框第一步先打开Socket库并校验其版本*/
	WinSockInit();										

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCtrlURobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCtrlURobotDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCtrlURobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/******************************回调函数*****************************/

void CCtrlURobotDlg::OnBnClickedButconnect()
{
	UpdateData(TRUE);	
	/**************************************************************/
	if (m_digClient.m_flag == FALSE)//套接字不存在
	{
		// 创建套接字
		if (m_digClient.CreatSocket()) // 创建成功
		{
			m_digClient.m_flag = TRUE;
			// 尝试连接
			SOCKADDR_IN addrSer;
			char strRobotIp[1024];
			WideCharToMultiByte(CP_OEMCP, 0, m_strRobortIpAdress, -1, strRobotIp, 1024, NULL, NULL);
			int iRobotPort = m_iRobortPort;
			addrSer.sin_family = AF_INET;						//  将协议信息存进addrSer结构体
			addrSer.sin_port = htons(iRobotPort);				//  将端口信息存进addrSer结构体
			inet_pton(AF_INET, strRobotIp, &addrSer.sin_addr);	//  将IP地址存进addrSer结构体
			m_digClient.SetRobortAddress(&addrSer);

			if (m_digClient.ConnectToRobort()) 
			{
				/*设置连接成功标识符!!!!!!!!!!*/
				m_digClient.m_conSucc = TRUE;

				CString tipMsg;
				tipMsg.Format(_T("已连接到机械臂!"));
				AfxMessageBox(tipMsg);

				// 设置ip\port 控件失效
				CWnd *cEditIp = GetDlgItem(IDC_EDITIPADDR);
				CWnd *cEditPort = GetDlgItem(IDC_EDITPORT);
				cEditIp->EnableWindow(FALSE);
				cEditPort->EnableWindow(FALSE);
				
				//return;
			} 
			else // 连接失败,提示并返回
			{
				CString tipMsg;
				tipMsg.Format(_T("连接机械臂失败!错误代码为%d"), WSAGetLastError());
				AfxMessageBox(tipMsg);
				return;
			}
		} 
		else  // 创建失败,提示并返回
		{ 
			CString tipMsg;
			tipMsg.Format(_T("创建套接字失败,错误代码为%d"), WSAGetLastError());
			AfxMessageBox(tipMsg);
			return;
		}
	} 
	else//套接字存在
	{
		// 套接字是否已经连接
		if (m_digClient.m_conSucc == FALSE) // 没有连接
		{
			// 尝试连接
			SOCKADDR_IN addrSer;
			char strRobotIp[1024];
			WideCharToMultiByte(CP_OEMCP, 0, m_strRobortIpAdress, -1, strRobotIp, 1024, NULL, NULL);
			int iRobotPort = m_iRobortPort;
			addrSer.sin_family = AF_INET;						
			addrSer.sin_port = htons(iRobotPort);				
			inet_pton(AF_INET, strRobotIp, &addrSer.sin_addr);	
			m_digClient.SetRobortAddress(&addrSer);

			if (TRUE == m_digClient.ConnectToRobort()) // 连接成功
			{ 
				/*设置连接成功标识符!!!!!!!!!!*/
				m_digClient.m_conSucc = TRUE;

				CString tipMsg;
				tipMsg.Format(_T("已连接到机械臂!"));
				AfxMessageBox(tipMsg);

				// 设置ip\port 控件失效
				CWnd *cEditIp = GetDlgItem(IDC_EDITIPADDR);
				CWnd *cEditPort = GetDlgItem(IDC_EDITPORT);
				cEditIp->EnableWindow(FALSE);
				cEditPort->EnableWindow(FALSE);
				
				//return;
			} 
			else  // 连接失败
			{
				CString tipMsg;
				tipMsg.Format(_T("连接到机械臂失败,错误代码为 %d"), WSAGetLastError());
				AfxMessageBox(tipMsg);
				return;
			}
		} 
		else // 已经连接
		{
			// 提示不要重复连接,返回
			CString tipMsg;
			tipMsg.Format(_T("您已经连接到机械臂,请勿重复连接!"));
			AfxMessageBox(tipMsg);
			return;
		}
	}
	/**************************************************************/
	//调用线程函数接受数据
	if (m_digClient.m_flag == TRUE && m_digClient.m_conSucc == TRUE)
	{
		/*第一次连接成功进入线程处理函数*/
		CWinThread* MyThread = AfxBeginThread(MyControllingFunction, this);
	}

	return;
}

void CCtrlURobotDlg::OnBnClickedButtdisconect()
{
	// TODO: 在此添加控件通知处理程序代码
	m_digClient.m_flag = FALSE;
	m_digClient.m_conSucc = FALSE;
	::WaitForSingleObject(m_digClient.m_hThread, INFINITE);
	CloseHandle(m_digClient.m_hThread);

	if (m_digClient.m_socket!= INVALID_SOCKET)
	{
		closesocket(m_digClient.m_socket);						// 断开连接时程序出现过崩溃!!!!
	}
	
	CWnd *cEditIp = GetDlgItem(IDC_EDITIPADDR);
	CWnd *cEditPort = GetDlgItem(IDC_EDITPORT);
	cEditIp->EnableWindow(TRUE);
	cEditPort->EnableWindow(TRUE);
}

void CCtrlURobotDlg::OnClose()
{
	m_digClient.m_flag = FALSE;
	m_digClient.m_conSucc = FALSE;

	if (m_digClient.m_socket != INVALID_SOCKET)
	{
		closesocket(m_digClient.m_socket);						// 断开连接时程序出现过崩溃!!!!
	}

	WSACleanup();
	CDialogEx::OnClose();
}

UINT __cdecl MyControllingFunction(LPVOID pParam)
{
	CCtrlURobotDlg * pCtrlDlg = (CCtrlURobotDlg *)pParam;
	// 在堆上开辟一块最终缓冲区

	char *firstRecvBuf = new char[FIRST_PACKAGE];
	char *seconRecvBuf = new char[SECON_PACKAGE];
	unsigned char *strRecvBuf = new unsigned char[PACKAGESIZE];
	char* strRecvTemp = new char[PACKAGESIZE];
	memset(strRecvBuf, '\0', PACKAGESIZE);
	memset(strRecvTemp, '\0', PACKAGESIZE);

	CEdit * pEditRecv = (CEdit *)pCtrlDlg->GetDlgItem(IDC_EDITRECV);
	CString lastDisp = NULL;
	unsigned short a = 1;
	
	CString recvTemp = NULL;

	while ((pCtrlDlg->m_digClient.m_flag == TRUE) && (pCtrlDlg->m_digClient.m_conSucc == TRUE))
	{
		if (a == 1)
		{
			// 读取1105包	然后丢弃
			pCtrlDlg->m_digClient.Recv(firstRecvBuf, FIRST_PACKAGE);
			a++;
			delete[]firstRecvBuf;
		}
		else if (a == 2)
		{
			// 读取1395包	然后丢弃
			pCtrlDlg->m_digClient.Recv(seconRecvBuf, SECON_PACKAGE);
			a++;
			delete[]seconRecvBuf;
		}
		else if (a >= 3)
		{
			// 读取725包
			int numOfReceive = 0;
			numOfReceive = pCtrlDlg->m_digClient.Recv(strRecvTemp, PACKAGESIZE);
			memcpy(strRecvBuf, strRecvTemp, PACKAGESIZE);						// 拷贝到strRecv中的数据量是我可以指定的
			memset(strRecvTemp, '\0', PACKAGESIZE);								// 这里犯过错误,memset越界了,导致程序崩溃

			// 显示数据
			CString recvText = NULL;
			for (int i = 0; i < numOfReceive; i++)
			{
				recvTemp.Empty();
				recvTemp.Format(_T("%02X\t"), strRecvBuf[i]);
				recvText.Append(recvTemp);
				if ((i + 1) % 11 == 0)
				{
					recvText += "\r\n";
				}
			}
			recvText += "\r\n";

			CString strDisp = NULL;
			strDisp += lastDisp;
			strDisp += recvText;
			
			pEditRecv->SetWindowTextW(strDisp);

			int nLength = pEditRecv->GetWindowTextLengthW();// 将光标聚焦于末尾
			pEditRecv->SetSel(nLength, nLength, FALSE);
			pEditRecv->SetFocus();

			lastDisp = recvText;
		}

	}

	/*学习多线程,然后添加WaitSingleObiect()退出线程*/


	delete[]strRecvBuf;
	delete[]strRecvTemp;
	return 0;
}


void CCtrlURobotDlg::OnBnClickedButclrrecv()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit * pEditRecv = (CEdit *)GetDlgItem(IDC_EDITRECV);
	CString clearStrRecv = NULL;
	pEditRecv->SetWindowTextW(clearStrRecv);
}


void CCtrlURobotDlg::OnBnClickedButclrsend()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit * pEditSend = (CEdit *)GetDlgItem(IDC_EDITSEND);
	CString clearStrSend = NULL;
	pEditSend->SetWindowTextW(clearStrSend);
}
