/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZImage.cpp <br>
Description: Implementation source file for core ZEngine Image Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZImage.cpp,v 1.1 2002/11/21 05:41:13 cozman Exp $<br>

    \file ZE_ZImage.cpp
    \brief Source file for ZImage.

    Implementation of ZImage, the basic Image class for ZEngine.
**/

#include "ZE_ZImage.h"

namespace ZE
{

ZImage::ZImage()
{
}

ZImage::ZImage(string filename)
{
    Open(filename);
}

ZImage::ZImage(SDL_Surface *surface)
{
    Attach(surface);
}

ZImage::ZImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
    OpenFromImage(img,x,y,w,h);
}

ZImage::~ZImage()
{
    Release();
}

void ZImage::Open(string filename)
{
    Release();
    rImage = rEngine->LoadImage(filename);
}

void ZImage::OpenFromImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
    Uint32 flags;
    SDL_Surface *screen = rEngine->GetDisplay();
    SDL_Rect rect;
    SDL_VideoInfo *videoInfo;

    Release();
    rImage.filename = "cut from image";

    //either set hardware or software surface//
    videoInfo = const_cast<SDL_VideoInfo*>(SDL_GetVideoInfo());

    if(videoInfo->hw_available)
        flags = SDL_HWSURFACE;
    else
        flags = SDL_SWSURFACE;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(!img)
        LogError("Invalid Parameter to ZImage::OpenFromImage: img==NULL");

    rImage.image = SDL_CreateRGBSurface(flags, rect.w, rect.h, rEngine->GetBPP(),
        screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if(!rImage.image)
        LogError(FormatStr("SDL_CreateRGBSurface failed in ZImage::OpenFromImage: %s",SDL_GetError()));

    SDL_BlitSurface(img,&rect,rImage.image,NULL);
}

void ZImage::Attach(SDL_Surface *surface)
{
    Release();
    rImage.filename = "attached";
    rImage.image = surface;
}

void ZImage::Release()
{
    rEngine->FreeImage(rImage);
}

void ZImage::SetAlpha(Uint8 alpha)
{
    SDL_Surface *temp=NULL;

    if(rImage.image)
    {
        if(SDL_SetAlpha(rImage.image, SDL_RLEACCEL|SDL_SRCALPHA, alpha) < 0)
            LogError("Invalid Call to SDL_SetAlpha.");
        else
        {
            //surface conversion//
            temp = rImage.image;
            rImage.image  = SDL_DisplayFormat(temp);
            if(rImage.image)
            {
                SDL_FreeSurface(temp);
                temp = NULL;
            }
            else    //can't convert (add error warning here?)
            {
                    LogError("Alpha surface conversion failed.");
                rImage.image = temp;
            }
        }
    }
    else
        LogError("ZImage not initialized in ZImage::SetAlpha.");
}

void ZImage::SetColorKey(Uint32 color)
{
    SDL_Surface *temp=NULL;

    if(rImage.image)
    {
        if(SDL_SetColorKey(rImage.image, SDL_RLEACCEL|SDL_SRCCOLORKEY, color) < 0)
            LogError("Invalid Call to SDL_SetColorKey.");
        else
        {
            //surface conversion//
            temp = rImage.image;
            rImage.image = SDL_DisplayFormat(temp);
            if(rImage.image)
            {
                SDL_FreeSurface(temp);
                temp = NULL;
            }
            else    //can't convert (add error warning here?)
            {
                LogError("Surface conversion failed.");
                rImage.image = temp;
            }
        }
    }
    else
        LogError("ZImage not initialized in ZImage::SetColorKey.");
}

void ZImage::Draw(Sint16 x, Sint16 y)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;

    if(rImage.image)
        SDL_BlitSurface(rImage.image,NULL,rEngine->GetDisplay(),&rect);
    else
        LogError("ZImage not initialized in ZImage::Draw.");
}

bool ZImage::IsLoaded()
{
    return rImage.image != NULL;
}

SDL_Surface *ZImage::GetImage()
{
    return rImage.image;
}

int ZImage::GetWidth()
{
    if(rImage.image)
        return rImage.image->w;
    else
    {
        LogError("ZImage not initialized in ZImage::GetWidth.");
        return 0;
    }
}

int ZImage::GetHeight()
{
    if(rImage.image)
        return rImage.image->h;
    else
    {
        LogError("ZImage not initialized in ZImage::GetHeight.");
        return 0;
    }
}

string ZImage::GetFilename()
{
    return rImage.filename.c_str();
}

}
