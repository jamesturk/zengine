/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

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

#if SND_BACKEND == ZE_MIXER
#include "SDL_mixer.h"
#elif SND_BACKEND == ZE_AUDIERE
#include "audiere.h"
#endif

#include "zlib/unzip.h"
#include "tinyxml/tinyxml.h"

#include <string>   //used frequently
#include <queue>    //used by ZEngine for ZErrors
#include <list>     //used by ZConfigFile
#include <fstream>  //used by ZConfigFile
#include <cctype>   //used in parsing
#include <ctime>    //used in Randgen
#include <cstdarg>  //used in FormatStr

#endif //__ze_includes_h__
