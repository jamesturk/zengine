/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Includes.h <br>
Description: Header file for ZEngine universal includes. <br>
Author(s): James Turk <br>
$Id: ZE_Includes.h,v 1.5 2003/01/13 05:53:47 cozman Exp $<br>

    \file ZE_Includes.h
    \brief Include file for SDL and C++ Includes that many ZEngine files need.

    ZE_*.h files should only include this file and any other ZE_*.h files that they need, External Library or C/C++ Standard Library
    files should be included from within this file.
**/

#ifndef __ze_includes_h__
#define __ze_includes_h__

#include "ZE_Defines.h"

#include "SDL.h"
#include "SDL_opengl.h"
#include "external/SDLGL_Util.h"
#ifdef USE_SDL_IMAGE
#include "SDL_image.h"
#endif
#ifdef USE_SDL_TTF
#include "SDL_ttf.h"
#endif
#ifdef USE_SDL_MIXER
#include "SDL_mixer.h"
#endif
#ifdef USE_PHYSFS
#include "physfs.h"
#include "external/physfsrwops.h"
#endif

#include <string>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cctype>
using namespace std;

#endif //__ze_includes_h__
