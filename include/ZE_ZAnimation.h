/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zanimation_h__
#define __ze_zanimation_h__

#include "ZE_ZEngine.h"
#include "ZE_ZImage.h"

namespace ZE
{

enum ZAnimType
{
    ZANIM_NONE,
    ZANIM_ONCE,
    ZANIM_LOOP,
    ZANIM_REVERSE
};


class ZAnimation
{
    protected:
        ZEngine *rEngine;
        ZImage *rAnimImages;
        int rCurFrame;
        int rNumFrames;
        int rFrameStep;
        Uint32 rFrameDelay;
        Uint32 rNextFrameTime;
        ZAnimType rAnimType;
        bool rBackwards;

    public:
        ZAnimation();
        ZAnimation(ZImage *images, int numFrames, Uint32 frameDelay, ZAnimType type, bool backwards=false);
        virtual ~ZAnimation();

        void Create(ZImage *images, int numFrames, Uint32 frameDelay, ZAnimType type, bool backwards=false);
        void SetAnimImages(ZImage *images, int numFrames);
        void SetFrameDelay(Uint32 frameDelay);
        void SetAnimType(ZAnimType type, bool backwards=false);

        void Reset();
        void Start();
        void Pause();
        void SetFrame(int frame);

        void Update();
        void Draw(float x, float y) const;

        bool IsRunning() const;
};

}

#endif //__ze_zanimation_h__
