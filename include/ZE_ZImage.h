/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zimage_h__
#define __ze_zimage_h__

#include "ZE_ZEngine.h"
#include "ZE_ZRect.h"

namespace ZE
{

class ZImage
{
    protected:
        ZEngine* rEngine;
        SDL_Surface *rImage;
        Uint8 rAlpha;
#if (GFX_BACKEND == ZE_OGL)
        GLfloat rTexMinX;
        GLfloat rTexMinY;
        GLfloat rTexMaxX;
        GLfloat rTexMaxY;
        unsigned int rTexID;
        GLfloat rWidth;
        GLfloat rHeight;
#endif //GFX_BACKEND == OGL
    
    public:
        ZImage();
        ZImage(const ZImage &rhs);
        ZImage(std::string filename);
        ZImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);
        ZImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);
        ZImage(SDL_Surface *surface);
        virtual ~ZImage();

        void Open(std::string filename);
        void OpenFromZip(std::string zipname, std::string filename);
        void OpenFromZRF(std::string resourceId);
        void OpenFromImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);
        void OpenFromImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        void Attach(SDL_Surface *surface);
        void Reload();
        void Release();

        void SetAlpha(Uint8 alpha);
        void SetColorKey(Uint8 red, Uint8 green, Uint8 blue);
        void Draw(int x, int y) const;
        void DrawClipped(int x, int y, ZRect clipRect) const;

#if (GFX_BACKEND == ZE_OGL)
        void Draw(float x, float y) const;
        void Draw(float x, float y, Uint8 vc[]) const;
        void DrawRotated(int x, int y, float angle) const;
        void DrawRotated(float x, float y, float angle) const;
        void DrawRotated(float x, float y, float angle, Uint8 vc[]) const;
        void DrawClipped(float x, float y, ZRect clipRect) const;
        void DrawClipped(float x, float y, ZRect clipRect, Uint8 vc[]) const;
        void Flip(bool horizontal, bool vertical);
        void Stretch(float xFactor, float yFactor);
        void Resize(float width, float height);
        void Bind() const;
#endif //GFX_BACKEND == OGL

        bool IsLoaded() const;
        SDL_Surface *Surface() const;

#if (GFX_BACKEND == ZE_OGL)
        float Width() const;
        float Height() const;
#elif (GFX_BACKEND == ZE_SDL)
        int Width() const;
        int Height() const;
#endif //GFX_BACKEND

        Uint8 Alpha() const;
};

}

#endif
