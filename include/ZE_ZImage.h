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
Description: Header file for core ZEngine Image Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZImage.h,v 1.1 2002/11/21 05:41:10 cozman Exp $<br>

    \file ZE_ZImage.h
    \brief Definition file for ZImage.

    Definition file for ZImage, the basic Image class for ZEngine.
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
        //!    Class containing image and filename.
        ImageData rImage;
    public:

        /*!
            \brief Default Constructor.

            Default Constructor, does nothing.
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
            \brief Sets Alpha (transparency) value of Image.

            Set Alpha channel of an Image, only used in 32 bit mode.
            \param alpha Number 0-255 describing translucency of image. (0 = transparent, 255 = opaque)
        **/
        void SetAlpha(Uint8 alpha);

        /*!
            \brief Set Color Key (transparent color) of Image.

            Set color which will not be drawn in image.
            \param color Uint32 color describing color to use as transparent.
        **/
        void SetColorKey(Uint32 color);

        /*!
            \brief Draw Image to Screen.

            Draw Image to screen at specified location.
            \param x X coord to draw Image to.
            \param y Y coord to draw Image to.
        **/
        void Draw(Sint16 x, Sint16 y);

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
        SDL_Surface *GetImage();

        /*!
            \brief Get Width.

            Get Width of Image.
            \return Image Width.
        **/
        int GetWidth();

        /*!
            \brief Get Height.

            Get Height of Image.
            \return Image Height.
        **/
        int GetHeight();

        /*!
            \brief Get filename of image.

            Get filename of image or if Image doesn't have a specific filename string describing origin of image.
            \return Image Filename.
        **/
        string GetFilename();
};
}

#endif //__ze_zimage_h__
