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
$Id: ZE_ZFont.cpp,v 1.3 2002/12/29 06:52:07 cozman Exp $<br>

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
        LogError("ZFont not initialized in ZFont::SetStyle.");
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
        LogError("ZFont not initialized in ZFont::IsBold.");
        return false;
    }
}

bool ZFont::IsItalic()
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_ITALIC) > 0;
    else
    {
        LogError("ZFont not initialized in ZFont::IsItalic.");
        return false;
    }
}

bool ZFont::IsUnderlined()
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_UNDERLINE) > 0;
    else
    {
        LogError("ZFont not initialized in ZFont::IsUnderlined.");
        return false;
    }
}

int ZFont::Height()
{
    if(rFont)
        return TTF_FontHeight(rFont);
    else
    {
        LogError("ZFont not initialized in ZFont::GetHeight.");
        return 0;
    }
}

int ZFont::LineSkip()
{
    if(rFont)
        return TTF_FontLineSkip(rFont);
    else
    {
        LogError("ZFont not initialized in ZFont::GetLineSkip.");
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
        LogError("ZFont not initialized in ZFont::GetStringWidth.");
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
        LogError("ZFont not initialized in ZFont::GetStringHeight.");
        return 0;
    }
}

}

#endif //USE_SDL_TTF
