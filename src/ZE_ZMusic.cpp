/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header:
File: ZE_ZMusic.cpp <br>
Description: Implementation source file for core ZEngine Music Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZMusic.cpp,v 1.3 2002/12/29 06:52:07 cozman Exp $<br>

    \file ZE_ZMusic.cpp
    \brief Source file for ZMusic.

    Implementation of ZMusic, the basic Music class for ZEngine.
**/

#include "ZE_ZMusic.h"

#ifdef USE_SDL_MIXER

namespace ZE
{

const int ZMusic::LoopInfinite = -1;

ZMusic::ZMusic()
{
    rMusic = NULL;
}

ZMusic::ZMusic(string filename)
{
    rMusic = NULL;
    Open(filename);
}

ZMusic::~ZMusic()
{
    Release();
}

void ZMusic::Open(string filename)
{
    Release();
    rMusic = rEngine->LoadMusic(filename);
}

void ZMusic::Release()
{
    Mix_HaltMusic();
    FreeMusic(rMusic);
}

void ZMusic::Play(int loopNum, int fadeTime)
{
    if(Mix_PlayingMusic())    //stop currently playing music
        Mix_HaltMusic();

    if(rMusic)
    {
        if(fadeTime)
            Mix_FadeInMusic(rMusic, loopNum, fadeTime);
        else
            Mix_PlayMusic(rMusic, loopNum);
    }
    else
        LogError("ZMusic not initialized in ZMusic::Play.");
}

void ZMusic::Pause()
{
    if(rMusic)
        Mix_PauseMusic();
    else
        LogError("ZMusic not initialized in ZMusic::Pause.");
}

void ZMusic::Unpause()
{
    if(rMusic)
        Mix_ResumeMusic();
    else
        LogError("ZMusic not initialized in ZMusic::Unpause.");
}

void ZMusic::Rewind()
{
    if(rMusic)
        Mix_RewindMusic();
    else
        LogError("ZMusic not initialized in ZMusic::Rewind.");
}

void ZMusic::Stop(int fadeTime)
{
    if(rMusic)
    {
        if(fadeTime)
            Mix_FadeOutMusic(fadeTime);
        else
            Mix_HaltMusic();
    }
    else
        LogError("ZMusic not initialized in ZMusic::Stop.");
}

void ZMusic::SetVolume(int volume)
{
    if(rMusic)
        Mix_VolumeMusic(volume);
    else
        LogError("ZMusic not initialized in ZMusic::SetVolume.");
}

bool ZMusic::IsLoaded()
{
    return rMusic != NULL;
}

bool ZMusic::IsPlaying()
{
    if(rMusic)
        return Mix_PlayingMusic() > 0;
    else
    {
        LogError("ZMusic not initialized in ZMusic::IsPlaying.");
        return false;
    }
}

bool ZMusic::IsPaused()
{
    if(rMusic)
        return Mix_PausedMusic() > 0;
    else
    {
        LogError("ZMusic not initialized in ZMusic::IsPaused.");
        return false;
    }
}

int ZMusic::Volume()
{
    if(rMusic)
        return Mix_VolumeMusic(-1);
    else
    {
        LogError("ZMusic not initialized in ZMusic::GetVolume.");
        return false;
    }
}

}

#endif 
