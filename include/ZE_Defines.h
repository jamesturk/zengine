/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header:
File: ZE_Defines.h <br>
Description: Defines header file for ZEngine class, where all #define statements to control compilation options are placed. <br>
Author(s): James Turk <br>
$Id: ZE_Defines.h,v 1.1 2002/11/21 05:41:10 cozman Exp $<br>

    \file ZE_Defines.h
    \brief Define file for ZEngine.

    Definition file, holds #define statements describing optional features of ZEngine.
**/

#ifndef __ze_defines_h__
#define __ze_defines_h__

//defines- undefine any of these if you dont have the indicated SDL extension//
//! Define to include font support.
#define USE_SDL_TTF
//! Define to include non-bmp image file support.
#define USE_SDL_IMAGE
//! Define to include sound support.
#define USE_SDL_MIXER
//! Define to use the Physfs file system.
//#define USE_PHYSFS
//! Undefine to disable debug streams for Error Handler.
#define DEBUG_STREAM
//! Version number.
#define VERSION "0.7.3"

#endif //__ze_defines_h__
