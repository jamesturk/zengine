/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZSound.h <br>
Description: Header file for core ZEngine Sound Wrapper Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZSound.h,v 1.5 2003/02/10 04:07:05 cozman Exp $<br>

    \file ZE_ZSound.h
    \brief Definition file for ZSound.

    Definition file for ZSound, the Sound Effect wrapper for ZEngine.
**/

#ifndef __ze_zsound_h__
#define __ze_zsound_h__

#include "ZE_ZEngine.h"

#ifdef USE_SDL_MIXER

namespace ZE
{

/*!
    \brief ZSound class for playing sound effects. (WAV)

    ZSound music class, class wraps common features for SDL_Mixer's Mix_Chunk.  Inherited from ZObject.
**/
class ZSound
{
    protected:
        //! Pointer to ZEngine Object
        ZEngine* rEngine;
        //! Pointer to music data.
        Mix_Chunk* rSound;
        //! Channel ID Number from SDL_Mixer.
        int rChannelID;

    public:
        //! Static Variable For Infinite loop of sound. (Defined as -1)
        static const int LoopInfinite;

        ///////////////////////
        //Opening and Closing//
        ///////////////////////

        /*!
            \brief Default Constructor.

            Default Constructor, does nothing.
        **/
        ZSound();

        /*!
            \brief Constructor that opens a sound effect file.

            Constructor simply calls ZSound::Open() with same filename. (WAV,MOD,MID,OGG)
            \param filename Sound effect to open.
        **/
        ZSound(string filename);

        /*!
            \brief Destructor, frees memory.

            Destructor calls ZSound::Release().
        **/
        ~ZSound();

        /*!
            \brief Opens a sound effect file.

            Open a music file to be used.
            \param filename Music to open.
        **/
        void Open(string filename);

        /*!
            \brief Release sound effect.

            Release memory held by sample data.
        **/
        void Release();

        /////////////////
        //Play Controls//
        /////////////////

        /*!
            \brief Play currently loaded sound effect.

            Play sound effect, looping loopNum times. (use ZSound::LoopInfinite to loop forever.)  
            If fade is not zero (which it defaults to) music will fade in over specified number of milliseconds.
            \param loopNum Number of times to loop song, defaults to zero.
            \param fadeTime Milliseconds to fade to full volume, defaults to zero for no fade.
        **/
        void Play(int loopNum=0, int fadeTime=0);

        /*!
            \brief Pause sound.

            Pause currently playing sound.
        **/
        void Pause() const;

        /*!
            \brief Unpause sound.

            Unpause currently playing sound.
        **/
        void Unpause() const;

        /*!
            \brief Stop sound.

            Stop currently playing sound, if fadeTime is not zero, fade out over specified time.
            \param fadeTime Milliseconds to fade out over, defaults to zero for immediate stop.
        **/
        void Stop(int fadeTime=0) const;

        /*!
            \brief Change Volume.

            Change volume of currently playing sample. 
            \param volume Volume to change to, can be in a range from 0 to 128.
        **/
        void SetVolume(int volume);

        /////////////
        //Accessors//
        /////////////

        /*!
            \brief Check if file is loaded.

            Check if file is loaded and pointer to data is non-NULL.
            \return Loaded or Unloaded state of data.
        **/
        bool IsLoaded() const;

        /*!
            \brief Check if sound is Playing.

            Check if sound is playing, specifically if it is not stopped. (Paused state should be checked for by IsPaused)
            \return Playing / Not Playing State of sound.
        **/
        bool IsPlaying() const;

        /*!
            \brief Check if sound is Paused.

            Check if sound is "playing" but currently paused.
            \return Paused / Not Paused State of Sound.
        **/
        bool IsPaused() const;

        /*!
            \brief Find Current Volume of Sound Channel.

            Get current volume of sound channel represented as a value from 0-128.
            \return Volume of sound channel, 0-128.
        **/
        int Volume() const;
};


}

#endif //USE_SDL_MIXER

#endif //__ze_zsound_h__
