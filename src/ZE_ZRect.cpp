/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZRect.cpp <br>
Description: Implementation source file for core ZEngine Rectangle Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZRect.cpp,v 1.1 2002/11/21 05:41:13 cozman Exp $<br>

    \file ZE_ZRect.cpp
    \brief Source file for ZRect.

    Implementation of ZRect, the Rectangle class for ZEngine.
**/

#include "ZE_ZRect.h"

namespace ZE
{

ZRect::ZRect() :
    mX(0),mY(0),mWidth(0),mHeight(0)
{
}

ZRect::ZRect(int x, int y, int width, int height) :
    mX(x),mY(y),mWidth(width),mHeight(height)
{
}

ZRect::ZRect(const ZRect &rhs) :
    mX(rhs.X()),mY(rhs.Y()),mWidth(rhs.Width()),mHeight(rhs.Height())
{
}

const ZRect& ZRect::operator=(const ZRect &rhs)
{
    if(this != &rhs)
    {
        mX = rhs.X();
        mY = rhs.Y();
        mWidth = rhs.Width();
        mHeight = rhs.Height();
    }
    return *this;
}

bool ZRect::operator<(const ZRect &rhs) const
{
    //< is the one that is closer to top corner (as a whole)//

    if(mY < rhs.Y())    //check Ys
        return true;
    else if(mY > rhs.Y())
        return false;
    else
    {
        if(mX < rhs.X())    //check Xs
            return true;
        else if(mX > rhs.X())
            return false;
        else
        {
            if(mHeight < rhs.Height())    //check heights
                return true;
            else if(mHeight > rhs.Height())
                return false;
            else
            {
                if(mWidth < rhs.Width())    //check widths
                    return true;
                else if(mWidth > rhs.Width())
                    return false;
                else
                    return false;    //nothing left to check they are ==
            }
        }
    }
}

void ZRect::Move(int x, int y)
{
    mX = x;
    mY = y;
}

void ZRect::MoveRel(int xMove, int yMove)
{
    mX += xMove;
    mY += yMove;
}

void ZRect::Resize(int width, int height)
{
    mWidth = width;
    mHeight = height;
}

void ZRect::ResizeRel(int widthChange, int heightChange)
{
    mWidth += widthChange;
    mHeight += heightChange;
}

bool ZRect::Intersects(const ZRect &rect) const
{
    return !(mX > rect.Right() || rect.Left() > mX+mWidth ||
        mY > rect.Bottom() || rect.Top() > mY+mHeight);
}

bool ZRect::Contains(int x, int y) const
{
    return x > mX && x < mX+mWidth && y > mY && y < mY+mHeight;
}

bool ZRect::Contains(const ZRect &rect) const
{
    //contains all 4 points
    return Contains(rect.Left(),rect.Top()) && Contains(rect.Right(),rect.Top()) &&
        Contains(rect.Left(),rect.Bottom()) && Contains(rect.Right(),rect.Bottom());
}

ZRect ZRect::Intersection(const ZRect &rect) const
{
    int tempX=0,tempY=0,tempW=0,tempH=0;

    if(Intersects(rect))
    {
        tempX = mX > rect.X() ? mX : rect.X();
        tempY = mY > rect.Y() ? mY : rect.Y();
        tempW = mX+mWidth < rect.Right() ? mX+mWidth : rect.Right();
        tempH = mY+mHeight < rect.Bottom() ? mY+mHeight : rect.Bottom();

        tempW -= tempX;        //adjust width and height
        tempH -= tempY;
    }

    return ZRect(tempX,tempY,tempW,tempH);
}

SDL_Rect ZRect::SDLrect() const
{
    SDL_Rect ret;
    
    ret.x = static_cast<Sint16>(mX);
    ret.y = static_cast<Sint16>(mY);
    ret.w = static_cast<Sint16>(mWidth);
    ret.h = static_cast<Sint16>(mHeight);

    return ret;
}

int ZRect::X() const
{
    return mX;
}

int ZRect::Y() const
{
    return mY;
}

int ZRect::Left() const
{
    return mX;
}

int ZRect::Right() const
{
    return mX+mWidth;
}

int ZRect::Top() const
{
    return mY;
}

int ZRect::Bottom() const
{
    return mY+mHeight;
}

int ZRect::Width() const
{
    return mWidth;
}

int ZRect::Height() const
{
    return mHeight;
}

}    //namespace ZE
