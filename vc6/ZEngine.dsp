# Microsoft Developer Studio Project File - Name="ZEngine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ZEngine - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZEngine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZEngine.mak" CFG="ZEngine - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZEngine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
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
# ADD BASE CPP /nologo /MD /I "../include" /Zi /W4 /WX /O2 /Ob1 /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /GF /Gy PRECOMP_VC7_TOBEREMOVED /c /GX 
# ADD CPP /nologo /MD /I "../include" /Zi /W4 /WX /O2 /Ob1 /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /GF /Gy PRECOMP_VC7_TOBEREMOVED /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\ZEngineS.lib" 
# ADD LIB32 /nologo /out:"..\lib\ZEngineS.lib" 

!ENDIF

# Begin Target

# Name "ZEngine - Win32 Release"
# Begin Group "Source Implementations"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm"
# Begin Source File

SOURCE=..\src\external\SDLGL_Util.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_Utility.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZClient.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZConfigFile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZError.cpp
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

!IF  "$(CFG)" == "ZEngine - Win32 Release"

# PROP Intermediate_Dir "$(IntDir)/$(InputName)1.obj"
# ADD CPP /nologo /Fo"$(IntDir)/$(InputName)1.obj" /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZServer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZSound.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ZE_ZTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\external\mt19937ar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\external\physfsrwops.cpp
# End Source File
# End Group
# Begin Group "Source Headers"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc"
# Begin Source File

SOURCE=..\include\external\SDLGL_Util.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_Defines.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_Includes.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_Utility.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZClient.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZConfigFile.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZEngine.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZError.h
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

SOURCE=..\include\ZE_ZRect.h
# End Source File
# Begin Source File

SOURCE=..\include\ZE_ZServer.h
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
# Begin Source File

SOURCE=..\include\external\mt19937ar.h
# End Source File
# Begin Source File

SOURCE=..\include\external\physfsrwops.h
# End Source File
# End Group
# End Target
# End Project

