/*!
    \file ZEngine.h
    \brief Header file for ZEngine.

    Header file for ZEngine Game Engine from Concept of Zero, this is the file that programs that wish to 
    utilize ZEngine should include.
    <br>$Id: ZEngine.h,v 1.32 2003/09/24 01:49:52 cozman Exp $<br>
    \author James Turk
**/

/*!
    \mainpage ZEngine Documentation

    \author James Turk
    \version 0.8.4
    \date July 12, 2003

    \section ZEngine About ZEngine
    <br>
    &nbsp;&nbsp;&nbsp;&nbsp;-ZEngine is designed to provide a powerful yet easy to use 2D game engine in a well designed 
    Object Oriented manner, and uses cross platform libraries such as SDL and OpenGL. (ZEngine can use SDL_ttf,SDL_image,
    and SDL_mixer all of which are cross platform as well as Open Source.)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;-It is licensed under a BSD-style license, and anyone is free to suggest or implement changes 
    to be added to the Engine, as well as modify the engine to their own needs or use it however they like.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;-ZEngine now uses OpenGL rather than SDL to do 2D drawing, thus increasing the uses of the engine
    and making the engine much faster in all test cases, and the engine was tested for memory leaks with MSVC and is known
    to have no leaks.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;-The ZEngine website : http://zengine.sourceforge.net/.<br>
    &nbsp;&nbsp;&nbsp;&nbsp;-The ZEngine tutorials : http://zengine.sourceforge.net/tutorials/.<br>
    
    \section Licensing Licensing
    <br>
<pre>        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://zengine.sourceforge.net
    </pre>
    \section Authors Contributing Authors
    <br>
    James Turk <a href="mailto:james@conceptofzero.net">james@conceptofzero.net</a> - Core Engine, Design, Docs, and Classes<br>
    Gamer Tazar <a href="mailto:tazar@conceptofzero.net">tazar@conceptofzero.net</a> - OpenGL assistance<br>
    Sean <a href="mailto:sean@conceptofzero.net">sean@conceptofzero.net</a> - MSVC++6 Project Files<br>
    Kevin Watters <a href="mailto:kwatters@adelphia.net">kwatters@adelphia.net</a> - Fix to ZImage::SetColorKey<br>
    Atani <a href="mailto:atani@atani-software.net">atani@atani-software.net</a> - Revised Linux Build System<br>
**/

#ifndef __zengine_h__
#define __zengine_h__

#include "ZE_Defines.h"
#include "ZE_ZEngine.h"
#include "ZE_Utility.h"
#include "ZE_ZImage.h"
#include "ZE_ZTimer.h"
#include "ZE_ZConfigFile.h"
#include "ZE_ZRect.h"
#include "ZE_ZRandGen.h"
#include "ZE_ZBaseParticleSystem.h"
#include "ZE_ZSimpleParticleSystem.h"
#ifdef USE_SDL_TTF
#include "ZE_ZFont.h"
#endif
#ifdef USE_SDL_MIXER
#include "ZE_ZSound.h"
#include "ZE_ZMusic.h"
#endif
#ifdef USE_SDL_NET
#include "ZE_ZClient.h"
#include "ZE_ZServer.h"
#endif

#endif //__zengine_h__
