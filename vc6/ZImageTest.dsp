# Microsoft Developer Studio Project File - Name="ZImageTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ZImageTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZImageTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZImageTest.mak" CFG="ZImageTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZImageTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ZImageTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZImageTest - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /GZ PRECOMP_VC7_TOBEREMOVED /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /GZ PRECOMP_VC7_TOBEREMOVED /c
# ADD BASE MTL /nologo /win32
# ADD MTL /nologo /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdl.lib sdlmain.lib opengl32.lib sdl_ttf.lib sdl_mixer.lib sdl_image.lib physfs.lib ZEngineSD.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"..\test\bin\ZImageTestD.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdl.lib sdlmain.lib opengl32.lib sdl_ttf.lib sdl_mixer.lib sdl_image.lib  ZEngineSD.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"..\test\bin\ZImageTestD.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ZImageTest - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /GF PRECOMP_VC7_TOBEREMOVED /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /GF PRECOMP_VC7_TOBEREMOVED /c
# ADD BASE MTL /nologo /win32
# ADD MTL /nologo /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdl.lib sdlmain.lib opengl32.lib sdl_ttf.lib sdl_mixer.lib sdl_image.lib physfs.lib ZEngineS.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"..\test\bin\ZImageTest.exe" /pdbtype:sept /opt:ref /opt:icf
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib sdl.lib sdlmain.lib opengl32.lib sdl_ttf.lib sdl_mixer.lib sdl_image.lib ZEngineS.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"..\test\bin\ZImageTest.exe" /pdbtype:sept /opt:ref /opt:icf

!ENDIF 

# Begin Target

# Name "ZImageTest - Win32 Debug"
# Name "ZImageTest - Win32 Release"
# Begin Source File

SOURCE=..\test\ZImageTest.cpp
DEP_CPP_ZIMAG=\
	{$(INCLUDE)}"begin_code.h"\
	{$(INCLUDE)}"close_code.h"\
	{$(INCLUDE)}"external\physfsrwops.h"\
	{$(INCLUDE)}"external\SDLGL_Util.h"\
	{$(INCLUDE)}"SDL.h"\
	{$(INCLUDE)}"SDL_active.h"\
	{$(INCLUDE)}"SDL_audio.h"\
	{$(INCLUDE)}"SDL_byteorder.h"\
	{$(INCLUDE)}"SDL_cdrom.h"\
	{$(INCLUDE)}"SDL_error.h"\
	{$(INCLUDE)}"SDL_events.h"\
	{$(INCLUDE)}"SDL_getenv.h"\
	{$(INCLUDE)}"SDL_image.h"\
	{$(INCLUDE)}"SDL_joystick.h"\
	{$(INCLUDE)}"SDL_keyboard.h"\
	{$(INCLUDE)}"SDL_keysym.h"\
	{$(INCLUDE)}"SDL_main.h"\
	{$(INCLUDE)}"SDL_mixer.h"\
	{$(INCLUDE)}"SDL_mouse.h"\
	{$(INCLUDE)}"SDL_mutex.h"\
	{$(INCLUDE)}"SDL_opengl.h"\
	{$(INCLUDE)}"SDL_quit.h"\
	{$(INCLUDE)}"SDL_rwops.h"\
	{$(INCLUDE)}"SDL_timer.h"\
	{$(INCLUDE)}"SDL_ttf.h"\
	{$(INCLUDE)}"SDL_types.h"\
	{$(INCLUDE)}"SDL_version.h"\
	{$(INCLUDE)}"SDL_video.h"\
	{$(INCLUDE)}"ZE_Defines.h"\
	{$(INCLUDE)}"ZE_Error.h"\
	{$(INCLUDE)}"ZE_Includes.h"\
	{$(INCLUDE)}"ZE_Macros.h"\
	{$(INCLUDE)}"ZE_ZConfigFile.h"\
	{$(INCLUDE)}"ZE_ZEngine.h"\
	{$(INCLUDE)}"ZE_ZFont.h"\
	{$(INCLUDE)}"ZE_ZImage.h"\
	{$(INCLUDE)}"ZE_ZMusic.h"\
	{$(INCLUDE)}"ZE_ZObject.h"\
	{$(INCLUDE)}"ZE_ZRect.h"\
	{$(INCLUDE)}"ZE_ZSound.h"\
	{$(INCLUDE)}"ZE_ZTimer.h"\
	{$(INCLUDE)}"ZEngine.h"\
	
NODEP_CPP_ZIMAG=\
	"..\include\physfs.h"\
	
# End Source File
# End Target
# End Project
