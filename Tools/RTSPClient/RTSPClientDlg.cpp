
// RTSPClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RTSPClient.h"
#include "RTSPClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CRTSPClientDlg 对话框



CRTSPClientDlg::CRTSPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RTSPCLIENT_DIALOG, pParent)\
	, m_port(0), m_channel(0), m_str_user(_T(""))\
	, m_str_pwd(_T("")), m_stream_type(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_task_scheduler = BasicTaskScheduler::createNew();
	m_env = BasicUsageEnvironment::createNew(*m_task_scheduler);
	env = m_env;
}

void CRTSPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IP, m_ip);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Text(pDX, IDC_USER, m_str_user);
	DDX_Text(pDX, IDC_PWD, m_str_pwd);
	DDX_Text(pDX, IDC_CHANNEL, m_channel);
	DDX_Text(pDX, IDC_STREAM, m_stream_type);
}

BEGIN_MESSAGE_MAP(CRTSPClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRTSPClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_PLAY, &CRTSPClientDlg::OnBnClickedPlay)
END_MESSAGE_MAP()


// CRTSPClientDlg 消息处理程序

BOOL CRTSPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	m_ip.SetAddress(172, 16, 0, 10);
	m_port = 8554;
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRTSPClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRTSPClientDlg::OnPaint()
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
HCURSOR CRTSPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRTSPClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CRTSPClientDlg::OnBnClickedPlay()
{
	UpdateData(true);
	BYTE ip_array[4] = { 0 };
	m_ip.GetAddress(ip_array[0], ip_array[1], ip_array[2]\
		, ip_array[3]);
	char ip_host[80] = { 0 };
	sprintf(ip_host, "%d.%d.%d.%d", ip_array[0], ip_array[1], ip_array[2]\
		, ip_array[3]);
	sprintf(m_str_url, "rtsp://%s:%d/a.ts", ip_host, m_port);
	char *argv[2];
	argv[0] = "player";
	argv[1] = m_str_url;
	//start(2, argv);
	ourClient = createClient(*m_env, m_str_url, 0, "player");
	if (ourClient == nullptr)
	{
		return;
	}
	else
	{
		continueAfterClientCreation1();
	}
	m_env->taskScheduler().doEventLoop();
	return;
	// TODO: Add your control notification handler code here
}
