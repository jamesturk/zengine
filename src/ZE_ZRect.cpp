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
$Id: ZE_ZRect.cpp,v 1.2 2002/12/01 08:36:39 cozman Exp $<br>

    \file ZE_ZRect.cpp
    \brief Source file for ZRect.

    Implementation of ZRect, the Rectangle class for ZEngine.
**/

#include "ZE_ZRect.h"

namespace ZE
{

ZRect::ZRect() :
    rX(0),rY(0),rWidth(0),rHeight(0)
{
}

ZRect::ZRect(int x, int y, int width, int height) :
    rX(x),rY(y),rWidth(width),rHeight(height)
{
}

ZRect::ZRect(const ZRect &rhs) :
    rX(rhs.X()),rY(rhs.Y()),rWidth(rhs.Width()),rHeight(rhs.Height())
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
                    return false;    //nothing left to check they are ==
            }
        }
    }
}

void ZRect::Draw(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    glColor4ub(red,green,blue,alpha);
    glBegin(GL_QUADS);
        glVertex2i(rX, rY);
        glVertex2i(rX+rWidth, rY);
        glVertex2i(rX+rWidth, rY+rHeight);
        glVertex2i(rX, rY+rHeight);
    glEnd();
}

void ZRect::Move(int x, int y)
{
    rX = x;
    rY = y;
}

void ZRect::MoveRel(int xMove, int yMove)
{
    rX += xMove;
    rY += yMove;
}

void ZRect::Resize(int width, int height)
{
    rWidth = width;
    rHeight = height;
}

void ZRect::ResizeRel(int widthChange, int heightChange)
{
    rWidth += widthChange;
    rHeight += heightChange;
}

bool ZRect::Intersects(const ZRect &rect) const
{
    return !(rX > rect.Right() || rect.Left() > rX+rWidth ||
        rY > rect.Bottom() || rect.Top() > rY+rHeight);
}

bool ZRect::Contains(int x, int y) const
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
    int tempX=0,tempY=0,tempW=0,tempH=0;

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

int ZRect::X() const
{
    return rX;
}

int ZRect::Y() const
{
    return rY;
}

int ZRect::Left() const
{
    return rX;
}

int ZRect::Right() const
{
    return rX+rWidth;
}

int ZRect::Top() const
{
    return rY;
}

int ZRect::Bottom() const
{
    return rY+rHeight;
}

int ZRect::Width() const
{
    return rWidth;
}

int ZRect::Height() const
{
    return rHeight;
}

}    //namespace ZE
