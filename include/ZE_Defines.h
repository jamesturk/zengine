/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_Defines.h
    \brief Define file for ZEngine where all #define statements to control compilation options are placed.

    Definition file, holds #define statements describing optional features of ZEngine.
    <br>$Id: ZE_Defines.h,v 1.25 2003/11/23 19:31:24 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_defines_h__
#define __ze_defines_h__

//Defines- undefine any of these if you dont have the indicated SDL extension//

//! OpenGL 2D Rendering Target.
#define ZE_OGL (1)
//! SDL Rendering Target.
#define ZE_SDL (2)
//! Define the graphics backend for ZEngine to use. (Options are ZE_OGL,ZE_SDL,ZE_D3D)
#define GFX_BACKEND (ZE_OGL)

//! Define to include font support.
#define USE_SDL_TTF
//! Define to include non-bmp image file support.
#define USE_SDL_IMAGE
//! Define to include sound support.
#define USE_SDL_MIXER
//! Define to use depreciated code that has not been entirely removed.
//#define DEPRECIATED

#endif //__ze_defines_h__
