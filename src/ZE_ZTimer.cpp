/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZTimer.h"

namespace ZE
{

Uint32 ZTimer::GetParentTime() const
{
    if(rUseZEngine)
        return rEngine->GetTime();
    else
        return SDL_GetTicks();
}

ZTimer::ZTimer(bool useZEngine) :
    rEngine(ZEngine::GetInstance()),
    rUseZEngine(useZEngine)
{
    Reset();	//initializes other members
}

ZTimer::~ZTimer()
{
}

void ZTimer::Reset()
{
    rLastPause = rPausedTime = GetParentTime();
    rPaused = false;
}

void ZTimer::Pause()
{
    if(!rPaused)
    {
        rLastPause = GetParentTime();
        rPaused = true;
    }
}

void ZTimer::Unpause()
{
    if(rPaused)
    {
        //when unpausing update the total paused time by that pause
        rPausedTime += (GetParentTime()-rLastPause);
        rPaused = false;
    }
}

Uint32 ZTimer::GetTime() const
{
    if(rPaused) //when paused timer adjusted to subtract currently paused time
        return GetParentTime() - (rPausedTime +  (GetParentTime() - rLastPause));
    else
        return GetParentTime() - rPausedTime;   //paused time is the cotal amt of time the program has been paused
}

bool ZTimer::IsPaused() const
{
    return rPaused;
}

}
