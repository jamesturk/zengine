/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZEngine.cpp
    \brief Central source file for ZEngine.

    Actual implementation of ZEngine singleton class, the core of ZEngine.
    <br>$Id: ZE_ZEngine.cpp,v 1.65 2003/11/24 02:21:20 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZEngine.h"
#include "ZE_ZRect.h"

namespace ZE
{

VersionInfo ZEngine::Version(0,8,5);
ZEngine *ZEngine::sInstance=NULL;

ZEngine::ZEngine() :
    mScreen(NULL), mFullscreen(true), mInitialized(false),
    mPaused(false), mUnpauseOnActive(false),
    mDesiredFramerate(0), mNextUpdate(0), mLastPause(0), mPausedTime(0), mLastTime(0),
    mSecPerFrame(0.0),
    mNeedReload(false), mActive(false), mQuit(false), mKeyIsPressed(NULL),
    mMouseX(0), mMouseY(0), mMouseB(0),
    mErrlog(stderr), mEventFilter(NULL)
{
    for(int k = 0; k < SDLK_LAST; ++k)
        mKeyPress[k] = false;
    
    //create error strings
    mErrorDesc[ZERR_NONE] = "No Error. [%s]";
    mErrorDesc[ZERR_SDL_INTERNAL] = "SDL Error. [%s]";
    mErrorDesc[ZERR_SDL_INIT] = "Error Initializing SDL: %s";
    mErrorDesc[ZERR_MIX_INIT] = "Error Initializing SDL_mixer: %s";
    mErrorDesc[ZERR_TTF_INIT] = "Error Initializing SDL_ttf: %s";
    mErrorDesc[ZERR_VIDMODE] = "Error Creating Display: %s";
    mErrorDesc[ZERR_LOAD_IMAGE] = "Failed to load Image: %s";
    mErrorDesc[ZERR_LOAD_SOUND] = "Failed to load Sound: %s"; 
    mErrorDesc[ZERR_LOAD_MUSIC] = "Failed to load Music: %s";
    mErrorDesc[ZERR_LOAD_FONT] = "Failed to load Font: %s";
    mErrorDesc[ZERR_NOIMAGE] = "Called ZImage::%s with no Image loaded.";
    mErrorDesc[ZERR_NOSOUND] = "Called ZSound::%s with no Sound loaded.";
    mErrorDesc[ZERR_NOMUSIC] = "Called ZMusic::%s with no Music loaded.";
    mErrorDesc[ZERR_NOFONT] = "Called ZFont::%s with no Font loaded.";
}

ZEngine* ZEngine::GetInstance()
{
    if(!sInstance)  //first time through, gets new instance, each time after returns same one
        sInstance = new ZEngine;

    return sInstance;
}

void ZEngine::ReleaseInstance()
{
    if(sInstance)
    {
        sInstance->CloseDisplay();  
        delete sInstance;
    }
    sInstance = NULL;
}

bool ZEngine::CreateDisplay(int width, int height, int bpp, bool fullscreen, std::string title, 
            int soundRate, bool stereo, std::string icon)
{
    Uint32 sdlFlags=SDL_INIT_VIDEO|SDL_INIT_TIMER;
    Uint32 vidFlags=0;
    SDL_Surface *iconImg;
    bool status=true;   //status of setup, only true if everything went flawlessly
    int okBPP;  //used to find working BPP
#if (GFX_BACKEND == ZE_OGL)
    int rgb_size[3];
#endif

    mFullscreen = fullscreen;

    if(!mInitialized)
    {
        //audio only initialized if soundRate != 0
        if(soundRate)
            sdlFlags |= SDL_INIT_AUDIO;
        if(SDL_Init(sdlFlags) < 0) 
        {
            ReportError(ZERR_SDL_INIT,SDL_GetError());
            return false;   //return now, nothing else should be called
        }
    }
    
#ifdef USE_SDL_MIXER
    if(!mInitialized)
    {
        if(Mix_OpenAudio(soundRate, AUDIO_S16SYS, stereo?2:1, 4096) < 0)  //Open Audio (Stereo?2:1 is conditional for number of channels)
        {
            ReportError(ZERR_MIX_INIT,SDL_GetError());
            status = false;
        }
    }
#endif //USE_SDL_MIXER

    //set vidFlags and bpp//
    if(mFullscreen)
        vidFlags |= SDL_FULLSCREEN;

    if(bpp != -1 && bpp != 8 && bpp != 15 && bpp != 16 && bpp != 24 && bpp !=32)
    {
        ReportError(ZERR_VIDMODE,"%d is invalid BPP, must be 8,15,16,24 or 32, trying best BPP.",bpp);
        bpp = -1;
    }
    else    //this decides correcr BPP
    {
        if(bpp == -1)
            bpp = SDL_GetVideoInfo()->vfmt->BitsPerPixel;  //try desktop resolution

        okBPP = SDL_VideoModeOK(width, height, bpp, vidFlags);
        if(!okBPP)
        {
            ReportError(ZERR_VIDMODE,"%dx%d not supported in any depth.",width,height);
            return false;   //return now
        }
        else if(okBPP != bpp)
        {
            ReportError(ZERR_VIDMODE,"%dx%d not supported in %dBPP, trying %dBPP.",width,height,bpp,okBPP);
            bpp = okBPP;
        }
    }

#if (GFX_BACKEND == ZE_OGL)
    //buffer sizes
    switch(bpp)
    {
        case 8:
            rgb_size[0] = rgb_size[1] = 3;
            rgb_size[2] = 2;
            break;
        case 15:
        case 16:
            rgb_size[0] = rgb_size[1] = rgb_size[2] = 5;
            break;
        default:
            rgb_size[0] = rgb_size[1] = rgb_size[2] = 8;
            break;
    }

    //key GL attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rgb_size[0]);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, rgb_size[1]);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rgb_size[2]);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bpp==32 ? 24 : bpp);   //use 24 if BPP is 32
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);

    vidFlags |= SDL_OPENGL;
#elif (GFX_BACKEND == ZE_SDL)
    vidFlags |= SDL_DOUBLEBUF;
#endif //GFX_BACKEND

    //Window manager settings
    if(!mInitialized)    //only set these settings the first time
    {
        SDL_WM_SetCaption(title.c_str(),title.c_str());
        if(icon.length())
        {
#ifdef USE_SDL_IMAGE
            iconImg = IMG_Load(icon.c_str());
#else
            iconImg = SDL_LoadBMP(icon.c_str());
#endif
            SDL_WM_SetIcon(iconImg,NULL);
            FreeImage(iconImg);
        }
    }

    //create SDL screen and update settings based on returned screen//
    mScreen = SDL_SetVideoMode(width, height, bpp, vidFlags);

    if(!mScreen)
    {
        ReportError(ZERR_VIDMODE,"Unknown Error. %dx%d %dBPP (%s)", width, height, bpp, SDL_GetError());

#ifdef USE_SDL_MIXER
        Mix_CloseAudio();
#endif
        SDL_Quit();

        return false;   //bail if display fails
    }

#if (GFX_BACKEND == ZE_OGL)
    SetGL2D();
#endif 

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
        mPausedTime = SDL_GetTicks();
    mActive = true;
    mInitialized = true;    //if it makes it to the end it has been initialized

    return status;  //return true (false will be returned if TTF or Mixer or Net fail)
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

        SDL_Quit();

        if(mErrlog && mErrlog != stderr && mErrlog != stdin)
            fclose(mErrlog);

        mInitialized = false;
    }
}

void ZEngine::ToggleFullscreen()
{
#ifdef linux    //SDL_WM_TF only works on Linux
    SDL_WM_ToggleFullScreen(mScreen);
#else
    CreateDisplay(mScreen->w,mScreen->h,mScreen->format->BitsPerPixel,!mFullscreen,""); //title, soundRate, stereo, and icon not used
#endif
    SetReloadNeed(true);    //images need to be reloaded on fullscreen swap
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
#if (GFX_BACKEND == ZE_OGL)
    SDL_GL_SwapBuffers();
#elif (GFX_BACKEND == ZE_SDL)
    SDL_Flip(mScreen);
#endif

    //keeps track of spf//
    mSecPerFrame = (GetTime()-mLastTime)/1000.0;
    mLastTime = GetTime();  

    //framerate limiting//
    if(mDesiredFramerate)   
    {
        if(mLastTime < mNextUpdate)
            SDL_Delay(mNextUpdate-mLastTime);
        mNextUpdate = GetTime()+(1000/mDesiredFramerate);
    }
}

#if (GFX_BACKEND == ZE_OGL)

void ZEngine::Clear(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    GLclampf r = red/255.0f, g = green/255.0f, b = blue/255.0f, a = alpha/255.0f;
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}

void ZEngine::SetGL2D()
{
    //disable unused features for 2D//
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    // This allows alpha blending of 2D textures with the scene //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //setup viewport & ortho mode to emulate standard 2D API conventions
    glViewport(0, 0, mScreen->w, mScreen->h);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0.0, (GLdouble)mScreen->w, (GLdouble)mScreen->h, 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

#elif (GFX_BACKEND == ZE_SDL)

void ZEngine::Clear(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    SDL_FillRect(mScreen,NULL,SDL_MapRGBA(mScreen->format,red,green,blue,alpha));
}

#endif //GFX_BACKEND

void ZEngine::Delay(Uint32 milliseconds)
{
    SDL_Delay(milliseconds);
}

Uint32 ZEngine::GetTime()
{
    if(mPaused) //when paused time hasn't been added to mPausedTime yet
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
        //mPaused time accumulates total time engine has been paused
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
    return mSecPerFrame ? 1/mSecPerFrame : 0;   //avoid /0
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
    mKeyPress[key] = false; //checking removes the press, this is used to detect single presses
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

bool ZEngine::MButtonPressed()
{
    return (mMouseB & SDL_BUTTON_MMASK) > 0;
}

bool ZEngine::MouseInRect(SDL_Rect *rect)
{
    //useful function, needed so much it made it into ZEngine
    return (mMouseX >= rect->x && mMouseX <= rect->x+rect->w && 
        mMouseY >= rect->y && mMouseY <= rect->y+rect->h);
}

bool ZEngine::MouseInRect(ZRect rect)
{
    return rect.Contains(static_cast<float>(mMouseX),static_cast<float>(mMouseY));
}

void ZEngine::CheckEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(!mEventFilter || mEventFilter(&event))    //if the filter returns 0 it is removing the event, it will not be processed
        {
            switch(event.type)  //only certain events are handled, mEventFilter can handle user requests
            {
                //these events try and catch all video changes, for potential surface loss
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
                    //SDL_KEYDOWN/UP messages manipulate the mKeyPress array, used for single presses
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
    }

    mKeyIsPressed = SDL_GetKeyState(NULL);        //recommended but not needed (says Sam on the list)

    //Alt-X or Alt-F4
    if((mKeyIsPressed[SDLK_x] || mKeyIsPressed[SDLK_F4]) && 
        (mKeyIsPressed[SDLK_LALT] || mKeyIsPressed[SDLK_RALT]))
        mQuit = true;

    mMouseB = SDL_GetMouseState(&mMouseX,&mMouseY);
}

void ZEngine::SetEventFilter(SDL_EventFilter filter)
{
    mEventFilter = filter;
}

void ZEngine::SetErrorLog(std::string logFile)
{
    if(logFile.length())
    {
        //stderr & stdout directed to their appropriate streams
        if(logFile == "stderr")
            mErrlog = stderr;
        else if(logFile == "stdout")
            mErrlog = stdout;
        else
            mErrlog = std::fopen(logFile.c_str(),"w");
    }
}

void ZEngine::DisableErrorLog()
{
    mErrlog = NULL;
}

void ZEngine::ReportError(ZErrorCode type, std::string desc, ...)
{
    char buf[512];
    va_list args;
    std::string msg;

    va_start(args,desc);
    vsprintf(buf,desc.c_str(),args);
    va_end(args);

    msg = desc.length() ? FormatStr(mErrorDesc[type],buf) : mErrorDesc[type];

    if(mErrlog)
    {
        std::fprintf(mErrlog,msg.c_str());
        std::fflush(mErrlog);
    }
}

void ZEngine::SeedRandGen(unsigned long seed)
{
    mRandGen.Seed(seed);
}

unsigned int ZEngine::Rand(unsigned int max)
{
    return mRandGen.Rand(max);
}

unsigned long ZEngine::Rand(unsigned long max)
{
    return mRandGen.Rand(max);
}

int ZEngine::Rand(int min, int max)
{
    return mRandGen.Rand(min,max);
}

long ZEngine::Rand(long min, long max)
{
    return mRandGen.Rand(min,max);
}

float ZEngine::Rand(float min, float max)
{
    return mRandGen.Rand(min,max);
}

double ZEngine::Rand(double min, double max)
{
    return mRandGen.Rand(min,max);
}

double ZEngine::RandDouble()
{
    return mRandGen.RandDouble();
}

int ZEngine::DisplayWidth()
{
    return mScreen->w;
}

int ZEngine::DisplayHeight()
{
    return mScreen->h;
}

int ZEngine::DisplayDepth()
{
    return mScreen->format->BitsPerPixel;
}

#ifdef DEPRECIATED

int ZEngine::Width()
{
    return mScreen->w;
}

int ZEngine::Height()
{
    return mScreen->h;
}

int ZEngine::BPP()
{
    return mScreen->format->BitsPerPixel;
}

#endif //DEPRECIATED

bool ZEngine::IsFullscreen()
{
    return mFullscreen;
}

}
