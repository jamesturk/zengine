/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_DataPtr.h <br>
Description: Header file for ZEngine Data Pointer Classes <br>
Author(s): James Turk <br>
$Id: ZE_DataPtr.h,v 1.1 2002/11/21 05:41:10 cozman Exp $<br>

    \file ZE_DataPtr.h
    \brief Definition file for ZEngine Data/Pointer Classes. ([Image,Font,Sound,Music]Data/Ptr)

    Definition file for ZEngine Data Pointer Classes. ([Image,Font,Sound,Music]Ptr) These classes are used to keep track of the Images (Fonts and Sounds) throughout 
    the entire ZEngine.
**/

#ifndef __ze_dataptr_h__
#define __ze_dataptr_h__

#include "ZE_Includes.h"

namespace ZE
{

///////////////////////////////////////////
//Utility Classes Used Throughout ZEngine//
///////////////////////////////////////////

/*!
    \brief Class to wrap SDL_Surface pointers.

    Class used to keep track of loaded data and associate an SDL_Surface with an index number and filename.
**/
class ImageData
{
    public:
        //! Pointer to SDL_Surface.
        SDL_Surface *image;
        //! File image was loaded from.
        string filename;
        /*!
            \brief Initialize ImageData.

            Sets image pointer to NULL
        **/
        ImageData() { image = NULL; };
};

#ifdef USE_SDL_TTF

/*!
    \brief Class to wrap TTF_Font pointers.

    Class used to keep track of loaded data and associate a TTF_Font with an index number and filename.
**/
class FontData
{
    public:
        //! Pointer to SDL_TTF font data.
        TTF_Font *font;
        //! File font was loaded from.
        string filename;
        /*!
            \brief Initialize FontData.

            Sets font pointer to NULL
        **/
        FontData() { font = NULL; };
};

#endif //USE_SDL_TTF

#ifdef USE_SDL_MIXER

/*!
    \brief Class to wrap Mix_Chunk pointers.

    Class used to keep track of loaded data and associate a Mix_Chunk with an index number and filename.
**/
class SoundData
{
    public:
        //! Pointer to SDL_Mixer sound effect data.
        Mix_Chunk *sound;
        //! File sound effect was loaded from.
        string filename;
        /*!
            \brief Initialize SoundData.

            Sets sound pointer to NULL
        **/
        SoundData() { sound = NULL; };
};

/*!
    \brief Class to wrap Mix_Music pointers.

    Class used to keep track of loaded data and associate a Mix_Music with an index number and filename.
**/
class MusicData
{
    public:
        //! Pointer to SDL_Mixer music data.
        Mix_Music *music;
        //! File music was loaded from.
        string filename;
        /*!
            \brief Initialize MusicData.

            Sets music pointer to NULL
        **/
        MusicData() { music = NULL; };
};

#endif //USE_SDL_MIXER

}

#endif //__ze_dataptr_h__
