/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Error.cpp <br>
Description: Implementation source file for ZEngine error logging utility functions. <br>
Author(s): James Turk <br>
$Id: ZE_Error.cpp,v 1.1 2002/11/21 05:41:12 cozman Exp $<br>

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
