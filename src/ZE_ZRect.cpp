/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZRect.h"

namespace ZE
{

ZRect::ZRect() :
    rEngine(ZEngine::GetInstance()),
    rX(0),rY(0),rWidth(0),rHeight(0)
{
}

ZRect::ZRect(float x, float y, float width, float height) :
    rEngine(ZEngine::GetInstance()),
    rX(x),rY(y),rWidth(width),rHeight(height)
{
}

ZRect::ZRect(const SDL_Rect &rect) :
    rEngine(ZEngine::GetInstance()),
    rX(static_cast<float>(rect.x)),
    rY(static_cast<float>(rect.y)),
    rWidth(static_cast<float>(rect.w)),
    rHeight(static_cast<float>(rect.h))
{
}

ZRect::ZRect(const ZRect &rhs) :
    rEngine(ZEngine::GetInstance()),
    rX(rhs.X()),rY(rhs.Y()),rWidth(rhs.Width()),rHeight(rhs.Height())
{
}

ZRect::~ZRect()
{
}

const ZRect& ZRect::operator=(const ZRect &rhs)
{
    if(this != &rhs)
    {
        rX = rhs.X();
        rY = rhs.Y();
        rWidth = rhs.Width();
        rHeight = rhs.Height();
    }
    return *this;
}

bool ZRect::operator<(const ZRect &rhs) const
{
    //< is the one that is closer to top corner (as a whole)//

    if(rY < rhs.Y())    //check Ys
        return true;
    else if(rY > rhs.Y())
        return false;
    else
    {
        if(rX < rhs.X())    //check Xs
            return true;
        else if(rX > rhs.X())
            return false;
        else
        {
            if(rHeight < rhs.Height())    //check heights
                return true;
            else if(rHeight > rhs.Height())
                return false;
            else
            {
                if(rWidth < rhs.Width())    //check widths
                    return true;
                else if(rWidth > rhs.Width())
                    return false;
                else
                    return false;    //nothing left to check, they are ==
            }
        }
    }
}

void ZRect::Draw(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) const
{
#if (GFX_BACKEND == ZE_OGL)
    glBindTexture(GL_TEXTURE_2D,0); //reset to blank texture
    glColor4ub(red,green,blue,alpha);
    glBegin(GL_QUADS);
        glVertex2f(rX, rY);
        glVertex2f(rX+rWidth, rY);
        glVertex2f(rX+rWidth, rY+rHeight);
        glVertex2f(rX, rY+rHeight);
    glEnd();
    glColor4ub(255,255,255,255);    //restore color setting
#elif (GFX_BACKEND == ZE_SDL)
    SDL_Rect rect = SDLrect();
    SDL_FillRect(rEngine->Display(), &rect, SDL_MapRGBA(rEngine->Display()->format,red,green,blue,alpha));
#endif //GFX_BACKEND

}

void ZRect::Move(float x, float y)
{
    rX = x;
    rY = y;
}

void ZRect::MoveRel(float xMove, float yMove)
{
    rX += xMove;
    rY += yMove;
}

void ZRect::Resize(float width, float height)
{
    rWidth = width;
    rHeight = height;
}

void ZRect::ResizeRel(float widthChange, float heightChange)
{
    rWidth += widthChange;
    rHeight += heightChange;
}

bool ZRect::Intersects(const ZRect &rect) const
{
    return !(rX > rect.Right() || rect.Left() > rX+rWidth ||
        rY > rect.Bottom() || rect.Top() > rY+rHeight);
}

bool ZRect::Contains(float x, float y) const
{
    return x > rX && x < rX+rWidth && y > rY && y < rY+rHeight;
}

bool ZRect::Contains(const ZRect &rect) const
{
    //contains all 4 points
    return Contains(rect.Left(),rect.Top()) && Contains(rect.Right(),rect.Top()) &&
        Contains(rect.Left(),rect.Bottom()) && Contains(rect.Right(),rect.Bottom());
}

ZRect ZRect::Intersection(const ZRect &rect) const
{
    float tempX=0,tempY=0,tempW=0,tempH=0;

    //can only grab the intersection if they intersect
    if(Intersects(rect))
    {
        tempX = rX > rect.X() ? rX : rect.X();
        tempY = rY > rect.Y() ? rY : rect.Y();
        tempW = rX+rWidth < rect.Right() ? rX+rWidth : rect.Right();
        tempH = rY+rHeight < rect.Bottom() ? rY+rHeight : rect.Bottom();

        tempW -= tempX;        //adjust width and height
        tempH -= tempY;
    }

    return ZRect(tempX,tempY,tempW,tempH);
}

SDL_Rect ZRect::SDLrect() const
{
    SDL_Rect ret;
    
    ret.x = static_cast<Sint16>(rX);
    ret.y = static_cast<Sint16>(rY);
    ret.w = static_cast<Sint16>(rWidth);
    ret.h = static_cast<Sint16>(rHeight);

    return ret;
}

float ZRect::X() const
{
    return rX;
}

float ZRect::Y() const
{
    return rY;
}

float ZRect::Left() const
{
    return rX;
}

float ZRect::Right() const
{
    return rX+rWidth;
}

float ZRect::Top() const
{
    return rY;
}

float ZRect::Bottom() const
{
    return rY+rHeight;
}

float ZRect::Width() const
{
    return rWidth;
}

float ZRect::Height() const
{
    return rHeight;
}

}    //namespace ZE
