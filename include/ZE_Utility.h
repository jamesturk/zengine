/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_utility_h__
#define __ze_utility_h__

#include "ZE_Includes.h"

namespace ZE
{

std::string FormatStr(std::string fmtStr, ...);

SDL_RWops* RWFromZip(std::string zipname, std::string filename);

#if (GFX_BACKEND == ZE_OGL)
int PowerOfTwo(int num);
GLuint SurfaceToTexture(SDL_Surface *surface, GLfloat *texcoord);
#endif //GFX_BACKEND

void FreeImage(SDL_Surface *&image);

#ifdef USE_SDL_TTF
void FreeFont(TTF_Font *&font);
#endif

}

#endif //__ze_utility_h__

