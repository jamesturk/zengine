/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header:
File: ZE_ZImage.h <br>
Description: Header file for core ZEngine Image and Texture Object. <br>
Author(s): James Turk, Gamer Tazar <br>
$Id: ZE_ZImage.h,v 1.3 2002/12/02 00:36:35 cozman Exp $<br>

    \file ZE_ZImage.h
    \brief Definition file for ZImage.

    Definition file for ZImage, the OpenGL version of the ZImage class for ZEngine.
**/

#ifndef __ze_zimage_h__
#define __ze_zimage_h__

#include "ZE_ZObject.h"

namespace ZE
{

/*!
    \brief ZImage class for basic Image use.

    ZImage image drawing class, class wraps common features of SDL_Surface.  Inherited from ZObject.
**/
class ZImage : public ZObject
{
    protected:
        //! Texture X width ratio, used internally by OpenGL.
        GLfloat rTexMaxX;
        //! Texture Y width ratio, used internally by OpenGL.
        GLfloat rTexMaxY;
        //! Stored texture for future use.
        SDL_Surface *rImage;
        //! Texture ID for OpenGL.
        unsigned int rTexID;
        //! Current draw width of Texture.
        unsigned int rWidth;
        //! Current draw height of Texture.
        unsigned int rHeight;
    
    public:

        /*!
            \brief Default Constructor.

            Default Constructor, initializes variables.
        **/
        ZImage();

        /*!
            \brief Constructor to Construct from File.

            Constructor is same as calling ZImage::Open() on passed filename.
            \param filename File to open as rImage.
        **/
        ZImage(string filename);

        /*!
            \brief Constructor to Construct from SDL_Surface*.

            Constructor is same as calling ZImage::Attach() on passed SDL_Surface*.
            \param surface SDL_Surface* to use as rImage.
        **/
        ZImage(SDL_Surface *surface);

        /*!
            \brief Constructor to Construct from part of an SDL_Surface*.

            Constructor is same as calling ZImage::OpenFromImage.
    
            \param img Image to take new image from.
            \param x X Coordinate in source of top left corner.
            \param y Y Coordinate in source of top left corner.
            \param w Width of new image.
            \param h Height of new image.
        **/
        ZImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        /*!
            \brief Destructor, frees memory.

            Destructor calls ZImage::Release().
        **/
        ~ZImage();

        ///////////////////////
        //Opening and Closing//
        ///////////////////////

        /*!
            \brief Opens a file.

            Open a file using ZEngine.  Loads into rImage member of class.
            \param filename File to open as rImage.
        **/
        void Open(string filename);

        /*!
            \brief Cuts part of an existing image to create the new image.

            Cut part of an SDL_Surface to create a new Image.
    
            \param img Image to take new image from.
            \param x X Coordinate in source of top left corner.
            \param y Y Coordinate in source of top left corner.
            \param w Width of new image.
            \param h Height of new image.
        **/
        void OpenFromImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        /*!
            \brief Attach an existing surface to class.

            Attach a pointer to instance of ZImage. (NOTE: Should not be used on a surface that is owned elsewhere.)
            \param surface SDL_Surface* to use as rImage.
        **/
        void Attach(SDL_Surface *surface);

        /*!
            \brief Releases image.

            Frees memory via call to SDL_FreeSurface for the image.
        **/
        void Release();

        ////////////
        //Graphics//
        ////////////

        /*!
            \brief Set Color Key (transparent color) of Image.

            Set color which will not be drawn in image.
            \param red Red component of colorkey (0-255).
            \param green Green component of colorkey (0-255).
            \param blue Blue component of colorkey (0-255).
        **/
        void SetColorKey(Uint8 red, Uint8 green, Uint8 blue);

        /*!
            \brief Stretch the image by a certain X and Y factor.

            Stretch image using a factor to multiply width and height by.
            \param xFactor Stretch factor for width. [newWidth = oldWidth * xStretch]
            \param yFactor Stretch factor for height. [newHeight = oldHeight * yStretch]
        **/
        void Stretch(float xFactor, float yFactor);

        /*!
            \brief Resizes an image, stretching to new size.

            Stretch image to new width and height.
            \param width New width to stretch image to.
            \param height New height to stretch image to.
        **/
        void Resize(unsigned int width, unsigned int height);

        /*!
            \brief OpenGL related bind call.

            OpenGL related bind call, only available in case you want to bind image in 3D.
            Draw uses this but the average user should never need to call this.
        **/
        void Bind();

        /*!
            \brief Draw Image to Screen.

            Draw Image to screen at specified location.
            \param x X coord to draw Image to.
            \param y Y coord to draw Image to.
        **/
        void Draw(float x, float y);

        /*!
            \brief Draw Image rotated to screen.

            Image is rotated about it's own center by specified angle, then drawn to screen.
            \param x X coord to draw Image to.
            \param y Y coord to draw Image to.
            \param angle Angle in degrees to rotate image.
        **/
        void DrawRotated(int x, int y, float angle);

        /////////////
        //Accessors//
        /////////////

        /*!
            \brief Check if file is loaded.

            Check if file is loaded and pointer to data is non-NULL.
            \return Loaded or Unloaded state of data.
        **/
        bool IsLoaded();

        /*!
            \brief Get SDL_Surface.
            Get SDL_Surface pointer to actual image data.
            \return SDL_Surface* of rImage.
        **/
        SDL_Surface *Surface();

        /*!
            \brief Get Width.

            Get Current Width of Image.
            \return Image Width.
        **/
        int Width();

        /*!
            \brief Get Height.

            Get Current Height of Image.
            \return Image Height.
        **/
        int Height();
};

}

#endif
