/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_Utility.cpp
    \brief Source file for ZEngine utility functions.

    Source file containing open utilities for use inside and alongside ZEngine.
    <br>$Id: ZE_Utility.cpp,v 1.11 2003/09/24 02:03:18 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_Utility.h"

namespace ZE
{

std::string FormatStr(const char *fmtstr, ...)
{
    char buf[512];
    va_list args;
    //simply puts args into the buffer using standard parsing rules
    va_start(args,fmtstr);
    vsprintf(buf, fmtstr, args);
    va_end(args);
    return buf;
}

SDL_RWops* RWFromZip(std::string zipname, std::string filename)
{
    unzFile zip = unzOpen(zipname.c_str());
    unz_file_info info;
    void *buffer;

    if(!zip)    //failed to open zip
    {
        //log error
        return NULL;
    }

    //locate the file and open it (last param means case sensitive comparison)
    unzLocateFile(zip,filename.c_str(),0);
    if(unzOpenCurrentFile(zip) != UNZ_OK)   //failed to open file within zip
    {
        return NULL;
    }

    //find current file info (we are looking for uncompressed file size)
    unzGetCurrentFileInfo(zip,&info,NULL,0,NULL,0,NULL,0);

    //create a buffer big enough to hold uncompressed file in memory
    buffer = (void*)new char[info.uncompressed_size];
    if(!buffer)
    {
        unzCloseCurrentFile(zip);
        unzClose(zip);
        //log error (failed to allocate memory?!)
        return NULL;
    }

    //load into memory
    unzReadCurrentFile(zip, buffer, info.uncompressed_size);

    //close archive
    unzCloseCurrentFile(zip);
    unzClose(zip);

    return SDL_RWFromMem(buffer, info.uncompressed_size);   //return buffer in RW form
}

//Each of the Free*s safely frees & NULLs the pointer
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

