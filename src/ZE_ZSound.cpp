/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

       The maintainer of this library is James Turk (james@conceptofzero.net) 
            and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header:
File: ZE_ZSound.cpp <br>
Description: Implementation source file for core ZEngine Sound Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZSound.cpp,v 1.2 2002/12/01 07:56:17 cozman Exp $<br>

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
    rSound = NULL;
    rChannelID = -1;    //request channel ID
}

ZSound::ZSound(string filename)
{
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
        LogError("ZSound not initialized in ZSound::Play.");
}

void ZSound::Pause()
{
    if(rSound && rChannelID >= 0)
        Mix_Pause(rChannelID);
    else if(!rSound)
        LogError("ZSound not initialized in ZSound::Pause.");
}

void ZSound::Unpause()
{
    if(rSound && rChannelID >= 0)
        Mix_Resume(rChannelID);
    else if(!rSound)
        LogError("ZSound not initialized in ZSound::Unpause.");
}

void ZSound::Stop(int fadeTime)
{
    if(rSound && rChannelID >= 0)
    {
        if(fadeTime)
            Mix_FadeOutChannel(rChannelID,fadeTime);
        else
            Mix_HaltChannel(rChannelID);
    }
    else if(!rSound)
        LogError("ZSound not initialized in ZSound::Stop.");
}

void ZSound::SetVolume(int volume)
{
    if(rSound)
        Mix_VolumeChunk(rSound,volume);
    else
        LogError("ZSound not initialized in ZSound::SetVolume.");
}

bool ZSound::IsLoaded()
{
    return rSound != NULL;
}

bool ZSound::IsPlaying()
{
    if(rSound && rChannelID >= 0)
        return Mix_Playing(rChannelID) > 0;
    else
    {
        if(rChannelID >= 0)
            LogError("ZSound not initialized in ZSound::IsPlaying().");
        return false;
    }
}

bool ZSound::IsPaused()
{
    if(rSound && rChannelID >= 0)
        return Mix_Paused(rChannelID) > 0;
    else
    {
        LogError("ZSound not initialized in ZSound::IsPaused().");
        return false;
    }
}

int ZSound::Volume()
{
    if(rSound)
        return Mix_VolumeChunk(rSound,-1);
    else
    {
        LogError("ZSound not initialized in ZSound::GetVolume().");
        return -1;
    }
}

}

#endif 
