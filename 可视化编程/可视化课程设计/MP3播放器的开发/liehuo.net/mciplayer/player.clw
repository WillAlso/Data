; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=listdlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "player.h"

ClassCount=4
Class1=CPlayerApp
Class2=CPlayerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=listdlg
Resource3=IDD_PLAYER_DIALOG

[CLS:CPlayerApp]
Type=0
HeaderFile=player.h
ImplementationFile=player.cpp
Filter=N
LastObject=CPlayerApp

[CLS:CAboutDlg]
Type=0
HeaderFile=playerDlg.h
ImplementationFile=playerDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EMAIL,static,1342308352

[DLG:IDD_PLAYER_DIALOG]
Type=1
Class=CPlayerDlg
ControlCount=13
Control1=IDC_PLAY,button,1342242955
Control2=IDC_OPEN,button,1342242955
Control3=IDC_STOP,button,1342242955
Control4=IDC_BHELP,button,1342242955
Control5=IDC_BMIM,button,1342242955
Control6=IDC_BEXIT,button,1342242955
Control7=IDC_SLIDER,msctls_trackbar32,1350631448
Control8=IDC_RP,button,1342242955
Control9=IDC_POP,button,1342242955
Control10=IDC_LIST,listbox,1352728833
Control11=IDC_PER,button,1342242955
Control12=IDC_NEXT,button,1342242955
Control13=IDC_SDEL,button,1342242955

[CLS:CPlayerDlg]
Type=0
HeaderFile=playerdlg.h
ImplementationFile=playerdlg.cpp
BaseClass=CDialog
LastObject=CPlayerDlg
Filter=D
VirtualFilter=dWC

[CLS:listdlg]
Type=0
HeaderFile=listdlg.h
ImplementationFile=listdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=listdlg
VirtualFilter=dWC

