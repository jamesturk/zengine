# Microsoft Developer Studio Project File - Name="ZEngine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ZEngine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZEngine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZEngine.mak" CFG="ZEngine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZEngine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ZEngine - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZEngine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib\ZEngineS.lib"

!ELSEIF  "$(CFG)" == "ZEngine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../lib/ZEngine.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib\ZEngineSD.lib"

!ENDIF 

# Begin Target

# Name "ZEngine - Win32 Release"
# Name "ZEngine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\external\physfsrwops.cpp
# End Source File
# Begin Source File

SOURCE=..\src\external\SDLGL_Util.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_Error.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZConfigFile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZFont.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZImage.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZMusic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZRect.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZSound.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZTimer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\external\physfsrwops.h
# End Source File
# Begin Source File

SOURCE=..\include\external\SDLGL_Util.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_Defines.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_Error.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_Includes.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_Macros.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZConfigFile.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZEngine.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZFont.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZImage.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZMusic.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZObject.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZRect.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZSound.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZTimer.h
# End Source File
# Begin Source File

SOURCE=..\include\ZEngine.h
# End Source File
# End Group
# End Target
# End Project
