/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZMusic.h"

namespace ZE
{

#if SND_BACKEND == ZE_MIXER

const int ZMusic::LoopInfinite = -1;    //constant for infinite, as used by SDL_Mixer

ZMusic::ZMusic() : 
    rEngine(ZEngine::GetInstance()),
    rMusic(NULL)
{
}

ZMusic::ZMusic(std::string filename) : 
    rEngine(ZEngine::GetInstance()),
    rMusic(NULL)
{
    Open(filename);
}

ZMusic::~ZMusic()
{
    Release();
}

void ZMusic::Open(std::string filename)
{
    Release();

    rMusic = Mix_LoadMUS(filename.c_str());

    if(!rMusic)
        rEngine->ReportError(ZERR_WARNING,"Could not load %s",filename.c_str());
}

void ZMusic::OpenFromZRF(std::string resourceId)
{
    std::string filename = rEngine->GetStringResource("music",resourceId,"filename");
    if(filename.length())
        Open(filename);
    else
        rEngine->ReportError(ZERR_WARNING,"Failed to load music resource '%s'",resourceId.c_str());
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
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::Play with no music loaded.");
}

void ZMusic::Pause() const
{
    if(rMusic)
        Mix_PauseMusic();
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::Pause with no music loaded.");
}

void ZMusic::Unpause() const
{
    if(rMusic)
        Mix_ResumeMusic();
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::Unpause with no music loaded.");
}

void ZMusic::Rewind() const
{
    if(rMusic)
        Mix_RewindMusic();
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::Rewind with no music loaded.");
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
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::Stop with no music loaded.");
}

void ZMusic::SetVolume(int volume)
{
    if(rMusic)
        Mix_VolumeMusic(volume);
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::SetVolume with no music loaded.");
}

void ZMusic::SetPosition(int position)
{
    if(rMusic)
    {
        if(!IsSeekable() || Mix_SetMusicPosition(static_cast<double>(position)) == -1)
            rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::SetPosition on non-seekable file.");
    }
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::SetPosition with no music loaded.");
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
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::IsPlaying with no music loaded.");
        return false;
    }
}

bool ZMusic::IsPaused() const
{
    if(rMusic)
        return Mix_PausedMusic() > 0;
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::IsPaused with no music loaded.");
        return false;
    }
}

bool ZMusic::IsSeekable() const
{
    Mix_MusicType type = Mix_GetMusicType(rMusic);
    if(type == MUS_MOD || type == MUS_OGG || type == MUS_MP3)
        return true;
    else
        return false;
}

int ZMusic::GetVolume() const
{
    if(rMusic)
        return Mix_VolumeMusic(-1);
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZMusic::GetVolume with no music loaded.");
        return false;
    }
}

#elif SND_BACKEND == ZE_AUDIERE

ZMusic::ZMusic() : ZAudioBase()
{
}

ZMusic::ZMusic(std::string filename) : ZAudioBase()
{
    Open(filename);
}

void ZMusic::Open(std::string filename)
{
    rStream = audiere::OpenSound(rDevice, filename.c_str(), true);
}

void ZMusic::OpenFromZip(std::string zipname, std::string filename)
{
    void *buffer;
    int bufSize;

    bufSize = LoadFromZip(zipname, filename, buffer);
    rStream = audiere::OpenSound(rDevice, audiere::hidden::AdrCreateMemoryFile(buffer,bufSize), true);
}

void ZMusic::OpenFromZRF(std::string resourceId)
{
    std::string filename = rEngine->GetStringResource("music",resourceId,"filename");
    if(filename.length())
        Open(filename);
    else
        rEngine->ReportError(ZERR_WARNING,"Failed to load music resource '%s'",resourceId.c_str());
}

#endif //SND_BACKEND

}
