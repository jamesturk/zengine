/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZSound.cpp
    \brief Source file for ZSound.

    Implementation of ZSound, the basic Sound class for ZEngine.
    <br>$Id: ZE_ZSound.cpp,v 1.15 2003/12/24 04:43:36 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZSound.h"

#ifdef USE_SDL_MIXER

namespace ZE
{

//ZSound is almost exactly like ZMusic, when making changes check if that change should
//be applied to ZMusic as well, roughly 90% of the time it should be.

const int ZSound::LoopInfinite = -1;

ZSound::ZSound() :
    rEngine(ZEngine::GetInstance()),
    rSound(NULL),
    rChannelID(-1)    //request channel ID
{
}

ZSound::ZSound(std::string filename) :
    rEngine(ZEngine::GetInstance()),
    rSound(NULL),
    rChannelID(-1)    //request channel ID
{
    Open(filename);
}

ZSound::~ZSound()
{
    Release();
}

void ZSound::Open(std::string filename)
{
    Release();
    rSound = Mix_LoadWAV(filename.c_str());

    if(!rSound)
        rEngine->ReportError(ZERR_ERROR,"Could not load %s",filename.c_str());
}

void ZSound::OpenFromZip(std::string zipname, std::string filename)
{
    SDL_RWops *rw = RWFromZip(zipname,filename);
    if(rw)
    {
        rSound = Mix_LoadWAV_RW(rw,0);
        delete []rw->hidden.mem.base;   //must free buffer
        SDL_FreeRW(rw);
    }

    if(!rSound)
        rEngine->ReportError(ZERR_WARNING,"Could not load %s from %s",filename.c_str(),zipname.c_str());
}

void ZSound::OpenFromZRF(std::string resourceId)
{
    std::string filename = rEngine->GetStringResource("sound",resourceId,"filename");
    if(filename.length())
        Open(filename);
    //else
    //error
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
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::Play with no sound effect loaded.");
}

void ZSound::Pause() const
{
    if(rSound && rChannelID >= 0)
        Mix_Pause(rChannelID);
    else if(!rSound)
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::Pause with no sound effect loaded.");
}

void ZSound::Unpause() const
{
    if(rSound && rChannelID >= 0)
        Mix_Resume(rChannelID);
    else if(!rSound)
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::Unpause with no sound effect loaded.");

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
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::Stop with no sound effect loaded.");
}

void ZSound::SetVolume(int volume)
{
    if(rSound)
        Mix_VolumeChunk(rSound,volume);
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::SetVolume with no sound effect loaded.");
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
            rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::IsPlaying with no sound effect loaded.");
        return false;
    }
}

bool ZSound::IsPaused() const
{
    if(rSound && rChannelID >= 0)
        return Mix_Paused(rChannelID) > 0;
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::IsPaused with no sound effect loaded.");
        return false;
    }
}

int ZSound::Volume() const
{
    if(rSound)
        return Mix_VolumeChunk(rSound,-1);
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::GetVolume with no sound effect loaded.");
        return -1;
    }
}

}

#endif
