/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_Includes.h
    \brief Include file for SDL and C++ Includes that many ZEngine files need.

    ZE_*.h files should only include this file and any other ZE_*.h files that they need, External Library or C/C++ Standard Library
    files should be included from within this file.
    $Id: ZE_Includes.h,v 1.21 2003/12/24 04:46:48 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_includes_h__
#define __ze_includes_h__

#include "ZE_Defines.h"

#include "SDL.h"
#if (GFX_BACKEND == ZE_OGL)
#include "SDL_opengl.h"
#endif
#ifdef USE_SDL_IMAGE
#include "SDL_image.h"
#endif
#ifdef USE_SDL_TTF
#include "SDL_ttf.h"
#endif
#ifdef USE_SDL_MIXER
#include "SDL_mixer.h"
#endif

#include "zlib/unzip.h"
#include "tinyxml/tinyxml.h"

#include <string>   //used frequently
#include <queue>    //used by ZEngine for ZErrors
#include <list>     //used by ZConfigFile
#include <fstream>  //used by ZConfigFile
#include <cctype>   //used in parsing
#include <cstdarg>  //used in FormatStr

#endif //__ze_includes_h__
