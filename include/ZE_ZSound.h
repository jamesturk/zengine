/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                   Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zsound_h__
#define __ze_zsound_h__

#include "ZE_ZEngine.h"
#include "ZE_ZSoundBase.h"

#ifdef USE_AUDIERE

namespace ZE
{

class ZSound : public ZSoundBase
{
    public:
        ZSound();
        ZSound(std::string filename);
        void Open(std::string filename);
};

}

#endif //USE_AUDIERE

#endif //__ze_zsound_h__