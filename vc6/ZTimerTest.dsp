# Microsoft Developer Studio Project File - Name="ZTimerTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ZTimerTest - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZTimerTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZTimerTest.mak" CFG="ZTimerTest - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZTimerTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZTimerTest - Win32 Release"

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
# ADD BASE CPP /nologo /MD /I "../include" /Zi /W3 /O2 /Ob1 /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "../include" /Zi /W3 /O2 /Ob1 /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\test\bin\ZTimerTest.exe" /incremental:no /libpath:"../lib" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 sdl.lib
sdlmain.lib
opengl32.lib
sdl_ttf.lib
sdl_mixer.lib
sdl_image.lib
ZEngineS.lib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\test\bin\ZTimerTest.exe" /incremental:no /libpath:"../lib" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 sdl.lib
sdlmain.lib
opengl32.lib
sdl_ttf.lib
sdl_mixer.lib
sdl_image.lib
ZEngineS.lib

!ENDIF

# Begin Target

# Name "ZTimerTest - Win32 Release"
# Begin Source File

SOURCE=..\test\ZTimerTest.cpp
# End Source File
# End Target
# End Project

