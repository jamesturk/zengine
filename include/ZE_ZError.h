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
$Id: ZE_ZError.h,v 1.6 2003/02/10 04:40:16 cozman Exp $<br>

    \file ZE_ZError.h
    \brief Definition file for ZError.

    Definition file for ZError, the Error logging class for ZEngine.
    This class should never be used by the average user, it is used by ZEngine to store information on an error.
**/

#ifndef __ze_zerror_h__
#define __ze_zerror_h__

#include "ZE_Utility.h"
#include <string>
using namespace std;

namespace ZE
{

//! Enumeration of ZEngine error codes.
/*!
    All the error codes currently possibly by ZEngine, note that ZERR_LAST is not used as an error code, but instead
    as a range check on the others.
**/
enum ZErrorCode 
{
    ZERR_NONE,          /*!< No error has occured.  */
    ZERR_SDL_INTERNAL,  /*!< Error internal to SDL has occured, usually more detail is given by SDL. */
    ZERR_SDL_INIT,      /*!< Error Initializing SDL. */
    ZERR_MIX_INIT,      /*!< Error Initializing SDL_mixer. */
    ZERR_TTF_INIT,      /*!< Error Initializing SDL_ttf. */
    ZERR_VIDMODE,       /*!< Error setting up the display. */
    ZERR_LOAD_IMAGE,    /*!< Error loading an image. */
    ZERR_LOAD_SOUND,    /*!< Error loading a sound sample. */
    ZERR_LOAD_MUSIC,    /*!< Error loading music. */
    ZERR_LOAD_FONT,     /*!< Error loading a font. */
    ZERR_NOIMAGE,       /*!< Error trying to use a ZImage without properly loading an image. */
    ZERR_NOSOUND,       /*!< Error trying to use a ZSound without properly loading a sound. */
    ZERR_NOMUSIC,       /*!< Error trying to use a ZMusic without properly loading music. */
    ZERR_NOFONT,        /*!< Error trying to use a ZFont without properly loading a font. */
    ZERR_LAST           /*!< Value used as range index, not a valid error code. */
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
        static string *sErrorDesc;
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
            \brief Construct string table for error strings.

            Constructs a string table for errors, enabling ZEngine to properly delete the table on exit.
        **/
        static void CreateStringTable();

        /*!
            \brief Destroy string table of error strings.

            Properly delete the string table, freeing all memory used by the strings.
        **/
        static void DestroyStringTable();

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
            \brief Virtual Destructor.

            Virtual destructor making future inheritance safe.
        **/
        virtual ~ZError();

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
        ZErrorCode Code() const;

        /*!
            \brief Get formatted string for log file.

            Return the string to be written to the logfile.  Called by ZEngine in LogError.
        **/
        string LogString() const;
};

}

#endif //__ze_zerror_h__
