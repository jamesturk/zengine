/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZSound.h"
#include "ZE_ZSoundBase.h"

#ifdef USE_AUDIERE

namespace ZE
{

ZSound::ZSound()
{
}

ZSound::ZSound(std::string filename) : ZSoundBase()
{
    Open(filename);
}

void ZSound::Open(std::string filename)
{
    rStream = audiere::OpenSound(rDevice, filename.c_str(), false);
}

}

#endif
