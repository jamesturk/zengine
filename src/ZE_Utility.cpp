/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_Utility.h"
#include "ZE_ZEngine.h" //needed for error log, can't be in ZE_Utility.h (circular dependency)

namespace ZE
{

std::string FormatStr(std::string fmtStr, ...)
{
    std::va_list args;
    char buf[1024];

    va_start(args,fmtStr);
    std::vsprintf(buf,fmtStr.c_str(),args);
    va_end(args);

    return buf;
}

int LoadFromZip(std::string zipname, std::string filename, void *&buffer)
{
    unzFile zip = unzOpen(zipname.c_str());
    unz_file_info info;
    
    buffer = NULL;  //start off buffer as NULL

    if(!zip)    //failed to open zip
    {
        ZEngine::GetInstance()->ReportError(ZERR_WARNING,"Could not open zipfile %s",zipname.c_str());
        return 0;
    }

    //locate the file and open it (last param means case sensitive comparison)
    unzLocateFile(zip,filename.c_str(),0);
    if(unzOpenCurrentFile(zip) != UNZ_OK)   //failed to open file within zip
    {
        return 0;    //error should reported in calling function
    }

    //find current file info (we are looking for uncompressed file size)
    unzGetCurrentFileInfo(zip,&info,NULL,0,NULL,0,NULL,0);

    //create a buffer big enough to hold uncompressed file in memory
    buffer = (void*)new char[info.uncompressed_size];
    if(!buffer)
    {
        unzCloseCurrentFile(zip);
        unzClose(zip);
        ZEngine::GetInstance()->ReportError(ZERR_ERROR,"RWFromZip failed to allocate enough memory for buffer while loading %s from %s.",filename.c_str(),zipname.c_str());
        return 0;
    }

    //load into memory
    unzReadCurrentFile(zip, buffer, info.uncompressed_size);

    //close archive
    unzCloseCurrentFile(zip);
    unzClose(zip);

    return info.uncompressed_size;  //return the buffer size
}

SDL_RWops* RWFromZip(std::string zipname, std::string filename)
{
    void *buffer;
    int bufSize;

    bufSize = LoadFromZip(zipname,filename,buffer);

    return SDL_RWFromMem(buffer,bufSize);
}

#if (GFX_BACKEND == ZE_OGL)

//from SDL's testgl.c power_of_two
int PowerOfTwo(int num)
{
    int value = 1;

    while(value < num) //texture coord must be >= input
        value <<= 1;     //value <<= 1 is the same as value *= 2
    return value;
}

//from SDL's testgl.c SDL_GL_LoadTexture
GLuint SurfaceToTexture(SDL_Surface *surface, GLfloat *texcoord)
{
    GLuint texture;
    int w, h;
    SDL_Surface *temp;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8  saved_alpha;

    //expand width and height to nearest powers of 2
    w = PowerOfTwo(surface->w);
    h = PowerOfTwo(surface->h);
    texcoord[0] = 0.0f; //min X
    texcoord[1] = 0.0f; //min Y
    texcoord[2] = (GLfloat)surface->w / w;  //max X
    texcoord[3] = (GLfloat)surface->h / h;  //max Y

    temp = SDL_CreateRGBSurface(
        SDL_SWSURFACE,
        w, h,
        32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN //endian specific color masks
        0x000000FF, 
        0x0000FF00, 
        0x00FF0000, 
        0xFF000000
#else
        0xFF000000,
        0x00FF0000, 
        0x0000FF00, 
        0x000000FF
#endif
    );
    if(!temp)  //failure in CreateRGBSurface
        return 0;

    //save alpha
    saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
        SDL_SetAlpha(surface, 0, 0);

    //copy surface (do not alter passed surface to allow this function to be used in special situations)
    area.x = 0;
    area.y = 0;
    area.w = static_cast<Sint16>(surface->w);
    area.h = static_cast<Sint16>(surface->h);
    SDL_BlitSurface(surface, &area, temp, &area);

    //restore saved alpha
    if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
        SDL_SetAlpha(surface, saved_flags, saved_alpha);

    //create the OpenGL texture
    glGenTextures(1, &texture); 
    //setup texture parmaters
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
    SDL_FreeSurface(temp); //temp surface no longer needed

    return texture;
}
#endif //GFX_BACKEND == ZE_OGL

//Each of the Free*s safely frees & NULLs the pointer
void FreeImage(SDL_Surface *&image)
{
    if(image)
    {
        SDL_FreeSurface(image);
        image = NULL;
    }
}

#if SND_BACKEND == ZE_MIXER

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

#endif //ZE_MIXER

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

