/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZTimer.cpp <br>
Description: Implementation source file for core ZEngine Timer Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZTimer.cpp,v 1.1.1.1 2002/11/21 05:41:13 cozman Exp $<br>

    \file ZE_ZTimer.cpp
    \brief Source file for ZTimer.

    Implementation of ZTimer, the basic Timer class for ZEngine.
**/

#include "ZE_ZTimer.h"

namespace ZE
{

Uint32 ZTimer::GetParentTime()
{
    if(rUseZEngine)
        return rEngine->GetTime();
    else
        return SDL_GetTicks();
}

ZTimer::ZTimer(bool useZEngine)
{
    rUseZEngine = useZEngine;
    rPaused = false;
    Reset();
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
        rPausedTime += (GetParentTime()-rLastPause);
        rPaused = false;
    }
}

Uint32 ZTimer::GetTime()
{
    if(rPaused)
        return GetParentTime() - (rPausedTime +  (GetParentTime() - rLastPause));
    else
        return GetParentTime() - rPausedTime;
}

bool ZTimer::IsPaused()
{
    return rPaused;
}

}
