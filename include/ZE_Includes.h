/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Includes.h <br>
Description: Header file for ZEngine universal includes. <br>
Author(s): James Turk <br>
$Id: ZE_Includes.h,v 1.2 2002/11/28 23:18:54 cozman Exp $<br>

    \file ZE_Includes.h
    \brief Include file for SDL and C++ Includes that many ZEngine files need.

    ZE_*.h files should only include this file and any other ZE_*.h files that they need, External Library or C/C++ Standard Library
    files should be included from within this file.
**/

#ifndef __ze_includes_h__
#define __ze_includes_h__

#include "ZE_Defines.h"

#include "SDL.h"
#ifdef USE_OPENGL_2D
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
#ifdef USE_PHYSFS
#include "physfs.h"
#include "external/physfsrwops.h"
#endif

#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cctype>
using namespace std;

#endif //__ze_includes_h__
