/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZMusic.h <br>
Description: Header file for core ZEngine Music Wrapper Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZMusic.h,v 1.1.1.1 2002/11/21 05:41:11 cozman Exp $<br>

    \file ZE_ZMusic.h
    \brief Definition file for ZMusic.

    Definition file for ZMusic, the Music file wrapper for ZEngine.
**/

#ifndef __ze_zmusic_h__
#define __ze_zmusic_h__

#include "ZE_ZObject.h"

#ifdef USE_SDL_MIXER

namespace ZE
{

/*!
    \brief ZMusic class for playing full length music (eg. ogg or wav).

    ZMusic music class, class wraps common features for SDL_Mixer's Mix_Music.  Inherited from ZObject.
**/
class ZMusic : public ZObject 
{
    protected:
        //! Class containing music data and music filename.
        MusicData rMusic;

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
        ZMusic();

        /*!
            \brief Constructor that opens a music file.

            Constructor simply calls ZMusic::Open() with same filename. (WAV,MOD,MID,OGG)
            \param filename Music to open.
        **/
        ZMusic(string filename);

        /*!
            \brief Destructor, frees memory.

            Destructor calls ZMusic::Release().
        **/
        ~ZMusic();

        /*!
            \brief Opens a music file.

            Open a music file to be used.
            \param filename Music to open.
        **/
        void Open(string filename);

        /*!
            \brief Release music.

            Release memory held by music data.
        **/
        void Release();

        /////////////////
        //Play Controls//
        /////////////////

        /*!
            \brief Play currently loaded music.

            Play music currently loaded in ZMusic, looping loopNum times. (use ZMusic::LoopInfinite to loop forever.)  
            If fade is not zero (which it defaults to) music will fade in over specified number of milliseconds.
            \param loopNum Number of times to loop song, defaults to zero.
            \param fadeTime Milliseconds to fade to full volume, defaults to zero for no fade.
        **/
        void Play(int loopNum=0, int fadeTime=0);

        /*!
            \brief Pause music.

            Pause currently playing music.
        **/
        void Pause();

        /*!
            \brief Unpause music.

            Unpause currently paused music.
        **/
        void Unpause();

        /*!
            \brief Rewind music.

            Rewind music to beginning.
        **/
        void Rewind();

        /*!
            \brief Stop music.

            Stop currently playing music, if fadeTime is not zero, fade out over specified time.
            \param fadeTime Milliseconds to fade out over, defaults to zero for immediate stop.
        **/
        void Stop(int fadeTime=0);

        /*!
            \brief Change Volume.

            Change volume of currently playing music. 
            \param volume Volume to change to, can be in a range from 0 to 128
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
        bool IsLoaded();

        /*!
            \brief Check if music is Playing.

            Check if music is playing, specifically if it is not stopped. (Paused state should be checked for by IsPaused)
            \return Playing / Not Playing State of Music.
        **/
        bool IsPlaying();

        /*!
            \brief Check if music is Paused.

            Check if music is "playing" but currently paused.
            \return Paused / Not Paused State of Music.
        **/
        bool IsPaused();

        /*!
            \brief Find Current Volume of Music.

            Get current volume of music represented as a value from 0-128.
            \return Volume of music, 0-128.
        **/
        int GetVolume();
};


}

#endif //USE_SDL_MIXER

#endif //__ze_zmusic_h__
