/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZTimer.h <br>
Description: Header file for core ZEngine Timer Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZTimer.h,v 1.3 2002/12/29 06:50:19 cozman Exp $<br>

    \file ZE_ZTimer.h
    \brief Definition file for ZTimer.

    Definition file for ZTimer, the Timer class for ZEngine.
**/

#ifndef __ze_ztimer_h__
#define __ze_ztimer_h__

#include "ZE_ZObject.h"

namespace ZE
{

/*!
    \brief ZTimer class for Timer use.

    ZTimer timing class, class wraps common features of SDL timer.  Inherited from ZObject and tied to ZEngine main timer.
**/
class ZTimer : public ZObject 
{
    protected:
        //! Paused / Unpaused state of Timer
        bool rPaused;
        //! Using ZEngine timer or SDL global timer.
        bool rUseZEngine;
        //! Total time this timer has been paused.
        Uint32 rPausedTime;
        //! Time this Timer was paused.
        Uint32 rLastPause;

        /*!
            \brief Get time from parent timer.

            Protected method to get time from whichever timer is parent.
            \return Time on parent timer.
        **/
        Uint32 GetParentTime();

    public:

        /*!
            \brief Constructs a new Timer.

            Sets TimePaused to current ZEngine time if useZEngine is true, otherwise uses SDL timer.
            \param useZEngine Tells if timer should use ZEngine or SDL.
        **/
        ZTimer(bool useZEngine=true);

        /*!
            \brief Reset Timer.

            Set Timer back to Zero, will also unpause timer if it was paused.
        **/
        void Reset();

        /*!
            \brief Pause Timer.

            Pause the timer if it is unpaused.
        **/
        void Pause();

        /*!
            \brief Unpause Timer.

            Unpause the timer if it is paused.
        **/
        void Unpause();

        /*!
            \brief Get Time of Timer.

            Get current time accounting for time paused.
            \return Current Timer Time.
        **/
        Uint32 GetTime();

        /*!
            \brief Get paused state.

            Find out paused state of timer.
            \return Paused state for timer.
        **/
        bool IsPaused();
};

}

#endif //__ze_ztimer_h__
