/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header:
File: ZE_Utility.cpp <br>
Description: Implementation source file for ZEngine Utilities. <br>
Author(s): James Turk <br>
$Id: ZE_Utility.cpp,v 1.5 2003/04/28 02:01:20 cozman Exp $<br>

    \file ZE_Utility.cpp
    \brief Source file for ZEngine utility functions.

    Source file containing open utilities for use inside and alongside ZEngine.
**/

#include "ZE_Utility.h"

namespace ZE
{

string FormatStr(const char *fmtstr, ...)
{
    char buf[512];
    va_list args;

    va_start(args,fmtstr);
    vsprintf(buf, fmtstr, args);
    va_end(args);
    return buf;
}

void FreeImage(SDL_Surface *&image)
{
    if(image)
    {
        SDL_FreeSurface(image);
        image = NULL;
    }
}

#ifdef USE_SDL_MIXER

void FreeSound(Mix_Chunk *&chunk)
{
    if(chunk)
    {
        Mix_FreeChunk(chunk);
        chunk = NULL;
    }
}

void FreeMusic(Mix_Music *&music)
{
    if(music)
    {
        Mix_FreeMusic(music);
        music = NULL;
    }
}

#endif 

#ifdef USE_SDL_TTF

void FreeFont(TTF_Font *&font)
{
    if(font)
    {
        TTF_CloseFont(font);
        font = NULL;
    }
}

#endif

}

