/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Error.cpp <br>
Description: Implementation source file for ZEngine error logging utility functions. <br>
Author(s): James Turk <br>
$Id: ZE_Error.cpp,v 1.3 2002/12/29 06:52:07 cozman Exp $<br>

    \file ZE_Error.cpp
    \brief Source file for error logging utilities.

    Error logging utilities for ZEngine and programs making use of ZEngine.
**/

#include "ZE_Error.h"

namespace ZE
{

string _GetError(int line, string file, string str)
{
    return FormatStr("%s (Line %d)\n Message Was: %s \n",file.c_str(),line,str.c_str());
}

void _LogError(int line, string file, string str)
{
    string errstr = _GetError(line,file,str);
#ifdef DEBUG_STREAM
    fprintf(stderr,errstr.c_str());        //this line writes the actual debug info
#endif
}

string FormatStr(const char *fmtstr, ...)
{
    char buf[512];
    va_list args;

    va_start(args,fmtstr);
    vsprintf(buf, fmtstr, args);
    va_end(args);
    return buf;
}

}
