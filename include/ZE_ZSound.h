/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zsound_h__
#define __ze_zsound_h__

#include "ZE_ZEngine.h"
#include "ZE_ZAudioBase.h"

namespace ZE
{

#if SND_BACKEND == ZE_MIXER

class ZSound
{
    protected:
        ZEngine* rEngine;
        Mix_Chunk* rSound;
        int rChannelID;

    public:
        static const int LoopInfinite;

        ZSound();
        ZSound(std::string filename);
        virtual ~ZSound();

        void Open(std::string filename);
        void OpenFromZip(std::string zipname, std::string filename);
        void OpenFromZRF(std::string resourceId);
        void Release();

        void Play(int loopNum=0, int fadeTime=0);
        void Pause() const;
        void Unpause() const;
        void Rewind() const;
        void Stop(int fadeTime=0) const;

        void SetVolume(int volume);
        void SetPan(float pan);
        //void SetPitch(float pitch);
        void SetPosition(int position);
        //void SetPosition(float posPercent);

        bool IsLoaded() const;
        bool IsPlaying() const;
        bool IsPaused() const;
        bool IsSeekable() const;
        int GetVolume() const;
        //float GetPan() const;
        //float GetPitch() const;
        //int GetPosition() const;
        //int GetLength() const;
};

#elif SND_BACKEND == ZE_AUDIERE

class ZSound : public ZAudioBase
{
    public:
        ZSound();
        ZSound(std::string filename);

        void Open(std::string filename);
        void OpenFromZip(std::string zipname, std::string filename);
        void OpenFromZRF(std::string resourceId);
};

#endif //SND_BACKEND

}

#endif //__ze_zsound_h__
