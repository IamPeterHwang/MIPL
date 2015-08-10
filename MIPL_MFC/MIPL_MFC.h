
// MIPL_MFC.h : main header file for the MIPL_MFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMIPL_MFCApp:
// See MIPL_MFC.cpp for the implementation of this class
//

class CMIPL_MFCApp : public CWinApp
{
public:
	CMIPL_MFCApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMIPL_MFCApp theApp;
