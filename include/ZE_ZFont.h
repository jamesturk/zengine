/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zfont_h__
#define __ze_zfont_h__

#include "ZE_ZEngine.h"
#include "ZE_ZImage.h"

#ifdef USE_SDL_TTF

namespace ZE
{

class ZFont
{
    protected:
        ZEngine* rEngine;
        TTF_Font *rFont;
        std::string rFilename;
        std::string rZipname;
        SDL_Color rColor;
        SDL_Color rBGColor;

    public:
        ZFont();
        ZFont(std::string filename, int size);
        virtual ~ZFont();

        void Open(std::string filename, int size);
        void OpenFromZip(std::string zipname, std::string filename, int size);
        void OpenFromZRF(std::string resourceId);

        void Release();

        void DrawText(std::string text, ZImage &image) const;
        void DrawShadedText(std::string text, ZImage &image) const;
        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255);
        void SetBGColor(Uint8 r, Uint8 g, Uint8 b);
        void SetStyle(bool bold, bool italic, bool underline);      
        void Resize(int size);

        bool IsLoaded() const;
        bool IsBold() const;
        bool IsItalic() const;
        bool IsUnderlined() const;
        int GetHeight() const;
        int GetLineSkip() const;
        int CalcStringWidth(std::string text) const;
        int CalcStringHeight(std::string text) const;
};

}

#endif //USE_SDL_TTF

#endif //__ze_zfont_h__
