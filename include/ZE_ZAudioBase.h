/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zaudiobase_h__
#define __ze_zaudiobase_h__

#include "ZE_ZEngine.h"

#if SND_BACKEND == ZE_AUDIERE

namespace ZE
{

class ZAudioBase
{
    protected:
        ZEngine* rEngine;
        audiere::AudioDevicePtr rDevice;
        audiere::OutputStreamPtr rStream;
        int rPausePos;

    public:
        ZAudioBase();
        virtual ~ZAudioBase();

        virtual void Open(std::string filename)=0;
        virtual void OpenFromZip(std::string zipname, std::string filename)=0;
        virtual void OpenFromZRF(std::string resourceId)=0;
        //void Release();

        void Play(bool loop=false);
        void Pause();
        void Unpause();
        void Rewind();
        void Stop();

        void SetVolume(int volume);
        void SetPan(float pan);
        void SetPitch(float pitch);
        void SetPosition(int position);
        void SetPosition(float posPercent);

        bool IsLoaded() const;
        bool IsPlaying() const;
        bool IsPaused() const;
        bool IsSeekable() const;
        int GetVolume() const;
        float GetPan() const;
        float GetPitch() const;
        int GetPosition() const;
        int GetLength() const;
};

}

#endif //ZE_AUDIERE

#endif //__ze_zaudiobase_h__
