/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZFont.cpp <br>
Description: Implementation source file for core ZEngine Font Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZFont.cpp,v 1.1.1.1 2002/11/21 05:41:13 cozman Exp $<br>

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
    rColor.r = rColor.g = rColor.b = rColor.unused = 255;
    rBGColor.r = rBGColor.g = rBGColor.b = rBGColor.unused = 0;
}

ZFont::ZFont(string filename, int size)
{
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
    rEngine->FreeFont(rFont);
}

void ZFont::DrawText(string text, ZImage &image)
{
    image.Attach(TTF_RenderText_Solid(rFont.font, text.c_str(), rColor));
}

void ZFont::DrawShadedText(string text, ZImage &image)
{
    image.Attach(TTF_RenderText_Shaded(rFont.font, text.c_str(), rColor, rBGColor));
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

    if(rFont.font)
        TTF_SetFontStyle(rFont.font,flags);
    else
        LogError(FormatStr("ZFont not initialized in ZFont::SetStyle(), filename: %s.",rFont.filename.c_str()));
}

void ZFont::Resize(int size)
{
    Open(rFont.filename,size);
}

bool ZFont::IsLoaded()
{
    return rFont.font != NULL;
}

bool ZFont::IsBold()
{
    if(rFont.font)
        return (TTF_GetFontStyle(rFont.font) & TTF_STYLE_BOLD) > 0;
    else
    {
        LogError(FormatStr("ZFont not initialized in ZFont::IsBold(), filename: %s.",rFont.filename.c_str()));
        return false;
    }
}

bool ZFont::IsItalic()
{
    if(rFont.font)
        return (TTF_GetFontStyle(rFont.font) & TTF_STYLE_ITALIC) > 0;
    else
    {
        LogError(FormatStr("ZFont not initialized in ZFont::IsItalic(), filename: %s.",rFont.filename.c_str()));
        return false;
    }
}

bool ZFont::IsUnderlined()
{
    if(rFont.font)
        return (TTF_GetFontStyle(rFont.font) & TTF_STYLE_UNDERLINE) > 0;
    else
    {
        LogError(FormatStr("ZFont not initialized in ZFont::IsUnderlined(), filename: %s.",rFont.filename.c_str()));
        return false;
    }
}

int ZFont::GetHeight()
{
    if(rFont.font)
        return TTF_FontHeight(rFont.font);
    else
    {
        LogError(FormatStr("ZFont not initialized in ZFont::GetHeight(), filename: %s.",rFont.filename.c_str()));
        return 0;
    }
}

int ZFont::GetLineSkip()
{
    if(rFont.font)
        return TTF_FontLineSkip(rFont.font);
    else
    {
        LogError(FormatStr("ZFont not initialized in ZFont::GetLineSkip(), filename: %s.",rFont.filename.c_str()));
        return 0;
    }
}

int ZFont::GetStringWidth(string text)
{
    int w,h;

    if(rFont.font)
    {
        TTF_SizeText(rFont.font,text.c_str(),&w,&h);
        return w;
    }
    else
    {
        LogError(FormatStr("ZFont not initialized in ZFont::GetStringWidth(%s), filename: %s.",text.c_str(),rFont.filename.c_str()));
        return 0;
    }
}

int ZFont::GetStringHeight(string text)
{
    int w,h;

    if(rFont.font)
    {
        TTF_SizeText(rFont.font,text.c_str(),&w,&h);
        return h;
    }
    else
    {
        LogError(FormatStr("ZFont not initialized in ZFont::GetStringHeight(%s), filename: %s.",text.c_str(),rFont.filename.c_str()));
        return 0;
    }
}

}

#endif //USE_SDL_TTF
