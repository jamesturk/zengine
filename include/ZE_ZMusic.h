/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zmusic_h__
#define __ze_zmusic_h__

#include "ZE_ZEngine.h"
#include "ZE_ZAudioBase.h"

namespace ZE
{

#if SND_BACKEND == ZE_MIXER

class ZMusic
{
    protected:
        ZEngine* rEngine;
        Mix_Music *rMusic;
    public:
        static const int LoopInfinite;
        
        ZMusic();
        ZMusic(std::string filename);
        virtual ~ZMusic();
        
        void Open(std::string filename);
        //void OpenFromZip(std::string zipname, std::string filename);
        void OpenFromZRF(std::string resourceId);
        void Release();

        void Play(int loopNum=0, int fadeTime=0) const;
        void Pause() const;
        void Unpause() const;
        void Rewind() const;
        void Stop(int fadeTime=0) const;

        void SetVolume(int volume);
        void SetPosition(int position);

        bool IsLoaded() const;
        bool IsPlaying() const;
        bool IsPaused() const;
        bool IsSeekable() const;
        int GetVolume() const;
};

#elif SND_BACKEND == ZE_AUDIERE

class ZMusic : public ZAudioBase
{
    public:
        ZMusic();
        ZMusic(std::string filename);

        void Open(std::string filename);
        void OpenFromZip(std::string zipname, std::string filename);
        void OpenFromZRF(std::string resourceId);
};

#endif //SND_BACKEND

}

#endif //__ze_zmusic_h__
