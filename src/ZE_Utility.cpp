/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header:
File: ZE_Utility.cpp <br>
Description: Implementation source file for ZEngine Utilities. <br>
Author(s): James Turk <br>
$Id: ZE_Utility.cpp,v 1.2 2003/01/16 04:42:04 cozman Exp $<br>

    \file ZE_ZUtility.cpp
    \brief Source file for ZEngine utility functions.

    Source file containing open utilities for use inside and alongside ZEngine.
**/

#include "ZE_Utility.h"

namespace ZE
{

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