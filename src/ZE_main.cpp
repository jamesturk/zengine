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
    <br>$Id: ZE_main.cpp,v 1.1 2003/09/09 02:45:58 cozman Exp $<br>
    \author James Turk
**/

#include "ZEngine.h"

extern int ZE_main(int argc, char *argv[]);

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

