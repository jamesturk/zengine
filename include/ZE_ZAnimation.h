/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZAnimation.h
    \brief Definition file for ZAnimation.

    Definition file for ZAnimation, a class for animations using ZImage.
    <br>$Id: ZE_ZAnimation.h,v 1.1 2003/11/25 01:31:36 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zanimation_h__
#define __ze_zanimation_h__

#include "ZE_ZEngine.h"
#include "ZE_ZImage.h"

namespace ZE
{

enum ZAnimationType
{
    ZANIM_ONCE,
    ZANIM_LOOP,
    ZANIM_REV_ONCE,
    ZANIM_REV_LOOP
};

class ZAnimation
{
    protected:
        ZEngine *rEngine;
        ZImage *rAnimImages;
        float rAnimWidth;
        float rAnimHeight;
        int rCurFrame;
        int rNumFrames;
        int rFrameStep;
        Uint32 rFrameDelay;
        Uint32 rNextFrameTime;
        bool rLoop;
        bool rBackwards;
    public:
        ZAnimation();
        ZAnimation(ZImage *images, int numFrames, Uint32 frameDelay, bool loop=false, bool backwards=false, float width=0, float height=0);

        void Create(ZImage *images, int numFrames, Uint32 frameDelay, bool loop=false, bool backwards=false, float width=0, float height=0);
        void SetAnimImages(ZImage *images, int numFrames);
        void SetFrameDelay(Uint32 frameDelay);
        void SetAnimType(bool loop, bool backwards);
        void SetAnimSize(float width, float height);

        void Start();
        void Stop();
        void Pause();
        void Unpause();
        void SetFrame(int frame);

        void Update();
        void Draw(float x, float y);

        bool Stopped();
};

}

#endif //__ze_zanimation_h__
