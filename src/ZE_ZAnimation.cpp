/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZAnimation.h"

namespace ZE
{

ZAnimation::ZAnimation() :
    rEngine(ZEngine::GetInstance()), 
    rAnimImages(NULL),
    rCurFrame(0),rNumFrames(0),rFrameStep(0),
    rFrameDelay(0),rNextFrameTime(0),
    rAnimType(ZANIM_NONE), rBackwards(false)
{
}

ZAnimation::ZAnimation(ZImage *images, int numFrames, Uint32 frameDelay, ZAnimType type, bool backwards)
{
    rEngine = ZEngine::GetInstance();
    Create(images,numFrames,frameDelay,type,backwards);
}

ZAnimation::~ZAnimation()
{
}

void ZAnimation::Create(ZImage *images, int numFrames, Uint32 frameDelay, ZAnimType type, bool backwards)
{
    rAnimImages = images;
    rNumFrames = numFrames;
    rFrameDelay = frameDelay;
    rAnimType = type;
    rBackwards = backwards;
    Reset();
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

void ZAnimation::SetAnimType(ZAnimType type, bool backwards)
{
    rAnimType = type;
    rBackwards = backwards;
}

void ZAnimation::Reset()
{
    rFrameStep = 0;
    rCurFrame = rBackwards ? rNumFrames-1 : 0;
}

void ZAnimation::Start()
{
    if(rAnimType != ZANIM_NONE)
        rFrameStep = rBackwards ? -1 : 1;
    else
        rFrameStep = 0;
    rNextFrameTime = rEngine->GetTime()+rFrameDelay;
}

void ZAnimation::Pause()
{
    rFrameStep = 0;
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
    //if not paused/stopped and time to update has come
    if(rFrameStep && rEngine->GetTime() >= rNextFrameTime)
    {
        rCurFrame += rFrameStep;
        
        if(rCurFrame < 0 || rCurFrame >= rNumFrames)
        {
            switch(rAnimType)
            {
                case ZANIM_ONCE:
                    Pause();
                    rCurFrame = rBackwards ? 0 : rNumFrames-1;
                    break;
                case ZANIM_LOOP:
                    rCurFrame = rBackwards ? rNumFrames-1 : 0;
                    break;
                case ZANIM_REVERSE:
                    rBackwards = !rBackwards;
                    rCurFrame = rBackwards ? rNumFrames-2 : 1;  //second to last or second frame
                    rFrameStep *= -1;
                    break;
                case ZANIM_NONE:
                default:
                    Reset();
                    //error?
                    break;
            }
        }
        rNextFrameTime = rEngine->GetTime()+rFrameDelay;
    }
}

void ZAnimation::Draw(float x, float y) const
{
    if(rAnimImages)
        rAnimImages[rCurFrame].Draw(x,y);
    //else
    //error: images not loaded
}

bool ZAnimation::IsRunning() const
{
    return rFrameStep != 0;
}

}
