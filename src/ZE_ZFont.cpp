/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZFont.cpp <br>
Description: Implementation source file for core ZEngine Font Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZFont.cpp,v 1.4 2003/01/13 06:00:38 cozman Exp $<br>

    \file ZE_ZFont.cpp
    \brief Source file for ZFont.

    Implementation of ZFont, the basic Font class for ZEngine.
**/

#include "ZE_ZFont.h"

#ifdef USE_SDL_TTF

namespace ZE
{


ZFont::ZFont()
{
    rFont = NULL;
    rColor.r = rColor.g = rColor.b = rColor.unused = 255;
    rBGColor.r = rBGColor.g = rBGColor.b = rBGColor.unused = 0;
}

ZFont::ZFont(string filename, int size)
{
    rFont = NULL;
    rColor.r = rColor.g = rColor.b = rColor.unused = 255;
    rBGColor.r = rBGColor.g = rBGColor.b = rBGColor.unused = 0;
    Open(filename,size);
}

ZFont::~ZFont()
{
    Release();
}

void ZFont::Open(string filename, int size)
{
    Release();
    rFont = rEngine->LoadFont(filename,size);
}

void ZFont::Release()
{
    FreeFont(rFont);
}

void ZFont::DrawText(string text, ZImage &image)
{
    image.Attach(TTF_RenderText_Solid(rFont, text.c_str(), rColor));
}

void ZFont::DrawShadedText(string text, ZImage &image)
{
    image.Attach(TTF_RenderText_Shaded(rFont, text.c_str(), rColor, rBGColor));
}

void ZFont::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
    rColor.r = r;
    rColor.g = g;
    rColor.b = b;
}

void ZFont::SetBGColor(Uint8 r, Uint8 g, Uint8 b)
{
    rBGColor.r = r;
    rBGColor.g = g;
    rBGColor.b = b;
}

void ZFont::SetStyle(bool Bold, bool Italic, bool Underline)
{
    int flags=0;

    if(Bold)
        flags |= TTF_STYLE_BOLD;
    if(Italic)
        flags |= TTF_STYLE_ITALIC;
    if(Underline)
        flags |= TTF_STYLE_UNDERLINE;
    if(!flags)
        flags = TTF_STYLE_NORMAL;

    if(rFont)
        TTF_SetFontStyle(rFont,flags);
    else
        rEngine->ReportError(ZERR_NOFONT,"SetStyle");
}

void ZFont::Resize(int size)
{
    Open(rFilename,size);
}

bool ZFont::IsLoaded()
{
    return rFont != NULL;
}

bool ZFont::IsBold()
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_BOLD) > 0;
    else
    {
        rEngine->ReportError(ZERR_NOFONT, "IsBold");
        return false;
    }
}

bool ZFont::IsItalic()
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_ITALIC) > 0;
    else
    {
        rEngine->ReportError(ZERR_NOFONT, "IsItalic");
        return false;
    }
}

bool ZFont::IsUnderlined()
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_UNDERLINE) > 0;
    else
    {
        rEngine->ReportError(ZERR_NOFONT, "IsUnderlined");
        return false;
    }
}

int ZFont::Height()
{
    if(rFont)
        return TTF_FontHeight(rFont);
    else
    {
        rEngine->ReportError(ZERR_NOFONT, "GetHeight");
        return 0;
    }
}

int ZFont::LineSkip()
{
    if(rFont)
        return TTF_FontLineSkip(rFont);
    else
    {
        rEngine->ReportError(ZERR_NOFONT, "GetLineSkip");
        return 0;
    }
}

int ZFont::StringWidth(string text)
{
    int w,h;

    if(rFont)
    {
        TTF_SizeText(rFont,text.c_str(),&w,&h);
        return w;
    }
    else
    {
        rEngine->ReportError(ZERR_NOFONT, "GetStringWidth");
        return 0;
    }
}

int ZFont::StringHeight(string text)
{
    int w,h;

    if(rFont)
    {
        TTF_SizeText(rFont,text.c_str(),&w,&h);
        return h;
    }
    else
    {
        rEngine->ReportError(ZERR_NOFONT, "GetStringHeight");
        return 0;
    }
}

}

#endif //USE_SDL_TTF
