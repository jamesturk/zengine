/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZAnimation.cpp
    \brief Source file for ZAnimation.

    Implementation of ZAnimation, ZEngine's class for ZImage based animations.
    <br>$Id: ZE_ZAnimation.cpp,v 1.1 2003/11/25 01:31:37 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZAnimation.h"

namespace ZE
{

ZAnimation::ZAnimation() :
    rEngine(ZEngine::GetInstance()), 
    rAnimImages(NULL),
    rAnimWidth(0),rAnimHeight(0),
    rCurFrame(0),rNumFrames(0),rFrameStep(0),
    rFrameDelay(0),rNextFrameTime(0),
    rLoop(false), rBackwards(false)
{
}

ZAnimation::ZAnimation(ZImage *images, int numFrames, Uint32 frameDelay, bool loop, bool backwards, float width, float height)
{
    rEngine = ZEngine::GetInstance();
    Create(images,numFrames,frameDelay,loop,backwards,width,height);
}

void ZAnimation::Create(ZImage *images, int numFrames, Uint32 frameDelay, bool loop, bool backwards, float width, float height)
{
    rAnimImages = images;
    rNumFrames = numFrames;
    rFrameDelay = frameDelay;
    rLoop = loop;
    rBackwards = backwards;
    rAnimWidth = width;
    rAnimHeight = height;
    Stop();
}

void ZAnimation::SetAnimImages(ZImage *images, int numFrames)
{
    rAnimImages = images;
    rNumFrames = numFrames;
}

void ZAnimation::SetFrameDelay(Uint32 frameDelay)
{
    rFrameDelay = frameDelay;
}

void ZAnimation::SetAnimType(bool loop, bool backwards)
{
    rLoop = loop;
    rBackwards = backwards;
}

void ZAnimation::SetAnimSize(float width, float height)
{
    rAnimWidth = width;
    rAnimHeight = height;
}

void ZAnimation::Start()
{
    rCurFrame = rBackwards ? rNumFrames-1 : 0;
    Unpause();
}

void ZAnimation::Stop()
{
    rCurFrame = rBackwards ? rNumFrames-1 : 0;
    Pause();
}

void ZAnimation::Pause()
{
    rFrameStep = 0;
}

void ZAnimation::Unpause()
{
    rFrameStep = rBackwards ? -1 : 1;
    rNextFrameTime = rEngine->GetTime()+rFrameDelay;
}

void ZAnimation::SetFrame(int frame)
{
    if(frame >= 0 && frame < rNumFrames)
        rCurFrame = frame;
    else if(frame < 0 && frame >= -rNumFrames)
        SetFrame(rNumFrames+frame);
    else
    {
        //invalid frame
    }
}

void ZAnimation::Update()
{
    if(rEngine->GetTime() >= rNextFrameTime)
    {
        rCurFrame += rFrameStep;
        
        if(rCurFrame < 0 || rCurFrame >= rNumFrames)
        {
            if(rLoop)
                rCurFrame = rBackwards ? rNumFrames-1 : 0;
            else
            {
                Stop();
                SetFrame(-1); //set to last frame
            }
        }
        rNextFrameTime = rEngine->GetTime()+rFrameDelay;
    }
}

void ZAnimation::Draw(float x, float y)
{
    if(rAnimImages)
    {
#if (GFX_BACKEND == ZE_OGL)
        rAnimImages[rCurFrame].Resize(rAnimWidth,rAnimHeight);
        rAnimImages[rCurFrame].Draw(x,y);
#elif (GFX_BACKEND == ZE_SDL)
       rAnimImages[rCurFrame].Draw(static_cast<int>(x),static_cast<int>(y));
#endif
    }
}

bool ZAnimation::Stopped()
{
    return rFrameStep == 0;
}

}
