/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZMusic.cpp
    \brief Source file for ZMusic.

    Implementation of ZMusic, the basic Music class for ZEngine.
    <br>$Id: ZE_ZMusic.cpp,v 1.9 2003/06/11 00:15:10 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZMusic.h"

#ifdef USE_SDL_MIXER

namespace ZE
{

const int ZMusic::LoopInfinite = -1;

ZMusic::ZMusic()
{
    rEngine = ZEngine::GetInstance();
    rMusic = NULL;
}

ZMusic::ZMusic(std::string filename)
{
    rEngine = ZEngine::GetInstance();
    rMusic = NULL;
    Open(filename);
}

ZMusic::~ZMusic()
{
    Release();
}

void ZMusic::Open(std::string filename)
{
    Release();
    rMusic = rEngine->LoadMusic(filename);
}

void ZMusic::Release()
{
    Mix_HaltMusic();
    FreeMusic(rMusic);
}

void ZMusic::Play(int loopNum, int fadeTime) const
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
        rEngine->ReportError(ZERR_NOMUSIC, "Play");
}

void ZMusic::Pause() const
{
    if(rMusic)
        Mix_PauseMusic();
    else
        rEngine->ReportError(ZERR_NOMUSIC, "Pause");
}

void ZMusic::Unpause() const
{
    if(rMusic)
        Mix_ResumeMusic();
    else
        rEngine->ReportError(ZERR_NOMUSIC, "Unpause");
}

void ZMusic::Rewind() const
{
    if(rMusic)
        Mix_RewindMusic();
    else
        rEngine->ReportError(ZERR_NOMUSIC, "Rewind");
}

void ZMusic::Stop(int fadeTime) const
{
    if(rMusic)
    {
        if(fadeTime)
            Mix_FadeOutMusic(fadeTime);
        else
            Mix_HaltMusic();
    }
    else
        rEngine->ReportError(ZERR_NOMUSIC, "Stop");
}

void ZMusic::SetVolume(int volume)
{
    if(rMusic)
        Mix_VolumeMusic(volume);
    else
        rEngine->ReportError(ZERR_NOMUSIC, "SetVolume");
}

bool ZMusic::IsLoaded() const
{
    return rMusic != NULL;
}

bool ZMusic::IsPlaying() const
{
    if(rMusic)
        return Mix_PlayingMusic() > 0;
    else
    {
        rEngine->ReportError(ZERR_NOMUSIC, "IsPlaying");
        return false;
    }
}

bool ZMusic::IsPaused() const
{
    if(rMusic)
        return Mix_PausedMusic() > 0;
    else
    {
        rEngine->ReportError(ZERR_NOMUSIC, "IsPaused");
        return false;
    }
}

int ZMusic::Volume() const
{
    if(rMusic)
        return Mix_VolumeMusic(-1);
    else
    {
        rEngine->ReportError(ZERR_NOMUSIC, "GetVolume");
        return false;
    }
}

}

#endif 
