/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_main.cpp
    \brief Source file which defines default ZEngine entry point.

    The entry point 'main' defined in this file simply does the initial creation and freeing of ZEngine.
    An application that defines main overrides this main, so backwards compatibility is not broken, however as of 0.8.5 ZE_main is the 
    expected entry point of ZEngine applications.
    <br>$Id: ZE_main.cpp,v 1.3 2003/09/24 02:03:18 cozman Exp $<br>
    \author James Turk
**/

#ifdef USE_PHYSFS

#include "ZEngine.h"

/*!
    \brief ZEngine entry point.
    Preferred entry point for ZEngine programs, when using the ZE_main instead of main
    there is no need to call the old InitPhysFS nor ZEngine::ReleaseInstance.
    \param argc number of arguments 
    \param argv argument array
**/
extern int ZE_main(int argc, char *argv[]);


/*!
    \brief Program entry point.
    Predefined main which does needed initialization and then calls ZE_main, making it the ZEngine entry point.
    \param argc number of arguments 
    \param argv argument array
**/
int main(int argc, char *argv[])
{
    ZE::ZEngine *engine = ZE::ZEngine::GetInstance();
    int ret;

#ifdef USE_PHYSFS
    engine->InitPhysFS(argv[0]);
#endif
    ret = ZE_main(argc,argv);

    ZE::ZEngine::ReleaseInstance(); //release engine instance
    return ret;
}

#endif //USE_PHYSFS