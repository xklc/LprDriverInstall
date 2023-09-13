// DriverInstallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DriverInstall.h"
#include "DriverInstallDlg.h"
#include "Windows.h"
#include "winspool.h"
#include <stdio.h>
#include <stdlib.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverInstallDlg dialog

CDriverInstallDlg::CDriverInstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDriverInstallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDriverInstallDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDriverInstallDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDriverInstallDlg, CDialog)
	//{{AFX_MSG_MAP(CDriverInstallDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverInstallDlg message handlers

BOOL CDriverInstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	if (!this->IsRunAsAdmin()){
		MessageBox( "需要管理员权限安装打印机!", "错误!", MB_OK| MB_ICONERROR);
		return FALSE;
	}

	int length=2048;
	CString config_file("./DriverInstall.ini");
	int len = GetPrivateProfileString("Config", "printer_name", "", printer_name.GetBuffer(length), length, config_file);
	int err = ::GetLastError();
	GetPrivateProfileString("Config", "driver_name", "", driver_name.GetBuffer(length), length, config_file);
	GetPrivateProfileString("Config", "driver_info_path", "", driver_info_path.GetBuffer(length), length, config_file);
	GetPrivateProfileString("Config", "port_name", "", port_name.GetBuffer(length), length, config_file);
	GetPrivateProfileString("Config", "reg_file", "", reg_file.GetBuffer(length), length, config_file);

	SetDlgItemText(IDC_EDIT1, printer_name);
	SetDlgItemText(IDC_EDIT2, driver_name);
	SetDlgItemText(IDC_EDIT3, driver_info_path);
	SetDlgItemText(IDC_EDIT4, port_name);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDriverInstallDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDriverInstallDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDriverInstallDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDriverInstallDlg::OnOK() 
{
	if (this->IsPrinterExists((LPCTSTR)printer_name)){
		if (MessageBox( "打印机已经"+printer_name+"安装,是否继续", "错误", MB_YESNO| MB_ICONQUESTION)==IDNO)
			return;
	}
	typedef BOOL (WINAPI *pPrintUIEntry)(HWND, HMODULE, wchar_t *, DWORD);

	// TODO: Add extra validation here
	if (!CheckFile((LPSTR)(LPCTSTR)reg_file))
	{
		MessageBox( "注册表文件"+reg_file+"不存在!", "错误", MB_OK| MB_ICONERROR);

		return;
	}

	if (!CheckFile((LPSTR)(LPCTSTR)driver_info_path))
	{
		MessageBox( "驱动"+driver_info_path+"不存在!", "错误", MB_OK| MB_ICONERROR);
		return;
	}


	string output ;
	string command;

	CString cmd0;
	cmd0.Format("regedit.exe /s %s", reg_file);
	system((LPCTSTR) cmd0);
	
	CString arg_string;
	arg_string.Format("rundll32.exe printui.dll,PrintUIEntry /if /b \"%s\" /m \"%s\" /h\"x86\" /v \"windows 7\" /f \"%s\" /r %s", printer_name, driver_name, driver_info_path, port_name );

	if (system(arg_string)==0){

	}



// 	if (execCmd((LPCTSTR)commandFile, output )!=0){
// 		MessageBox( output.c_str(), "错误", MB_OK| MB_ICONERROR);
// 		return;
// 	}

	
// 	HINSTANCE  m = LoadLibrary("printui.dll");
// 	FARPROC printuientry = GetProcAddress(m, "PrintUIEntryW");
// 	char arg_string[8192];
// 	memset(arg_string, '\0', sizeof(arg_string));
// 	printuientry(NULL, m, arg_string, SW_SHOW);

//	HINSTANCE printuiDll = LoadLibrary("printui.dll");
// 	
// 	if (printuiDll == NULL)
// 	{
// 		printf("Error LoadLibrary %d.\n", GetLastError());
// 		
// 		return ;
// 	}
// 	
// 	pPrintUIEntry PrintUIEntry = (pPrintUIEntry) GetProcAddress(printuiDll, "PrintUIEntryW");
// 	
// 	if (PrintUIEntry == NULL)
// 	{
// 		printf("Error GetProcAddress %d.\n", GetLastError());
// 		
// 		return ;
// 	}
// 	//cmd is /ia /m "Printer" /f "C:\Program Files x86)\\drivers\Printer\Printer.inf
// 	char arg_string[8192];
// 	memset(arg_string, '\0', sizeof(arg_string));
// 
// //	string cmd;
// //	cmd = "/if /b \""+printer_name+"\" /m \""+"\" /h\"x86\" /v \"windows 7\" /f \""+driver_info_path+"\" /r \""+port_name+"\"";
// 
// 	CString cmd1;
// 	cmd1.Format("/if /b \"%s\" /m \"%s\" /h\"x86\" /v \"windows 7\" /f \"%s\" /r \"%s\"", printer_name, driver_name, driver_info_path, port_name );
// 	 // /if /b "%printer_name%" /m "%driver_name%" /h"x86" /v "windows 7" /f "%driver_path%" /r "%port_name%"
// 	if (PrintUIEntry(GetDesktopWindow()->GetSafeHwnd(), printuiDll, (wchar_t *)(LPCTSTR)cmd1, SW_SHOW))
// 	{
// 		sprintf(arg_string, "Error PrintUIEntry %d.", GetLastError());
// 		MessageBox(arg_string);
// 		//printf("Error PrintUIEntry %d.", GetLastError());
// 		
// 		return ;
// 	}
	
}


int CDriverInstallDlg::execCmd(const char* cmd, std::string& result){
	const int bufferLen = 2048;
    FILE* pipe = _popen(cmd, "r");
    if(!pipe){
		CString msg ;
		msg.Format("popen error, error code:%d", ::GetLastError());
        printf((LPCTSTR)msg);
        return -1;
    }
    size_t ret = 0;
    char buf[bufferLen];
	memset(buf, '\0', sizeof(buf));
    while ((ret = fread(buf, sizeof(char),bufferLen, pipe)) == bufferLen){
        result.append(buf);
    }
    if(ferror(pipe) != 0) {
        printf("read pipe error");
        return -1;
    }
    if(feof(pipe) != 0) {
        printf("exec cmd:%s success");
        result.append(buf, ret);
    }

	_pclose(pipe);

    return 0;
}


BOOL CDriverInstallDlg::IsRunAsAdmin()
{
//	BOOL fIsRunAsAdmin = FALSE;DWORD dwError = ERROR_SUCCESS;PSID pAdministratorsGroup = NULL;SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;if (!AllocateAndInitializeSid(&NtAuthority, 2,SECURITY_BUILTIN_DOMAIN_RID,DOMAIN_ALIAS_RID_ADMINS,0, 0, 0, 0, 0, 0,&pAdministratorsGroup)){dwError = GetLastError();goto Cleanup;}if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin)){dwError = GetLastError();goto Cleanup;} Cleanup:if (pAdministratorsGroup){FreeSid(pAdministratorsGroup);pAdministratorsGroup = NULL;}if (ERROR_SUCCESS != dwError){throw dwError;}return fIsRunAsAdmin;
	return true;

}

BOOL CDriverInstallDlg::IsPrinterExists(const char * printer_name)
{

	HANDLE hPrinter=0;
	DWORD dwNeeded=0;
	PRINTER_INFO_2* pPrinterInfo= (PRINTER_INFO_2 *)malloc( 0 );
	
	BOOL ret = ::OpenPrinter((LPSTR)printer_name,&hPrinter,NULL);
	if (ret==0){
		return false;
	}else{
		::ClosePrinter(hPrinter);
	}
	return true;

}