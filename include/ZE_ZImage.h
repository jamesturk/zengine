/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZImage.h
    \brief Definition file for ZImage.

    Definition file for ZImage, the OpenGL version of the ZImage class for ZEngine.
    <br>$Id: ZE_ZImage.h,v 1.18 2003/05/13 01:30:51 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zimage_h__
#define __ze_zimage_h__

#include "ZE_ZEngine.h"

namespace ZE
{

/*!
    \brief ZImage class for basic Image use.

    ZImage image drawing class, class wraps common features of SDL_Surface.  Inherited from ZObject.
**/
class ZImage
{
    protected:
        //! Pointer to ZEngine Object
        ZEngine* rEngine;
        //! Texture lower X, used internally for flip.
        GLfloat rTexMinX;
        //! Texture lower Y, used internally for flip
        GLfloat rTexMinY;
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
        //! Stored alpha value for drawing texture.
        Uint8 rAlpha;
    
    public:

        /*!
            \brief Default Constructor.

            Default Constructor, initializes variables.
        **/
        ZImage();

        /*!
            \brief Copy constructor for ZImage.

            Creates one ZImage using another.
            \param rhs A previously created ZImage to copy.
        **/
        ZImage(const ZImage &rhs);

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

            Constructor is same as calling ZImage::OpenFromImage with an SDL_Surface*.
    
            \param img Image to take new image from.
            \param x X Coordinate in source of top left corner.
            \param y Y Coordinate in source of top left corner.
            \param w Width of new image.
            \param h Height of new image.
        **/
        ZImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        /*!
            \brief Constructor to Construct from part of another ZImage.

            Constructor is same as calling ZImage::OpenFromImage with a ZImage.
    
            \param img Image to take new image from.
            \param x X Coordinate in source of top left corner.
            \param y Y Coordinate in source of top left corner.
            \param w Width of new image.
            \param h Height of new image.
        **/
        ZImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        /*!
            \brief Destructor, frees memory.

            Destructor calls ZImage::Release().
        **/
        virtual ~ZImage();

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
            \brief Cuts part of an existing image to create a new image.

            Cut part of an SDL_Surface to create a new Image.
    
            \param img SDL_Surface* to take new image from.
            \param x X Coordinate in source of top left corner.
            \param y Y Coordinate in source of top left corner.
            \param w Width of new image.
            \param h Height of new image.
        **/
        void OpenFromImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        /*!
            \brief Cuts part of an existing ZImage to create a new image.

            Cut part of another ZImage to create a new Image.
    
            \param img ZImage to take new image from.
            \param x X Coordinate in source of top left corner.
            \param y Y Coordinate in source of top left corner.
            \param w Width of new image.
            \param h Height of new image.
        **/
        void OpenFromImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h);

        /*!
            \brief Attach an existing surface to class.

            Attach a pointer to instance of ZImage. (NOTE: Should not be used on a surface that is owned elsewhere.)
            \param surface SDL_Surface* to use as rImage.
        **/
        void Attach(SDL_Surface *surface);

        /*!
            \brief Reattach a preloaded texture that has been lost.

            Attach loaded textures which have been lost due to loss of focus, should be called when ZEngine::ImagesNeedReload is true.
        **/
        void Reload();

        /*!
            \brief Releases image.

            Frees memory via call to SDL_FreeSurface for the image.
        **/
        void Release();

        ////////////
        //Graphics//
        ////////////

        /*!
            \brief Set alpha value (translucency) of image.

            Set translucency value 0-255 (0 is transparent, 255 = opaque).
            \since 0.8.2
            \param alpha Number 0-255 setting translucency for image.
        **/
        void SetAlpha(Uint8 alpha);

        /*!
            \brief Set Color Key (transparent color) of image.

            Set color which will not be drawn in image.
            \param red Red component of colorkey (0-255).
            \param green Green component of colorkey (0-255).
            \param blue Blue component of colorkey (0-255).
        **/
        void SetColorKey(Uint8 red, Uint8 green, Uint8 blue);

        /*!
            \brief Flip image over one or both axes.

            Flip image vertical and/or horizontal.
            \param horizontal Boolean, true will flip image horizontally.
            \param vertical Boolean, true will flip image vertically.
        **/
        void Flip(bool horizontal, bool vertical);

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
        void Bind() const;

        /*!
            \brief Draw Image to Screen.

            Draw Image to screen at specified location.
            \param x X coord to draw Image to.
            \param y Y coord to draw Image to.
        **/
        void Draw(int x, int y) const;

        /*!
            \brief Draw Image to Screen.

            Draw Image to screen at specified location.
            \since 0.8.3
            \param x X coord to draw Image to.
            \param y Y coord to draw Image to.
        **/
        void Draw(float x, float y) const;

        /*!
            \brief Draw Image rotated to screen.

            Image is rotated about it's own center by specified angle, then drawn to screen.
            \param x X coord to draw Image to.
            \param y Y coord to draw Image to.
            \param angle Angle in degrees to rotate image.
        **/
        void DrawRotated(int x, int y, float angle) const;

        /*!
            \brief Draw Image rotated to screen.

            Image is rotated about it's own center by specified angle, then drawn to screen.
            \since 0.8.3
            \param x X coord to draw Image to.
            \param y Y coord to draw Image to.
            \param angle Angle in degrees to rotate image.
        **/
        void DrawRotated(float x, float y, float angle) const;

        /////////////
        //Accessors//
        /////////////

        /*!
            \brief Check if file is loaded.

            Check if surface is a valid GL texture. (does not detect surface loss)
            \return Loaded or Unloaded state of data.
        **/
        bool IsLoaded() const;

        /*!
            \brief Get SDL_Surface.
            Get SDL_Surface pointer to actual image data.
            \return SDL_Surface* of rImage.
        **/
        SDL_Surface *Surface() const;

        /*!
            \brief Get Width.

            Get Current Width of Image.
            \return Image Width.
        **/
        int Width() const;

        /*!
            \brief Get Height.

            Get Current Height of Image.
            \return Image Height.
        **/
        int Height() const;

        /*!
            \brief Get Alpha component.

            Get current alpha value of image.
            \since 0.8.2
            \return Image Alpha.
        **/
        Uint8 Alpha() const;
};

}

#endif
