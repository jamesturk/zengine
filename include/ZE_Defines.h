/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header:
File: ZE_Defines.h <br>
Description: Defines header file for ZEngine class, where all #define statements to control compilation options are placed. <br>
Author(s): James Turk <br>
$Id: ZE_Defines.h,v 1.6 2003/01/13 05:48:47 cozman Exp $<br>

    \file ZE_Defines.h
    \brief Define file for ZEngine.

    Definition file, holds #define statements describing optional features of ZEngine.
**/

#ifndef __ze_defines_h__
#define __ze_defines_h__

//defines- undefine any of these if you dont have the indicated SDL extension//
//! Define to include OpenGL support (MUST be defined, may become optional in future)
#define USE_OPENGL
//! Define to include font support.
#define USE_SDL_TTF
//! Define to include non-bmp image file support.
#define USE_SDL_IMAGE
//! Define to include sound support.
#define USE_SDL_MIXER
//! Define to use the Physfs file system.
//#define USE_PHYSFS
//! Version number.
#define VERSION "0.8.2"

#endif //__ze_defines_h__
