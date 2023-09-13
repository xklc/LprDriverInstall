// DriverInstall.h : main header file for the DRIVERINSTALL application
//

#if !defined(AFX_DRIVERINSTALL_H__081F40E2_1460_4D99_B9D3_A897D116CC03__INCLUDED_)
#define AFX_DRIVERINSTALL_H__081F40E2_1460_4D99_B9D3_A897D116CC03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDriverInstallApp:
// See DriverInstall.cpp for the implementation of this class
//

class CDriverInstallApp : public CWinApp
{
public:
	CDriverInstallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverInstallApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDriverInstallApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERINSTALL_H__081F40E2_1460_4D99_B9D3_A897D116CC03__INCLUDED_)
