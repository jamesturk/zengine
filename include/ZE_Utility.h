/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Utility.h <br>
Description: Header file for ZEngine Utilities. <br>
Author(s): James Turk <br>
$Id: ZE_Utility.h,v 1.1 2003/01/15 05:31:51 cozman Exp $<br>

    \file ZE_Utility.h
    \brief Definition file for ZEngine Utilities.

    Definition file for ZEngine Utilities which are used throughout the engine and can be used in
    conjunction with ZEngine.
**/

#ifndef __ze_utility_h__
#define __ze_utility_h__

#include "ZE_Includes.h"

namespace ZE
{

/*! 
    \brief Parses a string and interprets variable arguments, similar to sprintf.

    Takes % identifiers out of fmtstr and parses them, replacing them with cooresponding values 
    in the variable arguments list.  For more detail view stdarg documentation.
    \param fmtstr defines format of resulting string
    \param ... variable number of arguments after fmtstr
    \return string of parsed and combined string
**/
string FormatStr(const char *fmtstr, ...);

//////////
//Macros//
//////////

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

#endif //__ze_utility_h__

