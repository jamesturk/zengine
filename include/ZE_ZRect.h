/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZRect.h
    \brief Definition file for ZRect.

    Definition file for ZRect, the Rectangle class for ZEngine.
    <br>$Id: ZE_ZRect.h,v 1.11 2003/05/13 01:30:51 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zrect_h__
#define __ze_zrect_h__

#include "ZE_ZEngine.h"

namespace ZE
{

/*!
    \brief ZEngine class for simplified rectangle use.

    ZRect Rectangle class, used to define a rectangular area or perform operations on the defined area.
**/
class ZRect
{
    protected:  
        //! X Position of top left corner of rectangle.
        float rX;
        //! Y Position of top left corner of rectangle.
        float rY;
        //! Width of Rectangle.
        float rWidth;
        //! Height of Rectangle.
        float rHeight;

    public:

        /*!
            \brief Default constructor for ZRect.

            Default constructor, initializes all values to zero.
        **/
        ZRect();

        /*!
            \brief Constructor for ZRect that takes inital values.

            Constructor for ZRect that takes inital values for all four members.
            \param x Value for x position.
            \param y Value for y position.
            \param width Value for width.
            \param height Value for height.
        **/
        ZRect(float x, float y, float width, float height);

        /*!
            \brief Constructor for ZRect that uses an SDL_Rect.

            Constructor for ZRect that initializes from an SDL_Rect.
            \param rect SDL_Rect to intialize from.
        **/
        ZRect(const SDL_Rect &rect);

        /*!
            \brief Copy constructor for ZRect.

            Takes a ZRect and constructs a new identical rectangle.
            \param rhs Rectangle to construct from.
        **/
        ZRect(const ZRect &rhs);

        /*!
            \brief Overload for = operator with ZRect.

            Copies all values from one ZRect into another.
            \param rhs Rectangle to copy values from.
            \return New value of the ZRect.
        **/
        const ZRect& operator=(const ZRect &rhs);

        /*!
            \brief Virtual Destructor.

            Virtual destructor making future inheritance safe.
        **/
        virtual ~ZRect();

        /*!
            \brief Overload for < operator with ZRect, based upon location then size.

            Rectangles are sorted by y value, followed by x value, if they start at the same place, 
            the smaller of the two is deemed less than the other.
            \param rhs Rectangle to compare.
            \return True if this rectangle is smaller than the rhs rectangle, false otherwise.
        **/
        bool operator<(const ZRect &rhs) const;

        /*!
            \brief Draw rectangle. (filled)

            Draw the ZRect, this function is mainly provided for testing purposes.
            \param red Red component of color (0-255).
            \param green Green component of color (0-255).
            \param blue Blue component of color (0-255).
            \param alpha Alpha component of color (0-255).
        **/
        void Draw(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha=255) const;

        /*!
            \brief Changes the location of the rectangle.

            Changes the current x,y position of the rectangle.
            \param x New x position for rectangle.
            \param y New y position for rectangle.
        **/
        void Move(float x, float y);

        /*!
            \brief Changes the location of the rectangle based upon the current location.

            Changes the current x,y position of the rectangle relative to the current location.
            \param xMove Offset for new x position from current.
            \param yMove Offset for new y position from current.
        **/
        void MoveRel(float xMove, float yMove);

        /*!
            \brief Resize rectangle.

            Changes the current width and height of the rectangle.
            \param width New width for rectangle.
            \param height New height for rectangle.
        **/
        void Resize(float width, float height);

        /*!
            \brief Grows or shrinks current rectangle.

            Changes the current width and height of the rectangle based upon current values.
            \param widthChange Amount to add or subtract from width.
            \param heightChange Amount to add or subtract from height.
        **/
        void ResizeRel(float widthChange, float heightChange);

        /*!
            \brief Check if one ZRect intersects another.

            Checks for overlap and returns boolean value based on if overlap exists.
            \param rect Rectangle to check for intersection with.
            \return True if intersection occured, false otherwise.
        **/
        bool Intersects(const ZRect &rect) const;

        /*!
            \brief Check if a rectangle contains a given point.

            Checks point against boundaries of rectangle and returns result.
            \param x X value of point to check.
            \param y Y value of poitn to check.
            \return Boolean variable, true if point is inside rectangle, false otherwise.
        **/
        bool Contains(float x, float y) const;

        /*!
            \brief Check if a rectangle contains a given point.

            Checks point against boundaries of rectangle and returns result.
            \param rect Rectangle to check for point.
            \return Boolean variable, true if point is inside rectangle, false otherwise.
        **/
        bool Contains(const ZRect &rect) const;

        /*!
            \brief Finds intersection of two rectangles.

            Checks for intersection, and returns rectangle where the two rectangles intersect.
            \param rect Rectangle to check intersection with.
            \return ZRect describing intersection area.
        **/
        ZRect Intersection(const ZRect &rect) const;

        /*!
            \brief Returns an SDL_Rect representing the rectangle.

            Makes a SDL_Rect representing the rectangle, for use where functions require an SDL_Rect.
            \return SDL_Rect representing the ZRect.
        **/
        SDL_Rect SDLrect() const;

        /*!
            \brief Returns X Location.

            Access private X location member.
            \return Value of mX.
        **/
        float X() const;

        /*!
            \brief Returns Y Location.

            Access private Y location member.
            \return Value of mY.
        **/
        float Y() const;

        /*!
            \brief Return position of left side.

            Find X position of left side of rectangle.
            \return X position of left side.
        **/
        float Left() const;

        /*!
            \brief Return position of right side.

            Find X position of right side of rectangle.
            \return X position of right side.
        **/
        float Right() const;

        /*!
            \brief Return position of top side.

            Find Y position of top side of rectangle.
            \return Y position of top side.
        **/
        float Top() const;

        /*!
            \brief Return position of bottom side.

            Find Y position of left side of rectangle.
            \return Y position of bottom side.
        **/
        float Bottom() const;

        /*!
            \brief Returns Width.

            Access private width member.
            \return Value of mWidth.
        **/
        float Width() const;

        /*!
            \brief Returns Height.

            Access private height member.
            \return Value of mHeight.
        **/
        float Height() const;
};

} //namespace ZE

#endif //__ze_zrect_h__
