/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZImage.cpp <br>
Description: Implementation source file for core ZEngine Image or Texture Object. <br>
Author(s): James Turk, Gamer Tazar <br>
$Id: ZE_ZImage.cpp,v 1.13 2003/01/08 06:07:06 cozman Exp $<br>

    \file ZE_ZImage.cpp
    \brief Source file for ZImage.

    Implementation of ZImage, the Image class for ZEngine.
**/

#include "ZE_ZImage.h"

namespace ZE
{

ZImage::ZImage()
{
    rImage = NULL;
    Release();
}

ZImage::ZImage(string filename)
{
    rImage = NULL;
    Open(filename);
}

ZImage::ZImage(SDL_Surface *surface)
{
    rImage = NULL;
    Attach(surface);
}

ZImage::ZImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
    rImage = NULL;
    OpenFromImage(img,x,y,w,h);
}

ZImage::~ZImage()
{
    Release();
}

void ZImage::Open(string filename)
{
    SDL_Surface *image;

    image = rEngine->LoadImage(filename.c_str());
    Attach(image);
}

void ZImage::OpenFromImage(SDL_Surface *image, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
    SDL_Surface *screen = rEngine->Display();
    SDL_Surface *cutImg = NULL;
    SDL_Rect rect;
    SDL_VideoInfo *videoInfo;

    //either set hardware or software surface//
    videoInfo = const_cast<SDL_VideoInfo*>(SDL_GetVideoInfo());

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(!image)
        LogError("Invalid Parameter to ZImage::OpenFromImage.");

    cutImg = SDL_CreateRGBSurface(0, rect.w, rect.h, rEngine->BPP(),
        screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if(!cutImg)
        LogError(FormatStr("SDL_CreateRGBSurface failed in ZImage::OpenFromImage."));

    SDL_BlitSurface(image,&rect,cutImg,NULL);
    Attach(cutImg);
}

void ZImage::Attach(SDL_Surface *surface)
{
    GLfloat coord[4];

	Release();		//avoid most memory leaks

    if(surface)
    {
        rWidth = surface->w;
        rHeight = surface->h;
        rTexID = SDL_GL_LoadTexture(surface,coord);
        rTexMinX = coord[0];
        rTexMinY = coord[1];
        rTexMaxX = coord[2];
        rTexMaxY = coord[3];
        rImage = surface;
    }
    else
        LogError("Invalid surface passed to ZImage::Attach.");
}

void ZImage::Reload()
{
    SDL_Surface *temp = rImage;
    rImage = NULL;
    Attach(temp);
}

void ZImage::Release()
{
    if(glIsTexture(rTexID))
        glDeleteTextures(1,&rTexID);
    rTexMinX = rTexMinY = rTexMaxX = rTexMaxY = 0.0f;
    rTexID = rWidth = rHeight = 0;
    FreeImage(rImage);
}

void ZImage::SetColorKey(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_Surface *temp=NULL;
    Uint32 color = SDL_MapRGB(rEngine->Display()->format,red,green,blue);

    if(rImage)
    {
        if(SDL_SetColorKey(rImage, SDL_SRCCOLORKEY, color) < 0)
            LogError("Invalid Call to SDL_SetColorKey.");
        else
        {
            //surface conversion//
            temp = rImage;
            rImage = SDL_DisplayFormatAlpha(temp);
            if(rImage)
            {
                FreeImage(temp);
                temp = rImage;
                rImage = NULL;
                Attach(temp); //Rebind new image.
            }
            else    //can't convert
            {
                LogError("Surface conversion failed.");
                rImage = temp;
            }
        }
    }
    else
        LogError("ZImage not initialized in ZImage::SetColorKey.");
}

void ZImage::Flip(bool horizontal, bool vertical)
{
    GLfloat temp;
    if(horizontal)
    {
        temp = rTexMinX;
        rTexMinX = rTexMaxX;
        rTexMaxX = temp;
    }
    if(vertical)
    {
        temp = rTexMinY;
        rTexMinY = rTexMaxY;
        rTexMaxY = temp;
    }
}

void ZImage::Stretch(float xFactor, float yFactor)
{
    rWidth = static_cast<unsigned int>(xFactor*rWidth);
    rHeight = static_cast<unsigned int>(yFactor*rHeight);
}

void ZImage::Resize(unsigned int width, unsigned int height)
{
    rWidth = width;
    rHeight = height;
}

void ZImage::Bind()
{
    glBindTexture(GL_TEXTURE_2D, rTexID);
}

void ZImage::Draw(float x, float y)
{
    Bind();

    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(rTexMinX,rTexMinY);    glVertex2f(x,y);
        glTexCoord2f(rTexMaxX,rTexMinY);    glVertex2f(x+rWidth,y);
        glTexCoord2f(rTexMinX,rTexMaxY);    glVertex2f(x,y+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY);    glVertex2f(x+rWidth,y+rHeight);
    glEnd();
}

void ZImage::DrawRotated(int x, int y, float angle)
{
    float cX,cY; //center variables

    cX = rWidth/2.0f;
    cY = rHeight/2.0f;

    glPushMatrix();
    glTranslatef(x+cX,y+cY,0);
    glRotatef(angle,0,0,1.0f);
    Bind(); 
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(rTexMinX,rTexMinY);    glVertex2f(-cX,-cY);
        glTexCoord2f(rTexMaxX,rTexMinY);    glVertex2f(-cX+rWidth,-cY);
        glTexCoord2f(rTexMinX,rTexMaxY);    glVertex2f(-cX,-cY+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY);    glVertex2f(-cX+rWidth,-cY+rHeight);
    glEnd();
    glPopMatrix();
}

bool ZImage::IsLoaded()
{
    return glIsTexture(rTexID) == GL_TRUE;
}

SDL_Surface* ZImage::Surface()
{
    return rImage;
}

int ZImage::Width()
{
    return rWidth;
}

int ZImage::Height()
{
    return rHeight;
}

}
