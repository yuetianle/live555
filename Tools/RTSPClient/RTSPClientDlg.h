
// RTSPClientDlg.h : ͷ�ļ�
//
#pragma once
#include "playCommon.hh"
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"

extern Medium *ourClient;
extern UsageEnvironment *env;
extern void continueAfterClientCreation1();
extern Medium* createClient(UsageEnvironment& env, char const* URL, int verbosityLevel, char const* applicationName);
//extern int start(int argc, char** argv);
// CRTSPClientDlg �Ի���
class CRTSPClientDlg : public CDialogEx
{
// ����
public:
	CRTSPClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RTSPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPlay();
public:
	CIPAddressCtrl m_ip;
	CString m_str_user;
	CString m_str_pwd;
	DWORD m_port;
	DWORD m_channel;
	DWORD m_stream_type;
	TaskScheduler *m_task_scheduler;
	UsageEnvironment *m_env;
	char m_str_url[100] = { 0 };
	afx_msg void OnEnChangeEdit1();
};
