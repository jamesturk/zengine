/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZAudioBase.h"

#if SND_BACKEND == ZE_AUDIERE

namespace ZE
{

ZAudioBase::ZAudioBase() : 
    rEngine(ZEngine::GetInstance()),
    rDevice(rEngine->GetSoundDevice()),
    rPausePos(0)
{
}

ZAudioBase::~ZAudioBase()
{
}

void ZAudioBase::Play(bool loop)
{
    rStream->play();
    rStream->setRepeat(loop);
}

void ZAudioBase::Pause()
{
    rPausePos = rStream->getPosition();
    rStream->stop();
}

void ZAudioBase::Unpause()
{
    if(rPausePos)
    {
        rStream->setPosition(rPausePos);
        rPausePos = 0;
    }
    rStream->play();
}

void ZAudioBase::Rewind()
{
    rStream->reset();
    rPausePos = 0;
}

void ZAudioBase::Stop()
{
    rStream->stop();
    rStream->reset();
    rPausePos = 0;
}

void ZAudioBase::SetVolume(int volume)
{
    if(volume < 0)
        volume = 0;
    else if(volume > 100)
        volume = 100;

    rStream->setVolume(volume/100.0f);
}

void ZAudioBase::SetPan(float pan)
{
    rStream->setPan(pan);
}

void ZAudioBase::SetPitch(float pitch)
{
    rStream->setPitchShift(pitch);
}

void ZAudioBase::SetPosition(int position)
{
    rPausePos = 0;
    rStream->setPosition(position);
}

void ZAudioBase::SetPosition(float posPercent)
{
    rPausePos = 0;
    rStream->setPosition(static_cast<int>(posPercent*rStream->getLength()));
}

bool ZAudioBase::IsLoaded() const
{
    return (rStream != NULL);
}

bool ZAudioBase::IsPlaying() const
{
    return rStream->isPlaying();
}

bool ZAudioBase::IsPaused() const
{
    return (rPausePos != 0);
}

bool ZAudioBase::IsSeekable() const
{
    return rStream->isSeekable();
}

int ZAudioBase::GetVolume() const
{
    //cast here needs to be accurate, adds .5 to get proper rounding
    return static_cast<int>((rStream->getVolume()*100)+.5);
}

float ZAudioBase::GetPan() const
{
    return rStream->getPan();
}

float ZAudioBase::GetPitch() const
{
    return rStream->getPitchShift();
}

int ZAudioBase::GetPosition() const
{
    return rStream->getPosition();
}

int ZAudioBase::GetLength() const
{
    return rStream->getLength();
}

}

#endif //ZE_AUDIERE
