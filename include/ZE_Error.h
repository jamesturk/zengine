/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_Error.h <br>
Description: Header file for ZEngine Error Handling Functions. <br>
Author(s): James Turk <br>
$Id: ZE_Error.h,v 1.3 2002/12/05 00:00:42 cozman Exp $<br>

    \file ZE_Error.h
    \brief Definition file for ZEngine Error Handling Functions.

    Definition file for ZEngine Error Logging + Formatting functions which are used for internal and external errors.
**/

#ifndef __ze_error_h__
#define __ze_error_h__

#include "ZE_Includes.h"

namespace ZE
{


//////////////////////////////
//Error Logging + Formatting//
//////////////////////////////

/*!
    \brief Error handling Utiltity function.

    Get string describing error given appropriate details.
    \param line Line error occured on.
    \param file Name of file error occured in.
    \param str More detail on error.
    \return String describing error.
**/
string _GetError(int line, string file, string str);

/*!
    \brief Error handling Utiltity function.

    Log error to stderr, describing error given appropriate details.
    \param line Line error occured on.
    \param file Name of file error occured in.
    \param str More detail on error.
**/
void _LogError(int line, string file, string str);

/*! 
    \brief Parses a string and interprets variable arguments, similar to sprintf.

    Takes % identifiers out of fmtstr and parses them, replacing them with cooresponding values 
    in the variable arguments list.  For more detail view stdarg documentation.
    \param fmtstr defines format of resulting string
    \param ... variable number of arguments after fmtstr
    \return string of parsed and combined string
**/
string FormatStr(const char *fmtstr, ...);

/*!
    Creates a string about an error, telling what file it occured in and where, and gives a user defined string as well.
**/
#define GetError(str) _GetError(__LINE__,__FILE__,str)

/*!
    Logs a string about an error, telling what file it occured in and where, and gives a user defined string as well.
**/
#define LogError(str) _LogError(__LINE__,__FILE__,str)

}

#endif //__ze_error_h__
