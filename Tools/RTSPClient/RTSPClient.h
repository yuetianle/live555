
// RTSPClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRTSPClientApp: 
// �йش����ʵ�֣������ RTSPClient.cpp
//

class CRTSPClientApp : public CWinApp
{
public:
	CRTSPClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRTSPClientApp theApp;