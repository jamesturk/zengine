/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zengine_h__
#define __ze_zengine_h__

#include "ZE_Defines.h"
#include "ZE_Utility.h"
#include "ZE_Includes.h"
#include "ZE_ZRandGen.h"
#include "VersionInfo.h"

namespace ZE
{

class ZRect;

enum ZErrorSeverity
{
    ZERR_VERBOSE,
    ZERR_DEPRECIATED,
    ZERR_WARNING,
    ZERR_ERROR,
    ZERR_CRITICAL,
    ZERR_NOTE
};

enum ZErrorLogStyle
{
    ZLOG_NONE,
    ZLOG_TEXT,
    ZLOG_HTML
};

class ZEngine
{
    public:
        static VersionInfo Version;

    private:
        static ZEngine *sInstance;
        SDL_Surface *mScreen;
        bool mFullscreen;
        bool mInitialized;
        bool mPaused;
        bool mUnpauseOnActive;
        Uint32 mNextUpdate;
        Uint32 mLastPause;
        Uint32 mPausedTime;
        Uint32 mLastTime;
        double mSecPerFrame;
        bool mNeedReload;
        bool mActive;
        bool mQuit;
        Uint8 *mKeyIsPressed;
        bool mKeyPress[SDLK_LAST];
        int mMouseX;
        int mMouseY;
        Uint8 mMouseB;
        SDL_EventFilter mEventFilter;
        ZErrorLogStyle mLogStyle;
        ZErrorSeverity mMinSeverity;
        std::FILE *mErrlog;
        ZRandGen mRandGen;
        TiXmlDocument rZRF;
#if SND_BACKEND == ZE_MIXER
        int mMixerFrequency;
        Uint16 mMixerFormat;
        int mMixerChannels;
        int mMixerChunksize;
#elif SND_BACKEND == ZE_AUDIERE
        audiere::AudioDevicePtr mAudiereDevice;
#endif

        ZEngine();

        TiXmlElement* FindElement(std::string type, std::string id);

    public:
        static ZEngine* GetInstance();
        static void ReleaseInstance();

        void InitErrorLog(ZErrorLogStyle logStyle=ZLOG_HTML, std::string logFile="errlog.html", ZErrorSeverity severityFilter=ZERR_VERBOSE);
#if SND_BACKEND == ZE_MIXER
        void InitAudio(int frequency=MIX_DEFAULT_FREQUENCY, bool stereo=true, Uint16 format=MIX_DEFAULT_FORMAT, int chunksize=4096);
#elif SND_BACKEND == ZE_AUDIERE
        bool InitAudio();
#endif
        bool CreateDisplay(int width, int height, int bpp, bool fullscreen, std::string title="ZEngine Application", std::string icon="");
        void CloseDisplay();
        void ToggleFullscreen();

        void Update();
        void ClearDisplay(Uint8 red=0, Uint8 green=0, Uint8 blue=0);

#if (GFX_BACKEND == ZE_OGL)       
        void SetGL2D();
#endif //GFX_BACKEND

        void Delay(Uint32 milliseconds);
        Uint32 GetTime();
        void PauseTimer();
        void UnpauseTimer();
        bool TimerIsPaused();

        double GetFrameSpeed();
        double GetFramerate();
        
        bool IsActive();

        void RequestQuit();
        bool QuitRequested();

        void SetReloadNeed(bool state);
        bool ImagesNeedReload();

        void SetKeyRepeatRate(int rate);
        bool KeyIsPressed(SDLKey key);
        bool KeyPress(SDLKey key);
        void HideCursor();
        void ShowCursor();
        int MouseX();
        int MouseY();
        bool LButtonPressed();
        bool RButtonPressed();
        bool MButtonPressed();
        bool MouseInRect(const SDL_Rect &rect);
        bool MouseInRect(const ZRect &rect);
        void CheckEvents();
        void SetEventFilter(SDL_EventFilter filter);
        
        void ReportError(ZErrorSeverity type, std::string desc, ...);        
        void WriteLog(std::string str, ...);

        void SeedRandGen(unsigned long seed);
        unsigned int Rand(unsigned int max);
        unsigned long Rand(unsigned long max);
        int Rand(int min, int max);
        long Rand(long min, long max);
        float Rand(float min, float max);
        double Rand(double min, double max);        
        double RandDouble();

        void SetResourceFile(std::string filename);
        std::string GetStringResource(std::string type, std::string id, std::string element);
        int GetIntResource(std::string type, std::string id, std::string element);       
        double GetDoubleResource(std::string type, std::string id, std::string element);

#if SND_BACKEND == ZE_AUDIERE
        audiere::AudioDevicePtr GetSoundDevice();
#endif
        SDL_Surface* GetDisplayPointer();
        bool DisplayCreated();
        int DisplayWidth();
        int DisplayHeight();
        int DisplayDepth();
        bool IsFullscreen();
};

}

#endif //__ze_zengine_h__
