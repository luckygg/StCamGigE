
// FTech_StCamGigE.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFTech_StCamGigEApp:
// See FTech_StCamGigE.cpp for the implementation of this class
//

class CFTech_StCamGigEApp : public CWinApp
{
public:
	CFTech_StCamGigEApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFTech_StCamGigEApp theApp;