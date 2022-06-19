# Microsoft Developer Studio Project File - Name="Comprssr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Comprssr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Comprssr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Comprssr.mak" CFG="Comprssr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Comprssr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Comprssr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Od /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Comprssr - Win32 Release"
# Name "Comprssr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlsrSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Analyser.cpp
# End Source File
# Begin Source File

SOURCE=.\Analysis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Comprssr.cpp
# End Source File
# Begin Source File

SOURCE=.\Comprssr.rc
# End Source File
# Begin Source File

SOURCE=.\CprnView.cpp
# End Source File
# Begin Source File

SOURCE=.\CprsDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DataView.cpp
# End Source File
# Begin Source File

SOURCE=.\DBAdj.cpp
# End Source File
# Begin Source File

SOURCE=.\DBInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLReqVw.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlsrSet.h
# End Source File
# Begin Source File

SOURCE=.\Analyser.h
# End Source File
# Begin Source File

SOURCE=.\Analysis.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Comprssr.h
# End Source File
# Begin Source File

SOURCE=.\CprnView.h
# End Source File
# Begin Source File

SOURCE=.\CprsDoc.h
# End Source File
# Begin Source File

SOURCE=.\DataView.h
# End Source File
# Begin Source File

SOURCE=.\DBAdj.h
# End Source File
# Begin Source File

SOURCE=.\DBInfo.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SQLReqVw.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\types.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Comprssr.ico
# End Source File
# Begin Source File

SOURCE=.\res\Comprssr.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CprsDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\dbasetb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tbanal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tbcmprsn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tbdbase.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "3rd Party"

# PROP Default_Filter ""
# Begin Group "ODBCRecordset"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ODBCRs\ODBCRecordset.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Newmat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\newmat\BANDMAT.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\CHOLESKY.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\EVALUE.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\FFT.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\HHOLDER.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\JACOBI.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\MYEXCEPT.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT1.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT2.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT3.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT4.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT5.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT6.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT7.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT8.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMAT9.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMATEX.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMATNL.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\NEWMATRM.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\SOLUTION.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\SORT.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\SUBMAT.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newmat\SVD.CPP

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug\newmat"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "3DTabView"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3dTabVws\OX3DTabView.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3dTabVws\OX3DTabView.h

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3dTabVws\OXTabClientWnd.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "GridCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GridCtrl\GridCell.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCellBase.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.h

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridDropTarget.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceEdit.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GridCtrl\TitleTip.cpp

!IF  "$(CFG)" == "Comprssr - Win32 Release"

# PROP Intermediate_Dir "Release"

!ELSEIF  "$(CFG)" == "Comprssr - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Graphics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Graphics\BarLine.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\Graphics.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\Graphics.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\Pie.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\Scatter.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\Comprssr.reg
# End Source File
# End Target
# End Project
