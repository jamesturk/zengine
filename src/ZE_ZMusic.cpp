/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZMusic.h"

#ifdef USE_AUDIERE

namespace ZE
{

ZMusic::ZMusic()
{
}

ZMusic::ZMusic(std::string filename) : ZSoundBase()
{
    Open(filename);
}

void ZMusic::Open(std::string filename)
{
    rStream = audiere::OpenSound(rDevice, filename.c_str(), true);
}

}

#endif
