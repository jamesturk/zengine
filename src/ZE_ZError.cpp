/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZError.cpp
    \brief Source file for ZError.

    Implementation of ZError, the ZEngine internal error information storage class.
    <br>$Id: ZE_ZError.cpp,v 1.9 2003/06/11 00:15:09 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZError.h"

namespace ZE
{

std::string *ZError::sErrorDesc = NULL; 

void ZError::CreateStringTable()
{
    if(!sErrorDesc)
    {
        sErrorDesc = new std::string[ZERR_LAST]; 
        sErrorDesc[ZERR_NONE] = "No Error. [%s]";
        sErrorDesc[ZERR_SDL_INTERNAL] = "SDL Error. [%s]";
        sErrorDesc[ZERR_SDL_INIT] = "Error Initializing SDL: %s";
        sErrorDesc[ZERR_MIX_INIT] = "Error Initializing SDL_mixer: %s";
        sErrorDesc[ZERR_TTF_INIT] = "Error Initializing SDL_ttf: %s";
        sErrorDesc[ZERR_NET_INIT] = "Error Initializing SDL_net: %s";
        sErrorDesc[ZERR_VIDMODE] = "Error Creating Display: %s";
        sErrorDesc[ZERR_LOAD_IMAGE] = "Failed to load Image: %s";
        sErrorDesc[ZERR_LOAD_SOUND] = "Failed to load Sound: %s"; 
        sErrorDesc[ZERR_LOAD_MUSIC] = "Failed to load Music: %s";
        sErrorDesc[ZERR_LOAD_FONT] = "Failed to load Font: %s";
        sErrorDesc[ZERR_NOIMAGE] = "Called ZImage::%s with no Image loaded.";
        sErrorDesc[ZERR_NOSOUND] = "Called ZSound::%s with no Sound loaded.";
        sErrorDesc[ZERR_NOMUSIC] = "Called ZMusic::%s with no Music loaded.";
        sErrorDesc[ZERR_NOFONT] = "Called ZFont::%s with no Font loaded.";
        sErrorDesc[ZERR_NOSOCKET] = "Called ZClient::%s with no open Socket.";
        sErrorDesc[ZERR_NET_CLIENT] = "ZClient encountered a problem: %s";
        sErrorDesc[ZERR_NET_SERVER] = "ZServer encountered a problem: %s";
    }
}

void ZError::DestroyStringTable()
{
    if(sErrorDesc)
    {
        delete []sErrorDesc;
        sErrorDesc = NULL;
    }
}

ZError::ZError(ZErrorCode code, std::string desc, std::string file, int line)
{
    rCode = code;
    rDescription = desc;
    rFilename = file;
    rLine = line;
}

ZError::~ZError()
{
}

void ZError::Create(ZErrorCode code, std::string desc, std::string file, int line)
{
    rCode = code;
    rDescription = desc;
    rFilename = file;
    rLine = line;
}

ZErrorCode ZError::Code() const
{
    return rCode;
}

std::string ZError::LogString() const
{
    std::string msg;
    
    msg = rDescription.length() ? FormatStr(sErrorDesc[rCode].c_str(),rDescription.c_str()) : sErrorDesc[rCode];

    if(rLine != 0)
        return FormatStr(" -%s(%d): %s\n",rFilename.c_str(),rLine,msg.c_str());
    else if(rFilename.length())
        return FormatStr(" -%s: %s\n",rFilename.c_str(),msg.c_str());
    else
        return FormatStr(" -%s\n",msg.c_str());
}

}
