/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Macros.h <br>
Description: Header file for ZEngine Macros. <br>
Author(s): James Turk <br>
$Id: ZE_Macros.h,v 1.4 2002/12/29 06:50:19 cozman Exp $<br>

    \file ZE_Macros.h
    \brief Definition file for ZEngine Macros

    Definition file for ZEngine Macros which are used throughout the engine.
**/

#ifndef __ze_macros_h__
#define __ze_macros_h__

#include "ZE_Includes.h"

namespace ZE
{

/*!
    Safely free an SDL_Surface* and set it to NULL.
**/
#define FreeImage(image) if(image){SDL_FreeSurface(image); image = NULL;}

#ifdef USE_SDL_MIXER
/*!
    Safely free a Mix_Chunk* and set it to NULL.
**/
#define FreeSound(sound) if(sound){Mix_FreeChunk(sound); sound = NULL;}
/*!
    Safely free a Mix_Music* and set it to NULL.
**/
#define FreeMusic(music) if(music){Mix_FreeMusic(music); music = NULL;}
#endif

#ifdef USE_SDL_TTF
/*!
    Safely free a TTF_Font and set it to NULL.
**/
#define FreeFont(font) if(font){TTF_CloseFont(font); font = NULL;}
#endif


}

#endif //__ze_macros_h__

