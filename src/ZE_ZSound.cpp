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
$Id: ZE_ZSound.cpp,v 1.1 2002/11/21 05:41:13 cozman Exp $<br>

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
    rChannelID = -1;    //request channel ID
}

ZSound::ZSound(string filename)
{
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
    rEngine->FreeSound(rSound);
}

void ZSound::Play(int loopNum, int fadeTime)
{
    if(rChannelID >= 0 && Mix_Playing(rChannelID))    //stop currently playing sound
        Mix_HaltChannel(rChannelID);

    if(rSound.sound)
    {
        if(fadeTime)
            rChannelID = Mix_FadeInChannel(rChannelID, rSound.sound, loopNum, fadeTime);
        else
            rChannelID = Mix_PlayChannel(rChannelID, rSound.sound, loopNum);
    }
    else if(!rSound.sound)
        LogError(FormatStr("ZSound not initialized in ZSound::Play(%d,%d), filename: %s.",loopNum,fadeTime,rSound.filename.c_str()));
}

void ZSound::Pause()
{
    if(rSound.sound && rChannelID >= 0)
        Mix_Pause(rChannelID);
    else if(!rSound.sound)
        LogError(FormatStr("ZSound not initialized in ZSound::Pause(), filename: %s.",rSound.filename.c_str()));
}

void ZSound::Unpause()
{
    if(rSound.sound && rChannelID >= 0)
        Mix_Resume(rChannelID);
    else if(!rSound.sound)
        LogError(FormatStr("ZSound not initialized in ZSound::Unpause(), filename: %s.",rSound.filename.c_str()));
}

void ZSound::Stop(int fadeTime)
{
    if(rSound.sound && rChannelID >= 0)
    {
        if(fadeTime)
            Mix_FadeOutChannel(rChannelID,fadeTime);
        else
            Mix_HaltChannel(rChannelID);
    }
    else if(!rSound.sound)
        LogError(FormatStr("ZSound not initialized in ZSound::Stop(%d), filename: %s.",fadeTime,rSound.filename.c_str()));
}

void ZSound::SetVolume(int volume)
{
    if(rSound.sound)
        Mix_VolumeChunk(rSound.sound,volume);
    else
        LogError(FormatStr("ZSound not initialized in ZSound::SetVolume(%d), filename: %s.",volume,rSound.filename.c_str()));
}

bool ZSound::IsLoaded()
{
    return rSound.sound != NULL;
}

bool ZSound::IsPlaying()
{
    if(rSound.sound && rChannelID >= 0)
        return Mix_Playing(rChannelID) > 0;
    else
    {
        if(rChannelID >= 0)
            LogError(FormatStr("ZSound not initialized in ZSound::IsPlaying(), filename: %s.",rSound.filename.c_str()));
        return false;
    }
}

bool ZSound::IsPaused()
{
    if(rSound.sound && rChannelID >= 0)
        return Mix_Paused(rChannelID) > 0;
    else
    {
        LogError(FormatStr("ZSound not initialized in ZSound::IsPaused(), filename: %s.",rSound.filename.c_str()));
        return false;
    }
}

int ZSound::GetVolume()
{
    if(rSound.sound)
        return Mix_VolumeChunk(rSound.sound,-1);
    else
    {
        LogError(FormatStr("ZSound not initialized in ZSound::GetVolume(), filename: %s.",rSound.filename.c_str()));
        return false;
    }
}

}

#endif 
