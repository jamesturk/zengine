/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header:
File: ZE_ZError.cpp <br>
Description: Implementation source file for core ZEngine Error Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZError.cpp,v 1.2 2003/01/16 05:45:58 cozman Exp $<br>

    \file ZE_ZError.cpp
    \brief Source file for ZError.

    Implementation of ZError, the ZEngine internal error information storage class.
**/

#include "ZE_ZError.h"

namespace ZE
{

string ZError::sErrorDesc[] = 
{
    "No Error. [%s]",
    "SDL Error. [%s]",
    "Error Initializing SDL: %s", "Error Initializing SDL_mixer: %s", "Error Initializing SDL_ttf: %s",
    "Error Creating Display: %s",
    "Failed to load Image: %s", "Failed to load Sound: %s", "Failed to load Music: %s", "Failed to load Font: %s", 
    "Called ZImage::%s with no Image loaded.", "Called ZSound::%s with no Sound loaded.", 
    "Called ZMusic::%s with no Music loaded.", "Called ZFont::%s with no Font loaded."
};

ZError::ZError(ZErrorCode code, string desc, string file, int line)
{
    rCode = code;
    rDescription = desc;
    rFilename = file;
    rLine = line;
}

void ZError::Create(ZErrorCode code, string desc, string file, int line)
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

string ZError::LogString() const
{
    string msg;
    
    msg = rDescription.length() ? FormatStr(sErrorDesc[rCode].c_str(),rDescription.c_str()) : sErrorDesc[rCode];

    if(rLine != 0)
        return FormatStr(" -%s(%d): %s\n",rFilename.c_str(),rLine,msg.c_str());
    else if(rFilename.length())
        return FormatStr(" -%s: %s\n",rFilename.c_str(),msg.c_str());
    else
        return FormatStr(" -%s\n",msg.c_str());
}

}
