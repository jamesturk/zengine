/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZSoundBase.h"

#ifdef USE_AUDIERE

namespace ZE
{

ZSoundBase::ZSoundBase()
{
    rDevice = ZEngine::GetInstance()->GetSoundDevice();
}

ZSoundBase::~ZSoundBase()
{
}

void ZSoundBase::Play(bool loop)
{
    rStream->play();
    rStream->setRepeat(true);
}

void ZSoundBase::Stop()
{
    rStream->stop();
}

void ZSoundBase::SetVolume(float volume)
{
    rStream->setVolume(volume);
}

void ZSoundBase::SetPan(float pan)
{
    rStream->setPan(pan);
}

void ZSoundBase::SetPitch(float pitch)
{
    rStream->setPitchShift(pitch);
}

void ZSoundBase::SetPosition(int position)
{
    rStream->setPosition(position);
}

void ZSoundBase::SetPosition(float posPercent)
{
    rStream->setPosition(static_cast<int>(posPercent*rStream->getLength()));
}

bool ZSoundBase::IsLoaded() const
{
    return (rStream != NULL);
}

bool ZSoundBase::IsPlaying() const
{
    return rStream->isPlaying();
}

bool ZSoundBase::IsSeekable() const
{
    return rStream->isSeekable();
}

float ZSoundBase::GetVolume() const
{
    return rStream->getVolume();
}

float ZSoundBase::GetPan() const
{
    return rStream->getPan();
}

float ZSoundBase::GetPitch() const
{
    return rStream->getPitchShift();
}

int ZSoundBase::GetPosition() const
{
    return rStream->getPosition();
}

int ZSoundBase::GetLength() const
{
    return rStream->getLength();
}


}

#endif
