/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_ztimer_h__
#define __ze_ztimer_h__

#include "ZE_ZEngine.h"

namespace ZE
{

class ZTimer
{
    protected:
        ZEngine* rEngine;
        bool rPaused;
        bool rUseZEngine;
        Uint32 rPausedTime;
        Uint32 rLastPause;

        Uint32 GetParentTime() const;

    public:
        ZTimer(bool useZEngine=true);
        virtual ~ZTimer();

        void Reset();
        void Pause();
        void Unpause();

        Uint32 GetTime() const;
        bool IsPaused() const;
};

}

#endif //__ze_ztimer_h__
