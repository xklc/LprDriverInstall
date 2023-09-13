; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDriverInstallDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DriverInstall.h"

ClassCount=4
Class1=CDriverInstallApp
Class2=CDriverInstallDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DRIVERINSTALL_DIALOG

[CLS:CDriverInstallApp]
Type=0
HeaderFile=DriverInstall.h
ImplementationFile=DriverInstall.cpp
Filter=N

[CLS:CDriverInstallDlg]
Type=0
HeaderFile=DriverInstallDlg.h
ImplementationFile=DriverInstallDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=DriverInstallDlg.h
ImplementationFile=DriverInstallDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DRIVERINSTALL_DIALOG]
Type=1
Class=CDriverInstallDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_EDIT2,edit,1350631552
Control10=IDC_EDIT3,edit,1350631552
Control11=IDC_EDIT4,edit,1350631552

