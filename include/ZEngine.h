/*!
\par File Header:
File: ZEngine.h <br>
Description: Public Header File for ZEngine. <br>
Author(s): James Turk <br>
$Id: ZEngine.h,v 1.13 2002/12/29 07:15:30 cozman Exp $<br>

    \file ZEngine.h
    \brief Header file for ZEngine.

    Header file for ZEngine Game Engine from Concept of Zero, this is the file that programs that wish to 
    utilize ZEngine should include.
**/

/*!
    \mainpage ZEngine Documentation

    \author James Turk
    \version 0.8.0
    \date December 29, 2002

    \section ZEngine About ZEngine
    <br>
    ZEngine is designed to provide a powerful yet easy to use 2D game engine an Object Oriented manner. <br>
    It is licensed under a BSD-style license, and anyone is free to suggest or implement changes to be added to the Engine,
    as well as change the engine to their own needs or use it however they like.<br>
    ZEngine now uses OpenGL rather than SDL to do 2D drawing, thus increasing the uses of the engine
    and making the engine much faster in all test cases, and the engine was tested for memory leaks with MSVC and is known
    to have no leaks.<br>
    The ZEngine website can be found at http://zengine.sourceforge.net/.<br>
    
    \section Licensing Licensing
    <br>
<pre>        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
    </pre>
    \section Authors Contributing Authors
    <br>
    James Turk <a href="mailto:james@conceptofzero.net">james@conceptofzero.net</a> - Core Engine, Design, Docs, and Classes<br>
    Gamer Tazar <a href="mailto:tazar@conceptofzero.net">tazar@conceptofzero.net</a> - OpenGL assistance<br>
**/

#ifndef __zengine_h__
#define __zengine_h__

#include "ZE_ZEngine.h"
#include "ZE_Macros.h"
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

#endif //__zengine_h__