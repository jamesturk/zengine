/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zrect_h__
#define __ze_zrect_h__

#include "ZE_ZEngine.h"

namespace ZE
{

class ZRect
{
    protected:
        ZEngine* rEngine;
        float rX;
        float rY;
        float rWidth;
        float rHeight;

    public:

        ZRect();
        ZRect(float x, float y, float width, float height);
        ZRect(const SDL_Rect &rect);
        ZRect(const ZRect &rhs);
        virtual ~ZRect();

        const ZRect& operator=(const ZRect &rhs);
        bool operator<(const ZRect &rhs) const;

        void Draw(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha=255) const;
        void Move(float x, float y);
        void MoveRel(float xMove, float yMove);
        void Resize(float width, float height);
        void ResizeRel(float widthChange, float heightChange);

        bool Intersects(const ZRect &rect) const;
        bool Contains(float x, float y) const;
        bool Contains(const ZRect &rect) const;
        ZRect Intersection(const ZRect &rect) const;
        SDL_Rect SDLrect() const;
        float X() const;
        float Y() const;
        float Left() const;
        float Right() const;
        float Top() const;
        float Bottom() const;
        float Width() const;
        float Height() const;
};

} //namespace ZE

#endif //__ze_zrect_h__
