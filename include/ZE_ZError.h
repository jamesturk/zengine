/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZError.h <br>
Description: Header file for ZEngine Error Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZError.h,v 1.1 2003/01/15 05:40:09 cozman Exp $<br>

    \file ZE_ZError.h
    \brief Definition file for ZError.

    Definition file for ZError, the Error logging class for ZEngine.
    This class should never be used by the average user, it is used by ZEngine to store information on an error.
**/

#ifndef __ze_zerror_h__
#define __ze_zerror_h__

#include "ZE_Macros.h"
#include <string>
using namespace std;

namespace ZE
{

enum ZErrorCode 
{ 
    ZERR_NONE, //no error
    ZERR_SDL_INTERNAL,  //other internal error
    ZERR_SDL_INIT, ZERR_MIX_INIT, ZERR_TTF_INIT,    //Initialization errors
    ZERR_VIDMODE, //Error setting video mode.
    ZERR_LOAD_IMAGE, ZERR_LOAD_SOUND, ZERR_LOAD_MUSIC, ZERR_LOAD_FONT,  //Failed Loads
    ZERR_NOIMAGE, ZERR_NOSOUND, ZERR_NOMUSIC, ZERR_NOFONT,   //Using class w/o loading
    ZERR_LAST
};

/*!
    \brief ZError class for describing errors.

    ZError class for storing and printing information on errors.  Inherited from ZObject and tied closely to ZEngine.
    \since 0.8.2
**/
class ZError
{
    protected:
        //! Static Array of Error Identifiers
        static string sErrorDesc[ZERR_LAST];
        //! Error ID.
        ZErrorCode rCode;
        //! Error Description.
        string rDescription;
        //! File which error occured in.
        string rFilename;
        //! Line which error occured on.
        unsigned int rLine;

    public:
        /*!
            \brief Default constructor for ZError.

            Make new ZError object, by default set rCode to ZERR_NONE with no description.
            \param code ZErrorCode to set object to, defaults to ZERR_NONE.
            \param desc Description to use for object, defaults to nothing.
            \param file Optional argument specifying the file the error occured in.
            \param line Optional argument specifying the line the error occured on.
        **/
        ZError(ZErrorCode code=ZERR_NONE, string desc="", string file="", int line=0);

        /*!
            \brief Set members of error object.

            Set new values in ZError object.
            \param code ZErrorCode to set object to.
            \param desc Description to use for object, defaults to nothing.
            \param file Optional argument specifying the file the error occured in.
            \param line Optional argument specifying the line the error occured on.
        **/
        void Create(ZErrorCode code, string desc="", string file="", int line=0);

        /////////////
        //Accessors//
        /////////////

        /*!
            \brief Get ZErrorCode of error.

            Access ZErrorCode of the ZError object.
            \return The error ZErrorCode.
        **/
        ZErrorCode Code();

        /*!
            \brief Get formatted string for log file.

            Return the string to be written to the logfile.  Called by ZEngine in LogError.
        **/
        string LogString();
};

}

#endif //__ze_zerror_h__
