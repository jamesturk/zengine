/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_Utility.h
    \brief Definition file for ZEngine Utilities.

    Definition file for ZEngine Utilities which are used throughout the engine and can be used in
    conjunction with ZEngine.
    <br>$Id: ZE_Utility.h,v 1.6 2003/09/24 01:49:52 cozman Exp $<br>
    \author James Turk
**/


#ifndef __ze_utility_h__
#define __ze_utility_h__

#include "ZE_Includes.h"

namespace ZE
{

/*! 
    \brief Parses a std::string and interprets variable arguments, similar to sprintf.

    Takes % identifiers out of fmtstr and parses them, replacing them with cooresponding values 
    in the variable arguments list.  For more detail view stdarg documentation.
    \param fmtstr defines format of resulting std::string
    \param ... variable number of arguments after fmtstr
    \return std::string of parsed and combined std::string
**/
std::string FormatStr(const char *fmtstr, ...);

SDL_RWops* RWFromZip(std::string zipname, std::string filename);

/*!
    \brief Properly free SDL_Surface. 
    
    Safely free an SDL_Surface* and set it to NULL.
    \param image Image to free and set to NULL.
**/
void FreeImage(SDL_Surface *&image);

#ifdef USE_SDL_MIXER

/*!
    \brief Properly free Mix_Chunk. 
    
    Safely free a Mix_Chunk* and set it to NULL.
    \param chunk Chunk to free and set to NULL.
**/
void FreeSound(Mix_Chunk *&chunk);

/*!
    \brief Properly free Mix_Music.
    
    Safely free a Mix_Music* and set it to NULL.
    \param music Music to free and set to NULL.
**/
void FreeMusic(Mix_Music *&music);

#endif

#ifdef USE_SDL_TTF
/*!
    \brief Properly free TTF_Font. 
    
    Safely free a TTF_Font* and set it to NULL.
    \param font Font to free and set to NULL.
**/
void FreeFont(TTF_Font *&font);
#endif

}

#endif //__ze_utility_h__

