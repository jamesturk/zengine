/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header:
File: ZE_ZMusic.cpp <br>
Description: Implementation source file for core ZEngine Music Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZMusic.cpp,v 1.1 2002/11/21 05:41:13 cozman Exp $<br>

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
}

ZMusic::ZMusic(string filename)
{
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
    rEngine->FreeMusic(rMusic);
}

void ZMusic::Play(int loopNum, int fadeTime)
{
    if(Mix_PlayingMusic())    //stop currently playing music
        Mix_HaltMusic();

    if(rMusic.music)
    {
        if(fadeTime)
            Mix_FadeInMusic(rMusic.music, loopNum, fadeTime);
        else
            Mix_PlayMusic(rMusic.music, loopNum);
    }
    else
        LogError(FormatStr("ZMusic not initialized in ZMusic::Play(%d,%d), filename: %s.",loopNum,fadeTime,rMusic.filename.c_str()));
}

void ZMusic::Pause()
{
    if(rMusic.music)
        Mix_PauseMusic();
    else
        LogError(FormatStr("ZMusic not initialized in ZMusic::Pause(), filename: %s.",rMusic.filename.c_str()));
}

void ZMusic::Unpause()
{
    if(rMusic.music)
        Mix_ResumeMusic();
    else
        LogError(FormatStr("ZMusic not initialized in ZMusic::Unpause(), filename: %s.",rMusic.filename.c_str()));
}

void ZMusic::Rewind()
{
    if(rMusic.music)
        Mix_RewindMusic();
    else
        LogError(FormatStr("ZMusic not initialized in ZMusic::Rewind(), filename: %s.",rMusic.filename.c_str()));
}

void ZMusic::Stop(int fadeTime)
{
    if(rMusic.music)
    {
        if(fadeTime)
            Mix_FadeOutMusic(fadeTime);
        else
            Mix_HaltMusic();
    }
    else
        LogError(FormatStr("ZMusic not initialized in ZMusic::Stop(%d), filename: %s.",fadeTime,rMusic.filename.c_str()));
}

void ZMusic::SetVolume(int volume)
{
    if(rMusic.music)
        Mix_VolumeMusic(volume);
    else
        LogError(FormatStr("ZMusic not initialized in ZMusic::SetVolume(%d), filename: %s.",volume,rMusic.filename.c_str()));
}

bool ZMusic::IsLoaded()
{
    return rMusic.music != NULL;
}

bool ZMusic::IsPlaying()
{
    if(rMusic.music)
        return Mix_PlayingMusic() > 0;
    else
    {
        LogError(FormatStr("ZMusic not initialized in ZMusic::IsPlaying(), filename: %s.",rMusic.filename.c_str()));
        return false;
    }
}

bool ZMusic::IsPaused()
{
    if(rMusic.music)
        return Mix_PausedMusic() > 0;
    else
    {
        LogError(FormatStr("ZMusic not initialized in ZMusic::IsPaused(), filename: %s.",rMusic.filename.c_str()));
        return false;
    }
}

int ZMusic::GetVolume()
{
    if(rMusic.music)
        return Mix_VolumeMusic(-1);
    else
    {
        LogError(FormatStr("ZMusic not initialized in ZMusic::GetVolume(), filename: %s.",rMusic.filename.c_str()));
        return false;
    }
}

}

#endif 
