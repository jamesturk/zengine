/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Macros.h <br>
Description: Header file for ZEngine Macros. <br>
Author(s): James Turk <br>
$Id: ZE_Macros.h,v 1.2 2002/12/03 04:11:41 cozman Exp $<br>

    \file ZE_Macros.h
    \brief Definition file for ZEngine Macros

    Definition file for ZEngine Macros which are used throughout the engine.
**/

#ifndef __ze_macros_h__
#define __ze_macros_h__

#include "ZE_Includes.h"

namespace ZE
{

#define FreeImage(image) if(image){SDL_FreeSurface(image); image = NULL;}

#ifdef USE_SDL_MIXER
#define FreeSound(sound) if(sound){Mix_FreeChunk(sound); sound = NULL;}
#define FreeMusic(music) if(music){Mix_FreeMusic(music); music = NULL;}
#endif

#ifdef USE_SDL_TTF
#define FreeFont(font) if(font){TTF_CloseFont(font); font = NULL;}
#endif


}

#endif //__ze_macros_h__

