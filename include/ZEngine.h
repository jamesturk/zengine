/*!
\par File Header:
File: ZEngine.h <br>
Description: Public Header File for ZEngine. <br>
Author(s): James Turk <br>
$Id: ZEngine.h,v 1.2 2002/11/28 23:18:54 cozman Exp $<br>

    \file ZEngine.h
    \brief Header file for ZEngine.

    Header file for ZEngine Game Engine from Concept of Zero, this is the file that programs that wish to 
    utilize ZEngine should include.
**/

/*!
    \mainpage ZEngine Documentation

    \author James Turk
    \version 0.7.5
    \date 28 November, 2002

    \section ZEngine About ZEngine
    <br>
    ZEngine is designed to wrap common interfaces of the SDL API in an Object Oriented manner.  It is licensed under 
    a very liberal BSD-style license, and anyone is free to suggest or implement changes to be added to the Engine.  In addition
    ZEngine hopes to provide a core engine which can be used to develop a game without having to rewrite large amounts
    of code. 
    
    \section Licensing Licensing
    <br><pre>
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
     </pre>
    \section Authors Contributing Authors
    James Turk <a href="james@conceptofzero.net">james@conceptofzero.net</a> - Core Engine and Classes for Data Types
**/

#include "ZE_ZEngine.h"
#include "ZE_ZImage.h"
#include "ZE_ZTimer.h"
#include "ZE_ZConfigFile.h"
#include "ZE_ZRect.h"
#ifdef USE_SDL_TTF
#include "ZE_ZFont.h"
#endif
#ifdef USE_SDL_MIXER
#include "ZE_ZSound.h"
#include "ZE_ZMusic.h"
#endif
