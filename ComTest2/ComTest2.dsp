# Microsoft Developer Studio Project File - Name="ComTest2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ComTest2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComTest2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComTest2.mak" CFG="ComTest2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComTest2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ComTest2 - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "ComTest2 - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "ComTest2 - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "ComTest2 - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "ComTest2 - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComTest2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\usr\local\bin"
# PROP Intermediate_Dir "..\bin\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=\usr\local\bin
TargetPath=\usr\local\bin\ComTest2.exe
InputPath=\usr\local\bin\ComTest2.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\usr\local\bin"
# PROP Intermediate_Dir "..\bin\DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=\usr\local\bin
TargetPath=\usr\local\bin\ComTest2.exe
InputPath=\usr\local\bin\ComTest2.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\usr\local\bin"
# PROP Intermediate_Dir "..\bin\ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=\usr\local\bin
TargetPath=\usr\local\bin\ComTest2.exe
InputPath=\usr\local\bin\ComTest2.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\usr\local\bin"
# PROP Intermediate_Dir "..\bin\ReleaseMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=\usr\local\bin
TargetPath=\usr\local\bin\ComTest2.exe
InputPath=\usr\local\bin\ComTest2.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\usr\local\bin"
# PROP Intermediate_Dir "..\bin\ReleaseUMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=\usr\local\bin
TargetPath=\usr\local\bin\ComTest2.exe
InputPath=\usr\local\bin\ComTest2.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\usr\local\bin"
# PROP Intermediate_Dir "..\bin\ReleaseUMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=\usr\local\bin
TargetPath=\usr\local\bin\ComTest2.exe
InputPath=\usr\local\bin\ComTest2.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ComTest2 - Win32 Debug"
# Name "ComTest2 - Win32 Unicode Debug"
# Name "ComTest2 - Win32 Release MinSize"
# Name "ComTest2 - Win32 Release MinDependency"
# Name "ComTest2 - Win32 Unicode Release MinSize"
# Name "ComTest2 - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ComTest2.cpp
# End Source File
# Begin Source File

SOURCE=.\ComTest2.idl

!IF  "$(CFG)" == "ComTest2 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ComTest2.idl

BuildCmds= \
	midl /Oicf /h "ComTest2.h" /iid "ComTest2_i.c" "ComTest2.idl"

".\ComTest2.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Unicode Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ComTest2.idl

BuildCmds= \
	midl /Oicf /h "ComTest2.h" /iid "ComTest2_i.c" "ComTest2.idl"

".\ComTest2.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ComTest2.idl

BuildCmds= \
	midl /Oicf /h "ComTest2.h" /iid "ComTest2_i.c" "ComTest2.idl"

".\ComTest2.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Release MinDependency"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ComTest2.idl

BuildCmds= \
	midl /Oicf /h "ComTest2.h" /iid "ComTest2_i.c" "ComTest2.idl"

".\ComTest2.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Unicode Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ComTest2.idl

BuildCmds= \
	midl /Oicf /h "ComTest2.h" /iid "ComTest2_i.c" "ComTest2.idl"

".\ComTest2.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComTest2 - Win32 Unicode Release MinDependency"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\ComTest2.idl

BuildCmds= \
	midl /Oicf /h "ComTest2.h" /iid "ComTest2_i.c" "ComTest2.idl"

".\ComTest2.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ComTest2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ComTest2.rc
# End Source File
# Begin Source File

SOURCE=.\CT2.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CT2.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ComTest2.rgs
# End Source File
# Begin Source File

SOURCE=.\CT2.rgs
# End Source File
# End Target
# End Project
