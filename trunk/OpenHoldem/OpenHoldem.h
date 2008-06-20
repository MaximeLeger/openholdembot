// OpenHoldem.h : main header file for the OpenHoldem application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// COpenHoldemApp:
// See OpenHoldem.cpp for the implementation of this class
//

class COpenHoldemApp : public CWinApp {
public:
	COpenHoldemApp();
	~COpenHoldemApp();
	void MyLoadStdProfileSettings(UINT nMaxMRU);
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	virtual int ExitInstance();
};

extern COpenHoldemApp theApp;

#define		WMA_SETWINDOWTEXT				WM_APP+1