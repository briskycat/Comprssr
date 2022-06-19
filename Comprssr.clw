; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCompressorDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Comprssr.h"
LastPage=0

ClassCount=13
Class1=CCompressorApp
Class2=CCompressorDoc
Class3=CCompressorView
Class4=CMainFrame

ResourceCount=10
Resource1=IDR_MAINFRAME
Resource2=IDR_TBANALYSIS
Resource3=IDR_COMPRSTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDD_DBADJUSTMENT
Class7=CSQLRequestView
Class8=CDataView
Class9=CAnalysisView
Resource5=IDD_ANALYSERSETTINGS
Class10=CDBInfo
Resource6=IDR_TBCOMPRESSION
Resource7=IDD_DBINFO
Class11=CAnalyserSettings
Class12=CCompressionView
Resource8=IDD_ABOUTBOX
Resource9=IDR_TBDBASE
Class13=CDBAdjustment
Resource10=IDR_MAINFRAME (English (U.S.))

[CLS:CCompressorApp]
Type=0
HeaderFile=Comprssr.h
ImplementationFile=Comprssr.cpp
Filter=N

[CLS:CCompressorDoc]
Type=0
HeaderFile=CprsDoc.h
ImplementationFile=CprsDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_OUTPUTDBINFO

[CLS:CCompressorView]
Type=0
HeaderFile=CprsView.h
ImplementationFile=CprsView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=Comprssr.cpp
ImplementationFile=Comprssr.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_COMPRSTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_STATUS_BAR
Command16=ID_OPENDBASE
Command17=ID_DBASEINFO
Command18=ID_VIEWDB
Command19=ID_VIEWDOC
Command20=ID_EXECREQUEST
Command21=ID_ANALYZE
Command22=ID_ANALYSERSETTINGS
Command23=ID_WINDOW_NEW
Command24=ID_WINDOW_CASCADE
Command25=ID_WINDOW_TILE_HORZ
Command26=ID_WINDOW_ARRANGE
Command27=ID_APP_ABOUT
CommandCount=27

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CSQLRequestView]
Type=0
HeaderFile=SQLReqVw.h
ImplementationFile=SQLReqVw.cpp
BaseClass=CEditView
Filter=W
LastObject=CSQLRequestView
VirtualFilter=VWC

[CLS:CDataView]
Type=0
HeaderFile=DataView.h
ImplementationFile=DataView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CDataView

[CLS:CAnalysisView]
Type=0
HeaderFile=Analysis.h
ImplementationFile=Analysis.cpp
BaseClass=CView
Filter=C
LastObject=CAnalysisView
VirtualFilter=VWC

[TB:IDR_TBDBASE]
Type=1
Class=?
Command1=ID_OPENDBASE
Command2=ID_DBASEINFO
Command3=ID_VIEWDB
Command4=ID_VIEWDOC
Command5=ID_EXECREQUEST
CommandCount=5

[DLG:IDD_DBINFO]
Type=1
Class=CDBInfo
ControlCount=2
Control1=IDC_TABLELIST,listbox,1352728835
Control2=IDC_STATIC,static,1342308352

[CLS:CDBInfo]
Type=0
HeaderFile=DBInfo.h
ImplementationFile=DBInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_TABLELIST

[TB:IDR_TBANALYSIS]
Type=1
Class=?
Command1=ID_ANALYZE
Command2=ID_ANALYSERSETTINGS
CommandCount=2

[DLG:IDD_ANALYSERSETTINGS]
Type=1
Class=CAnalyserSettings
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_INFFACTOR,edit,1350631552

[CLS:CAnalyserSettings]
Type=0
HeaderFile=AlsrSet.h
ImplementationFile=AlsrSet.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CCompressionView]
Type=0
HeaderFile=CprnView.h
ImplementationFile=CprnView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CCompressionView

[TB:IDR_TBCOMPRESSION]
Type=1
Class=?
Command1=ID_OPENOUTPUTDB
Command2=ID_OUTPUTDBINFO
Command3=ID_OUTPUTDBADJUSTMENT
Command4=ID_INITCOMPRESSOR
Command5=ID_COMPRESS
Command6=ID_DECOMPRESS
Command7=ID_SAVEPROCESSEDDATA
CommandCount=7

[DLG:IDD_DBADJUSTMENT]
Type=1
Class=CDBAdjustment
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TABLENAME,edit,1350631552

[CLS:CDBAdjustment]
Type=0
HeaderFile=DBAdj.h
ImplementationFile=DBAdj.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TABLENAME
VirtualFilter=dWC

