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
    <br>$Id: ZE_ZImage.cpp,v 1.42 2003/09/01 00:22:35 cozman Exp $<br>
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

    cutImg = SDL_CreateRGBSurface(0, rect.w, rect.h, rEngine->DisplayDepth(),
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

#if (GFX_BACKEND == ZE_OGL)

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
        rWidth = static_cast<float>(surface->w);
        rHeight = static_cast<float>(surface->h);
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
    rTexID = 0;
    rWidth = rHeight = 0;
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

void ZImage::Draw(int x, int y) const
{
    Draw(static_cast<float>(x),static_cast<float>(y));
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

void ZImage::DrawClipped(float x, float y, ZRect clipRect) const
{
    ZRect imgRect(x,y,rWidth,rHeight),inRect;
    float xDiff,yDiff,nx,ny,nw,nh;
    xDiff = rTexMaxX - rTexMinX;
    yDiff = rTexMaxY - rTexMinY;

    if(clipRect.Contains(imgRect))
    {
        Draw(x,y);
    }
    else if(clipRect.Intersects(imgRect))
    {
        inRect = clipRect.Intersection(imgRect);

        nx = rTexMinX + (inRect.X()-imgRect.X())/imgRect.Width()*xDiff;
        ny = rTexMinY + (inRect.Y()-imgRect.Y())/imgRect.Height()*yDiff;
        nw = nx + (inRect.Width()/imgRect.Width())*xDiff;
        nh = ny + (inRect.Height()/imgRect.Height())*yDiff;

        glColor4ub(255,255,255,rAlpha); //sets the color correctly
        Bind();
        glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2f(nx,ny);    glVertex2f(inRect.Left(),inRect.Top());
            glTexCoord2f(nw,ny);    glVertex2f(inRect.Right(),inRect.Top());
            glTexCoord2f(nx,nh);    glVertex2f(inRect.Left(),inRect.Bottom());
            glTexCoord2f(nw,nh);    glVertex2f(inRect.Right(),inRect.Bottom());
        glEnd();
        glColor4ub(255,255,255,255);    //be responsible, return to standard color state
    }
    else    //doesn't contain nor intersect
    {
        //draw nothing
    }
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
    rWidth = xFactor*rWidth;
    rHeight = yFactor*rHeight;
}

void ZImage::Resize(float width, float height)
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

bool ZImage::IsLoaded() const
{
    return glIsTexture(rTexID) == GL_TRUE;
}

#elif (GFX_BACKEND == ZE_SDL)

void ZImage::Attach(SDL_Surface *surface)
{
    Release();

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
        rImage = surface;
    else
        rEngine->ReportError(ZERR_NOIMAGE,"Attach");
}

void ZImage::Reload()
{
    //currently a no-op
}

void ZImage::Release()
{
    FreeImage(rImage);
}

void ZImage::SetAlpha(Uint8 alpha)
{
    rAlpha = alpha;
    if(rImage)
    {
        if(SDL_SetAlpha(rImage, SDL_SRCALPHA, alpha) < 0)
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_SetAlpha failed in ZImage::SetAlpha: %s",SDL_GetError()));
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"SetAlpha");
}

void ZImage::SetColorKey(Uint8 red, Uint8 green, Uint8 blue)
{
    Uint32 color = SDL_MapRGBA(rImage->format,red,green,blue,255);

    if(rImage)
    {
        if(SDL_SetColorKey(rImage, SDL_RLEACCEL|SDL_SRCCOLORKEY, color) < 0)
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_SetColorKey failed in ZImage::SetColorKey: %s",SDL_GetError()));
        //surface conversion//
        SDL_Surface *temp = rImage;
        rImage = SDL_DisplayFormatAlpha(temp); //TTF_RenderTextBlended relys on this
        if(rImage)
        {
            FreeImage(temp);
        }
        else    //can't convert
        {
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_DisplayFormatAlpha failed in ZImage::SetColorKey: %s",SDL_GetError()));
            rImage = temp;
        }
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"SetColorKey");
}

void ZImage::Draw(int x, int y) const
{
    SDL_Rect rect;
    rect.x = static_cast<Sint16>(x);
    rect.y = static_cast<Sint16>(y);
    SDL_BlitSurface(rImage, NULL, rEngine->Display(), &rect);
}

bool ZImage::IsLoaded() const
{
    return rImage ? true : false;
}

#endif //GFX_BACKEND

SDL_Surface* ZImage::Surface() const
{
    return rImage;
}

#if (GFX_BACKEND == ZE_OGL)

float ZImage::Width() const
{
    return rWidth;
}

float ZImage::Height() const
{
    return rHeight;
}

#elif (GFX_BACKEND == ZE_SDL)

int ZImage::Width() const
{
    return rImage->w;
}

int ZImage::Height() const
{
    return rImage->h;
}

#endif //GFX_BACKEND

Uint8 ZImage::Alpha() const
{
    return rAlpha;
}

}
