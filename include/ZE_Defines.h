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
$Id: ZE_Defines.h,v 1.11 2003/04/08 03:33:10 cozman Exp $<br>

    \file ZE_Defines.h
    \brief Define file for ZEngine.

    Definition file, holds #define statements describing optional features of ZEngine.
**/

#ifndef __ze_defines_h__
#define __ze_defines_h__

//Defines- undefine any of these if you dont have the indicated SDL extension//

//! Version number.
#define VERSION "0.8.3-pre"

//! Define to include font support.
#define USE_SDL_TTF
//! Define to include non-bmp image file support.
#define USE_SDL_IMAGE
//! Define to include sound support.
#define USE_SDL_MIXER
//! Define to include net support.
#define USE_SDL_NET
//! Define to use the Physfs file system.
//#define USE_PHYSFS

//! Maximum message length (for SDL_net). (10kb [10240] default)
#define MAX_MSG_LEN 10240
//! Define a ZByte as a plain char (for SDL_net).
typedef char ZByte;

#endif //__ze_defines_h__
