// DriverInstallDlg.h : header file
//

#if !defined(AFX_DRIVERINSTALLDLG_H__EDBCCF33_910F_4720_88B7_BED5E8D96C3D__INCLUDED_)
#define AFX_DRIVERINSTALLDLG_H__EDBCCF33_910F_4720_88B7_BED5E8D96C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <io.h>
#include <string>
#include <stdio.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDriverInstallDlg dialog

class CDriverInstallDlg : public CDialog
{
// Construction
public:
	CDriverInstallDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDriverInstallDlg)
	enum { IDD = IDD_DRIVERINSTALL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverInstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDriverInstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	bool CheckFile(char* file)
	{
		return _access(file, 0) != -1;
	}

	int execCmd(const char* cmd, std::string& result);
	BOOL IsRunAsAdmin();
	BOOL IsPrinterExists(const char * printer_name);
private:
	CString driver_name;
	CString printer_name;
	CString driver_info_path;
	CString port_name;
	CString reg_file;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERINSTALLDLG_H__EDBCCF33_910F_4720_88B7_BED5E8D96C3D__INCLUDED_)
