/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZFont.cpp
    \brief Source file for ZFont.

    Implementation of ZFont, the basic Font class for ZEngine.
    <br>$Id: ZE_ZFont.cpp,v 1.17 2003/12/24 04:43:36 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZFont.h"

#ifdef USE_SDL_TTF

namespace ZE
{

ZFont::ZFont() : 
    rEngine(ZEngine::GetInstance()), 
    rFont(NULL)
{
    rColor.r = rColor.g = rColor.b = rColor.unused = 255;
    rBGColor.r = rBGColor.g = rBGColor.b = rBGColor.unused = 0;
}

ZFont::ZFont(std::string filename, int size) : 
    rEngine(ZEngine::GetInstance()), 
    rFont(NULL)
{
    rColor.r = rColor.g = rColor.b = rColor.unused = 255;
    rBGColor.r = rBGColor.g = rBGColor.b = rBGColor.unused = 0;
    Open(filename,size);
}

ZFont::~ZFont()
{
    Release();
}

void ZFont::Open(std::string filename, int size)
{
    Release();
    rFilename = filename;

    rFont = TTF_OpenFont(filename.c_str(),size);

    if(!rFont)
        rEngine->ReportError(ZERR_WARNING,"Could not load %s",filename.c_str());
}

void ZFont::OpenFromZip(std::string zipname, std::string filename, int size)
{
    SDL_RWops *rw;

    Release();
    rZipname = zipname;
    rFilename = filename;
    
    rw = RWFromZip(zipname,filename);

    if(rw)
    {
        rFont = TTF_OpenFontRW(rw,0,size);
        //dont free buffer on ZFont?
        //delete []rw->hidden.mem.base;   //must free buffer
        //SDL_FreeRW(rw);
    }

    if(!rFont)
        rEngine->ReportError(ZERR_WARNING,"Could not load %s from %s",filename.c_str(),zipname.c_str());
}

void ZFont::OpenFromZRF(std::string resourceId)
{
    std::string filename = rEngine->GetStringResource("font",resourceId,"filename");
    int size = rEngine->GetIntResource("font",resourceId,"size");

    if(filename.length() && size)
        Open(filename,size);
    else
        ;//error
}

void ZFont::Release()
{
    FreeFont(rFont);
}

void ZFont::DrawText(std::string text, ZImage &image) const
{
    if(rFont)
    {
        if(text.length() == 0)
            text = " ";
        image.Attach(TTF_RenderText_Blended(rFont, text.c_str(), rColor));
        image.SetAlpha(rColor.unused);  //the images alpha comes from the SetColor a parameter
    }
}

void ZFont::DrawShadedText(std::string text, ZImage &image) const
{
    if(rFont)
    {
        if(text.length() == 0)
            text = " ";
        image.Attach(TTF_RenderText_Shaded(rFont, text.c_str(), rColor, rBGColor));
        image.SetAlpha(rColor.unused);
    }
}

void ZFont::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    rColor.r = r;
    rColor.g = g;
    rColor.b = b;
    rColor.unused = a;  //used in DrawText and DrawBlendedText
}

void ZFont::SetBGColor(Uint8 r, Uint8 g, Uint8 b)
{
    rBGColor.r = r;
    rBGColor.g = g;
    rBGColor.b = b;
}

void ZFont::SetStyle(bool bold, bool italic, bool underline)
{
    int flags=0;

    if(bold)
        flags |= TTF_STYLE_BOLD;
    if(italic)
        flags |= TTF_STYLE_ITALIC;
    if(underline)
        flags |= TTF_STYLE_UNDERLINE;
    if(!flags)
        flags = TTF_STYLE_NORMAL;

    if(rFont)
        TTF_SetFontStyle(rFont,flags);
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::SetStyle with no font loaded.");
}

void ZFont::Resize(int size)
{
    if(rZipname.length())
        OpenFromZip(rZipname,rFilename,size);
    else
        Open(rFilename,size);
}

bool ZFont::IsLoaded() const
{
    return rFont != NULL;
}

bool ZFont::IsBold() const
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_BOLD) > 0;
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::IsBold with no font loaded.");
        return false;
    }
}

bool ZFont::IsItalic() const
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_ITALIC) > 0;
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::IsItalic with no font loaded.");
        return false;
    }
}

bool ZFont::IsUnderlined() const
{
    if(rFont)
        return (TTF_GetFontStyle(rFont) & TTF_STYLE_UNDERLINE) > 0;
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::IsUnderlined with no font loaded.");
        return false;
    }
}

int ZFont::Height() const
{
    if(rFont)
        return TTF_FontHeight(rFont);
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::Height with no font loaded.");
        return 0;
    }
}

int ZFont::LineSkip() const
{
    if(rFont)
        return TTF_FontLineSkip(rFont);
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::LineSkip with no font loaded.");
        return 0;
    }
}

int ZFont::StringWidth(std::string text) const
{
    int w,h;

    if(rFont)
    {
        TTF_SizeText(rFont,text.c_str(),&w,&h);
        return w;
    }
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::StringWidth with no font loaded.");
        return 0;
    }
}

int ZFont::StringHeight(std::string text) const
{
    int w,h;

    if(rFont)
    {
        TTF_SizeText(rFont,text.c_str(),&w,&h);
        return h;
    }
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZFont::StringHeight with no font loaded.");
        return 0;
    }
}

}

#endif //USE_SDL_TTF
