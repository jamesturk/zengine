/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

//ZSound is almost exactly like ZMusic, when making changes check if that change should
//be applied to ZMusic as well, roughly 95% of the time it should be.

#include "ZE_ZSound.h"

namespace ZE
{

#if SND_BACKEND == ZE_MIXER

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
    else
        rEngine->ReportError(ZERR_WARNING,"Failed to load sound resource '%s'",resourceId.c_str());
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

void ZSound::SetPan(float pan)
{
    if(rSound)
    {
        if(pan == 0)
            Mix_SetPanning(rChannelID,255,255);
        else if(pan < 0)
            Mix_SetPanning(rChannelID, static_cast<Uint8>(128+(128*-pan)), 128);
        else
            Mix_SetPanning(rChannelID, 128, static_cast<Uint8>(128+(128*pan)));
    }
    else
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::SetPan with no sound effect loaded.");
}

void ZSound::SetPosition(int position)
{
    //no-op, non-seekable currently
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

bool ZSound::IsSeekable() const
{
    return false;   //no Mix_Chunks are seekable atm.
}

int ZSound::GetVolume() const
{
    if(rSound)
        return Mix_VolumeChunk(rSound,-1);
    else
    {
        rEngine->ReportError(ZERR_VERBOSE,"Called ZSound::GetVolume with no sound effect loaded.");
        return -1;
    }
}

#elif SND_BACKEND == ZE_AUDIERE

ZSound::ZSound() : ZAudioBase()
{
}

ZSound::ZSound(std::string filename) : ZAudioBase()
{
    Open(filename);
}

void ZSound::Open(std::string filename)
{
    rStream = audiere::OpenSound(rDevice, filename.c_str(), false);
}

void ZSound::OpenFromZip(std::string zipname, std::string filename)
{
    void *buffer;
    int bufSize;

    bufSize = LoadFromZip(zipname, filename, buffer);
    rStream = audiere::OpenSound(rDevice, audiere::hidden::AdrCreateMemoryFile(buffer,bufSize), false);
}

void ZSound::OpenFromZRF(std::string resourceId)
{
    std::string filename = rEngine->GetStringResource("music",resourceId,"filename");
    if(filename.length())
        Open(filename);
    else
        rEngine->ReportError(ZERR_WARNING,"Failed to load music resource '%s'",resourceId.c_str());
}

#endif //SND_BACKEND

}
