/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZImage.cpp
    \brief Source file for ZImage.

    Implementation of ZImage, the Image class for ZEngine.
    <br>$Id: ZE_ZImage.cpp,v 1.36 2003/07/05 00:40:45 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZImage.h"

namespace ZE
{

ZImage::ZImage() : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    Release();
}

ZImage::ZImage(const ZImage &rhs) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(rhs.Alpha())
{
    OpenFromImage(rhs.Surface(),0,0,(Sint16)rhs.Width(),(Sint16)rhs.Height());
}

ZImage::ZImage(std::string filename) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    Open(filename);
}

ZImage::ZImage(SDL_Surface *surface) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    Attach(surface);
}

ZImage::ZImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    OpenFromImage(img,x,y,w,h);
}

ZImage::ZImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    OpenFromImage(img.Surface(),x,y,w,h);   //call SDL_Surface* version instead of taking the long way
}

ZImage::~ZImage()
{
    Release();
}

void ZImage::Open(std::string filename)
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
        rEngine->ReportError(ZERR_NOIMAGE,"OpenFromImage");

    cutImg = SDL_CreateRGBSurface(0, rect.w, rect.h, rEngine->BPP(),
        screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if(!cutImg)
        rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_CreateRGBSurface failed in ZImage::OpenFromImage: %s.",SDL_GetError()));

    SDL_BlitSurface(image,&rect,cutImg,NULL);
    Attach(cutImg);
}

void ZImage::OpenFromImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
    OpenFromImage(img.Surface(),x,y,w,h);
}

//attach is really the core of ZImage, everything calls it, it converts SDL_Surface->OpenGL Texture->ZImage
void ZImage::Attach(SDL_Surface *surface)
{
    GLfloat coord[4];

	Release();		//avoid most user inflicted memory leaks associated with ZImage

    //surface conversion//
    SDL_Surface *temp = surface;
    surface = SDL_DisplayFormatAlpha(temp); //TTF_RenderTextBlended relys on this
    if(surface)
    {
        FreeImage(temp);
    }
    else    //can't convert
    {
        rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_DisplayFormatAlpha failed in ZImage::Attach: %s",SDL_GetError()));
        surface = temp;
    }

    if(surface)
    {
        rWidth = surface->w;
        rHeight = surface->h;
        rTexID = SDL_GL_LoadTexture(surface,coord); //major helper, not written by me, from libsdl.org
        rTexMinX = coord[0];
        rTexMinY = coord[1];
        rTexMaxX = coord[2];
        rTexMaxY = coord[3];
        rImage = surface;
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"Attach");
}

void ZImage::Reload()
{
    //this little hack helps to reload images to OpenGL surfaces after loss
    SDL_Surface *temp = rImage;
    rImage = NULL;  
    Attach(temp);
}

void ZImage::Release()
{
    //set everything back the way it came
    if(glIsTexture(rTexID))
        glDeleteTextures(1,&rTexID);
    rTexMinX = rTexMinY = rTexMaxX = rTexMaxY = 0.0f;
    rTexID = rWidth = rHeight = 0;
    FreeImage(rImage);
}

void ZImage::SetAlpha(Uint8 alpha)
{
    rAlpha = alpha;
}

void ZImage::SetColorKey(Uint8 red, Uint8 green, Uint8 blue)
{
    Uint32 color = SDL_MapRGB(rImage->format,red,green,blue);

    if(rImage)
    {
        if(SDL_SetColorKey(rImage, SDL_SRCCOLORKEY, color) < 0)
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_SetColorKey failed in ZImage::SetColorKey: %s",SDL_GetError()));
        else
            Reload(); //do the reattach hack, this gets a new OpenGL surface for the same image
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"SetColorKey");
}

void ZImage::Flip(bool horizontal, bool vertical)
{
    GLfloat temp;
    //all that a flip does is invert the Min/Max coordinates
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

//stretching and resizing is very inexpensive, done via variables
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

//this is available for other uses of ZEngine
void ZImage::Bind() const
{
    if(rTexID)
        glBindTexture(GL_TEXTURE_2D, rTexID);
    else
        rEngine->ReportError(ZERR_NOIMAGE,"Bind");
        
}

void ZImage::Draw(int x, int y) const
{
    //source is same as float version, but uses glVertex2i
    glColor4ub(255,255,255,rAlpha);
    Bind();
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(rTexMinX,rTexMinY);    glVertex2i(x,y);
        glTexCoord2f(rTexMaxX,rTexMinY);    glVertex2i(x+rWidth,y);
        glTexCoord2f(rTexMinX,rTexMaxY);    glVertex2i(x,y+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY);    glVertex2i(x+rWidth,y+rHeight);
    glEnd();
    glColor4ub(255,255,255,255);
}

void ZImage::Draw(float x, float y) const
{
    glColor4ub(255,255,255,rAlpha); //sets the color correctly
    Bind();
    glBegin(GL_TRIANGLE_STRIP); //triangle strips, speedier?
        glTexCoord2f(rTexMinX,rTexMinY);    glVertex2f(x,y);
        glTexCoord2f(rTexMaxX,rTexMinY);    glVertex2f(x+rWidth,y);
        glTexCoord2f(rTexMinX,rTexMaxY);    glVertex2f(x,y+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY);    glVertex2f(x+rWidth,y+rHeight);
    glEnd();
    glColor4ub(255,255,255,255);    //be responsible, return to standard color state
}

void ZImage::DrawRotated(int x, int y, float angle) const
{
    DrawRotated(static_cast<float>(x),static_cast<float>(y),angle);
}

void ZImage::DrawRotated(float x, float y, float angle) const
{
    //center point
    float cX,cY; 
    cX = rWidth/2.0f;
    cY = rHeight/2.0f;

    glPushMatrix();
    glTranslatef(x+cX,y+cY,0);  //translate to center
    glRotatef(angle,0,0,1.0f);  //rotate on z axis, to keep x&y parallel to 2D plane
    glColor4ub(255,255,255,rAlpha); 
    Bind(); 
    //draw is modified to be based around center//
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(rTexMinX,rTexMinY);    glVertex2f(-cX,-cY);
        glTexCoord2f(rTexMaxX,rTexMinY);    glVertex2f(-cX+rWidth,-cY);
        glTexCoord2f(rTexMinX,rTexMaxY);    glVertex2f(-cX,-cY+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY);    glVertex2f(-cX+rWidth,-cY+rHeight);
    glEnd();
    glPopMatrix();
}

bool ZImage::IsLoaded() const
{
    return glIsTexture(rTexID) == GL_TRUE;
}

SDL_Surface* ZImage::Surface() const
{
    return rImage;
}

int ZImage::Width() const
{
    return rWidth;
}

int ZImage::Height() const
{
    return rHeight;
}

Uint8 ZImage::Alpha() const
{
    return rAlpha;
}

}
