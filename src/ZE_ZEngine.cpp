/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZEngine.cpp <br>
Description: Implementation source file for ZEngine library main singleton class. <br>
Author(s): James Turk <br>
$Id: ZE_ZEngine.cpp,v 1.1.1.1 2002/11/21 05:41:12 cozman Exp $<br>

    \file ZE_ZEngine.cpp
    \brief Central source file for ZEngine.

    Actual implementation of ZEngine singleton class at heart of ZEngine.
**/

#include "ZE_ZEngine.h"

namespace ZE
{

ZEngine *ZEngine::sInstance=NULL;

ZEngine::ZEngine()
{
    mWidth = 640;
    mHeight = 480;
    mBPP = 16;
    mFullscreen = true;

#ifdef USE_SDL_MIXER 
    mRate = 22050;
    mStereo = false;
#endif

    mScreen = NULL;

    mActive = mQuit = false;
    mKeyPressed = NULL;
    mMouseX = mMouseY = 0;
    mMouseB = 0;

    mUnpauseOnActive = mPaused = false;
    mLastPause = mPausedTime = mLastTime = 0;
    mSecPerFrame = 0.0;
}

ZEngine* ZEngine::GetInstance()
{
    if(!sInstance)
        sInstance = new ZEngine;

    return sInstance;
}

void ZEngine::ReleaseInstance()
{
    if(sInstance)
    {
        sInstance->CloseWindow();
        delete sInstance;
    }
    sInstance = NULL;
}

string ZEngine::GetVersion()
{
    return VERSION;
}

void ZEngine::SetupDisplay(int width, int height, int bpp, bool fullscreen)
{
    mWidth = width;
    mHeight = height;
    mBPP = bpp;
    mFullscreen = fullscreen;
}

#ifdef USE_SDL_MIXER
void ZEngine::SetupSound(int rate, bool stereo)
{
    mRate = rate;
    mStereo = stereo;
}
#endif

void ZEngine::CreateWindow(string title, string icon)
{
    Uint32 flags = SDL_DOUBLEBUF|SDL_HWPALETTE;
    ImageData iconImg;
    SDL_VideoInfo *videoInfo;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) < 0) 
    {
        LogError(FormatStr("SDL could not be Initialized: %s", SDL_GetError()));
        //CloseWindow();
    }
    
#ifdef USE_SDL_MIXER
    Mix_OpenAudio(mRate, AUDIO_S16SYS, mStereo?2:1, 4096);    //Open Audio Stream (Stereo?2:1 is conditional for number of channels)
#endif 

    videoInfo = const_cast<SDL_VideoInfo*>(SDL_GetVideoInfo());

    //check capabilities and use what we can//
    if(videoInfo->hw_available)
        flags |= SDL_HWSURFACE;
    else
        flags |= SDL_SWSURFACE;
    if(videoInfo->blit_hw)
        flags |= SDL_HWACCEL;

    //Window Manager settings//
    if(!icon.length())
        SDL_WM_SetCaption(title.c_str(),NULL);
    else
    {
        SDL_WM_SetCaption(title.c_str(),icon.c_str());
        iconImg = LoadImage(icon);
        SDL_WM_SetIcon(iconImg.image,NULL);
        FreeImage(iconImg);
    }

    //create SDL screen//
    if(mFullscreen)
        flags |= SDL_FULLSCREEN;
    mScreen = SDL_SetVideoMode(mWidth, mHeight, mBPP, flags);

    if(!mScreen)
    {
        LogError(FormatStr("Unable to set video mode %dx%d (%dBpp): %s",mWidth,mHeight,mBPP,SDL_GetError()));
        CloseWindow();
    }
    mKeyPressed = SDL_GetKeyState(NULL);

#ifdef USE_SDL_TTF
    TTF_Init();
#endif

    mLastTime = mPausedTime = SDL_GetTicks();
    mActive = true;
}

void ZEngine::CloseWindow()
{
#ifdef USE_SDL_TTF
    TTF_Quit();
#endif

#ifdef USE_SDL_MIXER
    Mix_CloseAudio();
#endif

#ifdef USE_PHYSFS
    PHYSFS_deinit();
#endif

    SDL_Quit();
}

SDL_Surface *ZEngine::GetDisplay()
{
    return mScreen;
}

void ZEngine::UpdateScreen()
{
    SDL_Flip(mScreen);

    mSecPerFrame = (GetTime()-mLastTime)/1000.0;
    mLastTime = GetTime();
}

Uint32 ZEngine::MapColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDL_MapRGBA(mScreen->format,r,g,b,a);
}

void ZEngine::Clear(Uint32 color, SDL_Rect *rect)
{
    SDL_FillRect(mScreen,rect,color);
}

void ZEngine::Sleep(Uint32 milliseconds)
{
    SDL_Delay(milliseconds);
}

Uint32 ZEngine::GetTime()
{
    if(mPaused)
        return SDL_GetTicks() - (mPausedTime +  (SDL_GetTicks() - mLastPause));
    else
        return SDL_GetTicks() - mPausedTime;
}

void ZEngine::PauseTimer()
{
    if(!mPaused)
    {
        mLastPause = SDL_GetTicks();
        mPaused = true;
    }
}

void ZEngine::UnpauseTimer()
{
    if(mPaused)
    {
        mPausedTime += (SDL_GetTicks() - mLastPause);
        mPaused = false;
    }
}

double ZEngine::GetFrameTime()
{
    return mSecPerFrame;
}

bool ZEngine::IsPaused()
{
    return mPaused;
}

bool ZEngine::IsActive()
{
    return mActive;
}

void ZEngine::RequestQuit()
{
    mQuit = true;    //simply request a quit, nothing more
}

bool ZEngine::QuitRequested()
{
    return mQuit;
}

bool ZEngine::KeyIsPressed(SDLKey key)
{
    return mKeyPressed[key] == 1;
}

void ZEngine::HideCursor()
{
    SDL_ShowCursor(SDL_DISABLE);
}

void ZEngine::ShowCursor()
{
    SDL_ShowCursor(SDL_ENABLE);
}

int ZEngine::GetMouseX()
{
    return mMouseX;
}

int ZEngine::GetMouseY()
{
    return mMouseY;
}

bool ZEngine::LButtonPressed()
{
    return (mMouseB & SDL_BUTTON_LMASK) > 0;
}

bool ZEngine::RButtonPressed()
{
    return (mMouseB & SDL_BUTTON_RMASK) > 0;
}

bool ZEngine::MouseInRect(SDL_Rect *rect)
{
    return (mMouseX >= rect->x && mMouseX <= rect->x+rect->w && 
        mMouseY >= rect->y && mMouseY <= rect->y+rect->h);
}

void ZEngine::CheckEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_VIDEOEXPOSE:
            case SDL_ACTIVEEVENT:
                if(event.active.state & SDL_APPACTIVE || event.active.state & SDL_APPINPUTFOCUS)
                {
                    if( (event.type == SDL_ACTIVEEVENT && event.active.gain == 1) || event.type == SDL_VIDEOEXPOSE)
                    {
                        mActive = true;
                        if(mUnpauseOnActive)
                            UnpauseTimer();
                    }
                    else
                    {
                        mActive = mUnpauseOnActive = false;
                        if(!mPaused)
                        {
                            mUnpauseOnActive = true;
                            PauseTimer();
                        }
                        else
                            mUnpauseOnActive = false;
                    }
                }
                break;
            case SDL_QUIT:
                mQuit = true;
                break;
            default:
                break;
        }
    }

    mKeyPressed = SDL_GetKeyState(NULL);        //recommended but not needed (says Sam)

    if(mKeyPressed[SDLK_F4] && (mKeyPressed[SDLK_LALT] || mKeyPressed[SDLK_RALT]))
        mQuit = true;

    mMouseB = SDL_GetMouseState(&mMouseX,&mMouseY);
}

#ifdef USE_PHYSFS

void ZEngine::InitPhysFS(string argv)
{
    string::size_type pos;
    PHYSFS_init(argv.c_str());

    pos = argv.rfind(PHYSFS_getDirSeparator());
    if(pos != string::npos)
        AddPhysFSDir(argv.substr(0,pos));
}

void ZEngine::AddPhysFSDir(string dir)
{
    PHYSFS_addToSearchPath(dir.c_str(),0);
}

#endif //USE_PHYSFS

ImageData ZEngine::LoadImage(string filename)
{
    ImageData img;

//using physfs//
#ifdef USE_PHYSFS
    SDL_RWops *rw;
    rw = PHYSFSRWOPS_openRead(filename.c_str());
    if(!rw)
        LogError(FormatStr("PhysFS RWops failed: %s",SDL_GetError()));
#ifdef USE_SDL_IMAGE
    img.image = IMG_Load_RW(rw,0);
#else
    img.image = SDL_LoadBMP_RW(rw,0);
#endif    //USE_SDL_IMAGE
    SDL_FreeRW(rw);
//end using physfs//

//Just SDL//
#else
#ifdef USE_SDL_IMAGE
    img.image = IMG_Load(filename.c_str());
#else
    img.image = SDL_LoadBMP(filename.c_str());
#endif    //USE_SDL_IMAGE
#endif    //USE_PHYSFS

    if(!img.image)
    {
        img.filename = FormatStr("LoadImage could not load %s.",filename.c_str());
        LogError(img.filename);
    }
    else
        img.filename = filename;

    return img;
}

void ZEngine::FreeImage(ImageData &image)
{
    if(image.image)
    {
        SDL_FreeSurface(image.image);
        image.image = NULL;
        image.filename = "free";
    }
}

#ifdef USE_SDL_MIXER

SoundData ZEngine::LoadSound(string filename)
{
    SoundData snd;

#ifdef USE_PHYSFS
    SDL_RWops *rw;
    rw = PHYSFSRWOPS_openRead(filename.c_str());
    snd.sound = Mix_LoadWAV_RW(rw,0);
    SDL_FreeRW(rw);
#else
    snd.sound = Mix_LoadWAV(filename.c_str());
#endif //USE_PHYSFS

    if(!snd.sound)
    {
        snd.filename = FormatStr("LoadSound could not load %s.",filename.c_str());
        LogError(snd.filename);
    }
    else
        snd.filename = filename;

    return snd;
}

void ZEngine::FreeSound(SoundData &sound)
{
    if(sound.sound)
    {
        Mix_FreeChunk(sound.sound);
        sound.sound = NULL;
        sound.filename = "free";
    }
}

MusicData ZEngine::LoadMusic(string filename)
{
    MusicData mus;

//Currently SDL_Mixer doesn't support Music from a RW
//#ifdef USE_PHYSFS
//    SDL_RWops *rw;
//    rw = PHYSFSRWOPS_openRead(filename.c_str());
//    mus.music = Mix_LoadMUS_RW(filename.c_str(),0);
//    SDL_FreeRW(rw);
//#else
    mus.music = Mix_LoadMUS(filename.c_str());
//#endif //USE_PHYSFS
    
    if(!mus.music)
    {
        mus.filename = FormatStr("LoadMusic could not load %s.",filename.c_str());
        LogError(mus.filename);
    }
    else
        mus.filename = filename;

    return mus;
}

void ZEngine::FreeMusic(MusicData &music)
{
    if(music.music)
    {
        Mix_FreeMusic(music.music);
        music.music = NULL;
        music.filename = "free";
    }
}

#endif

#ifdef USE_SDL_TTF

FontData ZEngine::LoadFont(string filename, int size)
{
    FontData fnt;

//Currently SDL_ttf doesn't support Fonts from a RW
//#ifdef USE_PHYSFS
//    SDL_RWops *rw;
//    rw = PHYSFSRWOPS_openRead(filename.c_str());
//    fnt.font = TTF_OpenFontRW(rw,0);
//    SDL_FreeRW(rw);
//#else
    fnt.font = TTF_OpenFont(filename.c_str(),size);
//#endif //USE_PHYSFS

    if(!fnt.font)
    {
        fnt.filename = FormatStr("LoadFont could not load %s.",filename.c_str());
        LogError(fnt.filename);
    }
    else
        fnt.filename = filename;
    
    return fnt;
}

void ZEngine::FreeFont(FontData &font)
{
    if(font.font)
    {
        TTF_CloseFont(font.font);
        font.font = NULL;
        font.filename = "free";
    }
}


#endif 

int ZEngine::GetWidth()
{
    return mWidth;
}

int ZEngine::GetHeight()
{
    return mHeight;
}

int ZEngine::GetBPP()
{
    return mBPP;
}

bool ZEngine::IsFullscreen()
{
    return mFullscreen;
}

}
