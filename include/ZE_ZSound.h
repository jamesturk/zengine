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

#ifdef USE_SDL_MIXER

namespace ZE
{

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
        void Stop(int fadeTime=0) const;
        void SetVolume(int volume);

        bool IsLoaded() const;
        bool IsPlaying() const;
        bool IsPaused() const;
        int GetVolume() const;
};

}

#endif //USE_SDL_MIXER

#endif //__ze_zsound_h__
