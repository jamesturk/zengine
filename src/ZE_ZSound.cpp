/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header:
File: ZE_ZSound.cpp <br>
Description: Implementation source file for core ZEngine Sound Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZSound.cpp,v 1.6 2003/02/10 04:02:39 cozman Exp $<br>

    \file ZE_ZSound.cpp
    \brief Source file for ZSound.

    Implementation of ZSound, the basic Sound class for ZEngine.
**/

#include "ZE_ZSound.h"

#ifdef USE_SDL_MIXER

namespace ZE
{

const int ZSound::LoopInfinite = -1;

ZSound::ZSound()
{
    rEngine = ZEngine::GetInstance();
    rSound = NULL;
    rChannelID = -1;    //request channel ID
}

ZSound::ZSound(string filename)
{
    rEngine = ZEngine::GetInstance();
    rSound = NULL;
    rChannelID = -1;    //request channel ID
    Open(filename);
}

ZSound::~ZSound()
{
    Release();
}

void ZSound::Open(string filename)
{
    Release();
    rSound = rEngine->LoadSound(filename);
}

void ZSound::Release()
{
    if(rChannelID >= 0)
        Mix_HaltChannel(rChannelID);
    FreeSound(rSound);
}

void ZSound::Play(int loopNum, int fadeTime)
{
    if(rChannelID >= 0 && Mix_Playing(rChannelID))    //stop currently playing sound
        Mix_HaltChannel(rChannelID);

    if(rSound)
    {
        if(fadeTime)
            rChannelID = Mix_FadeInChannel(rChannelID, rSound, loopNum, fadeTime);
        else
            rChannelID = Mix_PlayChannel(rChannelID, rSound, loopNum);
    }
    else if(!rSound)
        rEngine->ReportError(ZERR_NOSOUND, "Play");
}

void ZSound::Pause() const
{
    if(rSound && rChannelID >= 0)
        Mix_Pause(rChannelID);
    else if(!rSound)
        rEngine->ReportError(ZERR_NOSOUND, "Pause");
}

void ZSound::Unpause() const
{
    if(rSound && rChannelID >= 0)
        Mix_Resume(rChannelID);
    else if(!rSound)
        rEngine->ReportError(ZERR_NOSOUND, "Unpause");
}

void ZSound::Stop(int fadeTime) const
{
    if(rSound && rChannelID >= 0)
    {
        if(fadeTime)
            Mix_FadeOutChannel(rChannelID,fadeTime);
        else
            Mix_HaltChannel(rChannelID);
    }
    else if(!rSound)
        rEngine->ReportError(ZERR_NOSOUND, "Stop");
}

void ZSound::SetVolume(int volume)
{
    if(rSound)
        Mix_VolumeChunk(rSound,volume);
    else
        rEngine->ReportError(ZERR_NOSOUND, "SetVolume");
}

bool ZSound::IsLoaded() const
{
    return rSound != NULL;
}

bool ZSound::IsPlaying() const
{
    if(rSound && rChannelID >= 0)
        return Mix_Playing(rChannelID) > 0;
    else
    {
        if(rChannelID >= 0)
            rEngine->ReportError(ZERR_NOSOUND, "IsPlaying");
        return false;
    }
}

bool ZSound::IsPaused() const
{
    if(rSound && rChannelID >= 0)
        return Mix_Paused(rChannelID) > 0;
    else
    {
        rEngine->ReportError(ZERR_NOSOUND, "IsPaused");
        return false;
    }
}

int ZSound::Volume() const
{
    if(rSound)
        return Mix_VolumeChunk(rSound,-1);
    else
    {
        rEngine->ReportError(ZERR_NOSOUND, "GetVolume");
        return -1;
    }
}

}

#endif 
