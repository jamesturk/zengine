/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZFont.h
    \brief Definition file for ZFont.

    Definition file for ZFont, the basic Font class for ZEngine.
    <br>$Id: ZE_ZFont.h,v 1.17 2003/12/24 04:46:48 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zfont_h__
#define __ze_zfont_h__

#include "ZE_ZEngine.h"
#include "ZE_ZImage.h"

#ifdef USE_SDL_TTF

namespace ZE
{

/*!
    \brief ZFont class for basic Font use.

    ZFont font container class, class wraps common features of SDL_TTF.
**/
class ZFont
{
    protected:
        //! Pointer to ZEngine Object
        ZEngine* rEngine;
        //! Pointer to font data.
        TTF_Font *rFont;
        //! Filename, for resizing.
        std::string rFilename;
        //! Zip filename, for resizing when file was from archive.
        std::string rZipname;
        //! SDL_Color for current text color.
        SDL_Color rColor;
        //! SDL_Color for background color to be used in shaded draws. 
        SDL_Color rBGColor;

    public:

        ///////////////////////
        //Opening and Closing//
        ///////////////////////

        /*!
            \brief Default Constructor.

            Default Constructor, does nothing.
        **/
        ZFont();

        /*!
            \brief Constructor that opens a font with a certain size.

            Constructor simply calls ZFont::Open() with same parameters.
            \param filename Font to open.
            \param size Size to use for font.
        **/
        ZFont(std::string filename, int size);

        /*!
            \brief Destructor, frees memory.

            Destructor calls ZFont::Release().
        **/
        virtual ~ZFont();

        /*!
            \brief Opens a font with a certain size.

            Opens a font given a filename and a point size.
            \param filename Font to open.
            \param size Size to use for font.
        **/
        void Open(std::string filename, int size);

        /*!
            \brief Opens a font from within a zip archive.

            Open a font from within a zip archive using zlib and SDL_RWops.
            \param zipname Zip file to open image from.
            \param filename File to open as new image.
            \param size Size to use for font.
        **/
        void OpenFromZip(std::string zipname, std::string filename, int size);

        /*!
            \brief Opens a font file from the current ZEngine Resource File.

            Open font file from the current ZEngine Resource File, the XML resource file set via ZEngine::SetResourceFile.
        **/
        void OpenFromZRF(std::string resourceId);

        /*!
            \brief Release font.

            Release memory held by font. (Called by destructor).
        **/
        void Release();

        ////////////////////////
        //Settings and Drawing//
        ////////////////////////

        /*!
            \brief Draws a std::string in a color to a ZImage.

            Draw to a surface in specified color and associate that surface with a ZImage.
            \param text String to write.
            \param image ZImage to draw to.
        **/
        void DrawText(std::string text, ZImage &image) const;

        /*!
            \brief Draws a std::string with a colored background to a ZImage.

            Draw to a surface a std::string with a background of rBGColor and lettering in the normal color and associate that surface with a ZImage.
            \param text String to write.
            \param image ZImage to draw to.
        **/
        void DrawShadedText(std::string text, ZImage &image) const;

        /*!
            \brief Set Text rColor.

            Set rColor of Text Output.
            \param r Red component of color (0-255).
            \param g Green component of color (0-255).
            \param b Blue component of color (0-255).
            \param a Alpha component of drawn font, including background if present. (0-255) (Optional, defaults to 255.)
        **/
        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255);

        /*!
            \brief Set Background rColor.

            Set rColor of Background for Shaded Draw.
            \param r Red component of color (0-255).
            \param g Green component of color (0-255).
            \param b Blue component of color (0-255).
        **/
        void SetBGColor(Uint8 r, Uint8 g, Uint8 b);

        /*!
            \brief Set display format.

            Set display format (bold, italic, underline).
            \param bold Decides bold setting of font.
            \param italic Decides italic setting of font.
            \param underline Decides underline setting of font.
        **/
        void SetStyle(bool bold, bool italic, bool underline);

        /*!
            \brief Resize Font.

            Release and Reopen font in new size.
            \param size New size for font.
        **/
        void Resize(int size);

        /////////////
        //Accessors//
        /////////////

        /*!
            \brief Check if file is loaded.

            Check if file is loaded and pointer to data is non-NULL.
            \return Loaded or Unloaded state of data.
        **/
        bool IsLoaded() const;

        /*!
            \brief Get Bold Setting.

            Check if font output is currently bold.
            \return True or False state of bold.
        **/
        bool IsBold() const;

        /*!
            \brief Get Italic Setting.

            Check if font output is currently italic.
            \return True or False state of italic.
        **/
        bool IsItalic() const;

        /*!
            \brief Get Underlined Setting.

            Check if font output is currently underline.
            \return True or False state of underline.
        **/
        bool IsUnderlined() const;

        /*!
            \brief Get Height of Font.

            Check font height as reported by SDL_ttf.
            \return Height of font.
        **/
        int Height() const;

        /*!
            \brief Get Line Skip for Font.

            Check font line skip as reported by SDL_ttf.
            \return Recommended Line Skip of font.
        **/
        int LineSkip() const;

        /*!
            \brief Get String Width.

            Get Width of String in Current Font in Pixels.
            \param text String to get width of.
            \return Width of String in Current font.
        **/
        int StringWidth(std::string text) const;

        /*!
            \brief Get String Height.

            Get Height of String in Current Font in Pixels.
            \param text String to get height of.
            \return Height of String in Current font.
        **/
        int StringHeight(std::string text) const;
};

}

#endif //USE_SDL_TTF

#endif //__ze_zfont_h__
