/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZEngine.cpp <br>
Description: Implementation source file for ZEngine library main singleton class. <br>
Author(s): James Turk <br>
$Id: ZE_ZEngine.cpp,v 1.25 2003/01/27 04:33:34 cozman Exp $<br>

    \file ZE_ZEngine.cpp
    \brief Central source file for ZEngine.

    Actual implementation of ZEngine singleton class, the core of ZEngine.
**/

#include "ZE_ZEngine.h"

namespace ZE
{

ZEngine *ZEngine::sInstance=NULL;

ZEngine::ZEngine()
{
    mInitialized = false;
    mWidth = 640;
    mHeight = 480;
    mBPP = 16;
    mFullscreen = true;

#ifdef USE_SDL_MIXER 
    mRate = 22050;
    mStereo = false;
#endif
    mNeedReload = false;

    mScreen = NULL;

    mActive = mQuit = false;
    mKeyIsPressed = NULL;
    mMouseX = mMouseY = 0;
    mMouseB = 0;

    for(int k = 0; k < SDLK_LAST; k++)
        mKeyPress[k] = false;

    mUnpauseOnActive = mPaused = false;
    mDesiredFramerate = 0;
    mNextUpdate = mLastPause = mPausedTime = mLastTime = 0;
    mSecPerFrame = 0.0;

    ZError::CreateStringTable();
    mLogAllErrors = true;
    mErrlog = stderr;
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
        ZError::DestroyStringTable();
        sInstance->CloseDisplay();
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

bool ZEngine::CreateDisplay(string title, string icon)
{
    Uint32 flags=0;
    SDL_Surface *iconImg;
    bool status=true;   //status of setup, only true if everything went flawless
    int bpp;
    int rgb_size[3];

    if(!mInitialized)
    {
        if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) < 0) 
        {
            ReportError(ZERR_SDL_INIT,SDL_GetError());
            return false;   //return now, nothing else should be called
        }
    }
    
#ifdef USE_SDL_MIXER
    if(!mInitialized)
    {
        if(Mix_OpenAudio(mRate, AUDIO_S16SYS, mStereo?2:1, 4096) < 0)  //Open Audio (Stereo?2:1 is conditional for number of channels)
        {
            ReportError(ZERR_MIX_INIT,SDL_GetError());
            status = false; //continue setup without sound
        }
    }
#endif //USE_SDL_MIXER

    //set flags and bpp//
    if(mFullscreen)
        flags |= SDL_FULLSCREEN;

    if(mBPP != -1 && mBPP != 8 && mBPP != 15 && mBPP != 16 && mBPP != 24 && mBPP !=32)
    {
        ReportError(ZERR_VIDMODE,FormatStr("%d is invalid BPP, must be 8,15,16,24 or 32, trying best BPP.",mBPP));
        mBPP = -1;
    }
    else
    {
        if(mBPP == -1)
            mBPP = SDL_GetVideoInfo()->vfmt->BitsPerPixel;

        bpp = SDL_VideoModeOK(mWidth, mHeight, mBPP, flags);
        if(!bpp)
        {
            ReportError(ZERR_VIDMODE,FormatStr("%dx%d not supported in any depth.",mWidth,mHeight));
            return false;   //return now
        }
        else if(bpp != mBPP)
        {
            ReportError(ZERR_VIDMODE,FormatStr("%dx%d not supported in %dBPP, trying %dBPP.",mWidth,mHeight,mBPP,bpp));
            mBPP = bpp;
        }
    }

    switch (mBPP)
    {
        case 8:
            rgb_size[0] = 3;
            rgb_size[1] = 3;
            rgb_size[2] = 2;
            break;
        case 15:
        case 16:
            rgb_size[0] = 5;
            rgb_size[1] = 5;
            rgb_size[2] = 5;
            break;
        default:
            rgb_size[0] = 8;
            rgb_size[1] = 8;
            rgb_size[2] = 8;
            break;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rgb_size[0]);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, rgb_size[1]);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rgb_size[2]);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, mBPP==32 ? 24 : mBPP);   //use 24 if BPP is 32
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);

    flags |= SDL_OPENGL;

    if(!mInitialized)    //only set these settings the first time
    {
        //Default window manager settings//
        SDL_EnableKeyRepeat(30,30);
        if(!icon.length())
            SDL_WM_SetCaption(title.c_str(),NULL);
        else
        {
            SDL_WM_SetCaption(title.c_str(),title.c_str());
            iconImg = LoadImage(icon);
            SDL_WM_SetIcon(iconImg,NULL);
            FreeImage(iconImg);
        }
    }

    //create SDL screen and update settings based on returned screen//
    mScreen = SDL_SetVideoMode(mWidth, mHeight, mBPP, flags);

    if(!mScreen)
    {
        ReportError(ZERR_VIDMODE,FormatStr("Unknown Error. %dx%d %dBPP (%s)",mWidth, mHeight, mBPP, SDL_GetError()));

#ifdef USE_SDL_MIXER
        Mix_CloseAudio();
#endif
        SDL_Quit();

        return false;   //bail if display fails
    }
    
    mWidth = mScreen->w;
    mHeight = mScreen->h;
    mBPP = mScreen->format->BitsPerPixel;

    SetGL2D();

    mKeyIsPressed = SDL_GetKeyState(NULL);

#ifdef USE_SDL_TTF
    if(!mInitialized)
    {
        if(TTF_Init() < 0)
        {
            ReportError(ZERR_TTF_INIT,TTF_GetError());
            status = false; //possible to go on without SDL_TTF
        }
    }
#endif  //USE_SDL_TTF

    if(!mInitialized)
        mLastTime = mPausedTime = SDL_GetTicks();
    mActive = true;
    mInitialized = true;    //if it makes it to the end it has been initialized

    return status;  //return true (false will be returned if TTF or Mixer fail)
}

void ZEngine::CloseDisplay()
{
    if(mInitialized)
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

        if(mErrlog != stderr && mErrlog != stdin)
            fclose(mErrlog);

        mInitialized = false;
    }
}

void ZEngine::ToggleFullscreen()
{
    char *title,*icon;
#ifdef linux    //SDL_WM_TF only works on Linux
    SDL_WM_ToggleFullscreen(mScreen);
#else
    SetupDisplay(mWidth,mHeight,mBPP,!mFullscreen);
    SDL_WM_GetCaption(&title,&icon);
    if(icon)
        CreateDisplay(title,icon);
    else
        CreateDisplay(title);
#endif
    SetReloadNeed(true);
}

bool ZEngine::Initialized()
{
    return mInitialized;
}

SDL_Surface *ZEngine::Display()
{
    return mScreen;
}

void ZEngine::Update()
{
    SDL_GL_SwapBuffers();

    mSecPerFrame = (GetTime()-mLastTime)/1000.0;
    mLastTime = GetTime();

    if(mDesiredFramerate)
    {
        if(mLastTime < mNextUpdate)
            SDL_Delay(mNextUpdate-mLastTime);
        mNextUpdate = GetTime()+(1000/mDesiredFramerate);
    }
}

void ZEngine::Clear(float red, float green, float blue, float alpha)
{
    glClearColor(red,green,blue,alpha);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void ZEngine::SetGL2D()
{
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    /* This allows alpha blending of 2D textures with the scene*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, mWidth, mHeight);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0.0, (GLdouble)mWidth, (GLdouble)mHeight, 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void ZEngine::Delay(Uint32 milliseconds)
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

double ZEngine::GetFramerate()
{
    return 1/mSecPerFrame;
}

void ZEngine::SetDesiredFramerate(Uint8 rate)
{
    mDesiredFramerate = rate;
}

Uint8 ZEngine::GetDesiredFramerate()
{
    return mDesiredFramerate;
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

void ZEngine::SetReloadNeed(bool state)
{
    mNeedReload = state;
}

bool ZEngine::ImagesNeedReload()
{
    return mNeedReload;
}

void ZEngine::SetKeyRepeatRate(int rate)
{
    SDL_EnableKeyRepeat(rate,rate);
}

bool ZEngine::KeyIsPressed(SDLKey key)
{
    return mKeyIsPressed[key] == 1;
}

bool ZEngine::KeyPress(SDLKey key)
{
    bool temp = mKeyPress[key];
    mKeyPress[key] = false;
    return temp;
}

void ZEngine::HideCursor()
{
    SDL_ShowCursor(SDL_DISABLE);
}

void ZEngine::ShowCursor()
{
    SDL_ShowCursor(SDL_ENABLE);
}

int ZEngine::MouseX()
{
    return mMouseX;
}

int ZEngine::MouseY()
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
                        if(mFullscreen)
                            mNeedReload = true;
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
            case SDL_KEYDOWN:
                mKeyPress[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                mKeyPress[event.key.keysym.sym] = false;
                break;
            case SDL_QUIT:
                mQuit = true;
                break;
            default:
                break;
        }
    }

    mKeyIsPressed = SDL_GetKeyState(NULL);        //recommended but not needed (says Sam)

    //Alt-X or Alt-F4
    if((mKeyIsPressed[SDLK_x] || mKeyIsPressed[SDLK_F4]) && 
        (mKeyIsPressed[SDLK_LALT] || mKeyIsPressed[SDLK_RALT]))
        mQuit = true;

    mMouseB = SDL_GetMouseState(&mMouseX,&mMouseY);
}

void ZEngine::SetEventFilter(SDL_EventFilter filter)
{
    SDL_SetEventFilter(filter);
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

void ZEngine::SetErrorLog(bool logAll, string logFile)
{
    mLogAllErrors = logAll;
    if(logFile.length())
    {
        if(logFile == "stderr")
            mErrlog = stderr;
        else if(logFile == "stdout")
            mErrlog = stdout;
        else
            mErrlog = fopen(logFile.c_str(),"w");
    }
}

void ZEngine::ReportError(ZErrorCode code, string desc, string file, unsigned int line)
{
    mCurError.Create(code,desc,file,line);

    if(mLogAllErrors)
    {
        LogError(mCurError);
        fflush(mErrlog);
    }
    else
        mErrorQueue.push(mCurError);
}

ZErrorCode ZEngine::GetLastError()
{
    ZErrorCode code = mCurError.Code();
    mCurError.Create(ZERR_NONE);
    return code;
}

void ZEngine::WriteLog(string str)
{
    fprintf(mErrlog,str.c_str());
}

void ZEngine::LogError(ZError error)
{
    fprintf(mErrlog,error.LogString().c_str());
}

void ZEngine::FlushErrors()
{
    mCurError.Create(ZERR_NONE);
    while(!mErrorQueue.empty())
    {
        LogError(mErrorQueue.front());
        mErrorQueue.pop();
    }
}

SDL_Surface* ZEngine::LoadImage(string filename)
{
    SDL_Surface *image;
//using physfs//
#ifdef USE_PHYSFS
    SDL_RWops *rw;
    rw = PHYSFSRWOPS_openRead(filename.c_str());
    if(!rw)
    {
        ReportError(ZERR_LOAD_IMAGE,FormatStr("%s [PhysFS RWops failed: %s]",filename.c_str(),SDL_GetError()));
        return NULL;
    }
#ifdef USE_SDL_IMAGE
    image = IMG_Load_RW(rw,0);
#else
    image = SDL_LoadBMP_RW(rw,0);
#endif    //USE_SDL_IMAGE
    SDL_FreeRW(rw);
//end using physfs//

//Just SDL//
#else
#ifdef USE_SDL_IMAGE
    image = IMG_Load(filename.c_str());
#else
    image = SDL_LoadBMP(filename.c_str());
#endif    //USE_SDL_IMAGE
#endif    //USE_PHYSFS

    if(!image)
    {
        ReportError(ZERR_LOAD_IMAGE,filename);
        return NULL;
    }
    else
        return image;
}

#ifdef USE_SDL_MIXER

Mix_Chunk* ZEngine::LoadSound(string filename)
{
    Mix_Chunk *sound;

#ifdef USE_PHYSFS
    SDL_RWops *rw;
    rw = PHYSFSRWOPS_openRead(filename.c_str());
    sound = Mix_LoadWAV_RW(rw,0);
    SDL_FreeRW(rw);
#else
    sound = Mix_LoadWAV(filename.c_str());
#endif //USE_PHYSFS

    if(!sound)
    {
        ReportError(ZERR_LOAD_SOUND,filename);
        return NULL;
    }
    else
        return sound;
}

Mix_Music* ZEngine::LoadMusic(string filename)
{
    Mix_Music *music;

//Currently SDL_Mixer doesn't support Music from a RW
//#ifdef USE_PHYSFS
//    SDL_RWops *rw;
//    rw = PHYSFSRWOPS_openRead(filename.c_str());
//    mus.music = Mix_LoadMUS_RW(filename.c_str(),0);
//    SDL_FreeRW(rw);
//#else
    music = Mix_LoadMUS(filename.c_str());
//#endif //USE_PHYSFS
    
    if(!music)
    {
        ReportError(ZERR_LOAD_MUSIC,filename);
        return NULL;
    }
    else
        return music;
}

#endif

#ifdef USE_SDL_TTF

TTF_Font* ZEngine::LoadFont(string filename, int size)
{
    TTF_Font *font;

//Currently SDL_ttf doesn't support Fonts from a RW
//#ifdef USE_PHYSFS
//    SDL_RWops *rw;
//    rw = PHYSFSRWOPS_openRead(filename.c_str());
//    fnt.font = TTF_OpenFontRW(rw,0);
//    SDL_FreeRW(rw);
//#else
    font = TTF_OpenFont(filename.c_str(),size);
//#endif //USE_PHYSFS

    if(!font)
    {
        ReportError(ZERR_LOAD_FONT,filename);
        return NULL;
    }
    else
        return font;
}


#endif 

int ZEngine::Width()
{
    return mWidth;
}

int ZEngine::Height()
{
    return mHeight;
}

int ZEngine::BPP()
{
    return mBPP;
}

bool ZEngine::IsFullscreen()
{
    return mFullscreen;
}

}
