/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zsoundbase_h__
#define __ze_zsoundbase_h__

#include "ZE_ZEngine.h"

#ifdef USE_AUDIERE

namespace ZE
{

class ZSoundBase
{
    protected:
        //ZEngine* rEngine;
        audiere::AudioDevicePtr rDevice;
        audiere::OutputStreamPtr rStream;

    public:
        ZSoundBase();
        virtual ~ZSoundBase();

        virtual void Open(std::string filename)=0;

        void Play(bool loop=false);
        void Stop();

        void SetVolume(float volume);
        void SetPan(float pan);
        void SetPitch(float pitch);
        void SetPosition(int position);
        void SetPosition(float posPercent);

        bool IsLoaded() const;
        bool IsPlaying() const;
        bool IsSeekable() const;
        float GetVolume() const;
        float GetPan() const;
        float GetPitch() const;
        int GetPosition() const;
        int GetLength() const;
};

}

#endif //USE_AUDIERE

#endif //__ze_zsound_h__
