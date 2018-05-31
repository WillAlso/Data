; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demo.h"

ClassCount=3
Class1=CDemoApp
Class2=CDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DEMO_DIALOG

[CLS:CDemoApp]
Type=0
HeaderFile=demo.h
ImplementationFile=demo.cpp
Filter=N

[CLS:CDemoDlg]
Type=0
HeaderFile=demoDlg.h
ImplementationFile=demoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDemoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=demoDlg.h
ImplementationFile=demoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DEMO_DIALOG]
Type=1
Class=CDemoDlg
ControlCount=7
Control1=IDC_SHOW_BUTTON,button,1342242817
Control2=IDC_EXIT_BUTTON,button,1342242816
Control3=IDC_NAME_COMBO,combobox,1344471043
Control4=IDC_FAVORATE_COMBO,combobox,1344340227
Control5=IDC_SHOW_EDIT,edit,1350631552
Control6=IDC_STATIC,static,1342308865
Control7=IDC_STATIC,static,1342308865

