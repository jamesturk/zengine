/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZEngine.h"
#include "ZE_ZRect.h"

namespace ZE
{

VersionInfo ZEngine::Version(0,8,5);
ZEngine *ZEngine::sInstance=NULL;

ZEngine::ZEngine() :
    mScreen(NULL), mFullscreen(true), mInitialized(false),
    mPaused(false), mUnpauseOnActive(false),
    mNextUpdate(0), mLastPause(0), mPausedTime(0), mLastTime(0),
    mSecPerFrame(0.0),
    mNeedReload(false), mActive(false), mQuit(false), mKeyIsPressed(NULL),
    mMouseX(0), mMouseY(0), mMouseB(0),
    mEventFilter(NULL),
    mLogStyle(ZLOG_NONE), mMinSeverity(ZERR_NOTE), mErrlog(NULL)
#if SND_BACKEND == ZE_MIXER
    ,mMixerFrequency(0),mMixerFormat(0),mMixerChannels(0),mMixerChunksize(0)
#endif
{
    for(int k = 0; k < SDLK_LAST; ++k)
        mKeyPress[k] = false;
    atexit(ZEngine::ReleaseInstance);
}

TiXmlElement* ZEngine::FindElement(std::string type, std::string id)
{
    TiXmlElement *elem=NULL;

    if(rZRF.RootElement())
    {
        elem = rZRF.RootElement()->FirstChildElement();

        //while element exists
        while(elem)
        {
            if(strcmpi(elem->Value(),type.c_str()) == 0 && strcmpi(elem->Attribute("id"),id.c_str()) == 0)
                break;  //found our guy
            else
                elem = elem->NextSiblingElement();
        }

        if(!elem)
            ReportError(ZERR_WARNING,"No '%s' resource found with id '%s'",type.c_str(),id.c_str());
    }
    else
    {
        ReportError(ZERR_WARNING,"No root element in ZRF file.");
    }

    return elem;
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
        if(sInstance->mErrlog && sInstance->mLogStyle == ZLOG_HTML)
        {
            fprintf(sInstance->mErrlog,"</body>\n</html>");
            fclose(sInstance->mErrlog);
        }

        sInstance->CloseDisplay();
        delete sInstance;
    }
    sInstance = NULL;
}

void ZEngine::InitErrorLog(ZErrorLogStyle logStyle, std::string logFile, ZErrorSeverity minSeverity)
{
    mMinSeverity = minSeverity;
    mLogStyle = logStyle;

    if(logStyle != ZLOG_NONE && logFile.length())
    {
        //stderr & stdout directed to their appropriate streams
        if(logFile == "stderr")
            mErrlog = stderr;
        else if(logFile == "stdout")
            mErrlog = stdout;
        else
            mErrlog = std::fopen(logFile.c_str(),"w");

        if(logStyle == ZLOG_HTML)
        {
            fprintf(mErrlog,
                "<html><head><title>ZEngine Error Log</title>\n<style type=\"text/css\">\n<!--\n"
                "p { margin: 0 }\n"
                ".note { font-style:italic color:gray }\n"
                ".verbose { font-style:italic; background:yellow; font-size:small }\n"
                ".depr { font-weight:bold; background:blue; color:white }\n"
                ".warning { font-weight:bold; background:yellow }\n"
                ".error { font-weight:bold; background:orange }\n"
                ".critical { font-weight:bold; background:red; color:white }\n"
                "-->\n</style>\n</head>\n<body>\n");
            fflush(mErrlog);
        }
    }
}

#if SND_BACKEND == ZE_MIXER
void ZEngine::InitAudio(int frequency, bool stereo, Uint16 format,  int chunksize)
{
    mMixerFrequency = frequency;
    mMixerChannels = stereo ? 2 : 1;
    mMixerFormat = format;
    mMixerChunksize = chunksize;
}
#elif SND_BACKEND == ZE_AUDIERE
bool ZEngine::InitAudio()
{
    mAudiereDevice = audiere::OpenDevice();
    if(!mAudiereDevice)
    {
        ReportError(ZERR_CRITICAL,"Failed to initialize sound, AudiereDevice creation failed.");
    }
    return (mAudiereDevice != NULL);
}
#endif //SND_BACKEND

bool ZEngine::CreateDisplay(int width, int height, int bpp, bool fullscreen, std::string title, std::string icon)
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

#if SND_BACKEND == ZE_MIXER
    if(mMixerFrequency && mMixerFormat && mMixerChannels && mMixerChunksize)
        sdlFlags |= SDL_INIT_AUDIO;
#endif

    if(!mInitialized)
    {
        if(SDL_Init(sdlFlags) < 0)
        {
            ReportError(ZERR_CRITICAL,"Error initializing SDL: %s",SDL_GetError());
            return false;   //return now, nothing else should be called
        }
    }

#if SND_BACKEND == ZE_MIXER
    if(!mInitialized && mMixerFrequency && mMixerFormat && mMixerChannels && mMixerChunksize)
    {
        if(Mix_OpenAudio(mMixerFrequency,mMixerFormat,mMixerChannels,mMixerChunksize) < 0)
        {
            ReportError(ZERR_ERROR,"Error initializing SDL_mixer: %s",SDL_GetError());
            status = false;
        }
    }
#endif //USE_SDL_MIXER

    //set vidFlags and bpp//
    if(mFullscreen)
        vidFlags |= SDL_FULLSCREEN;

    if(bpp != -1 && bpp != 8 && bpp != 15 && bpp != 16 && bpp != 24 && bpp !=32)
    {
        ReportError(ZERR_WARNING,"Error creating display: %d is invalid BPP, must be 8,15,16,24 or 32, trying best BPP.",bpp);
        bpp = -1;
    }
    else    //this decides correcr BPP
    {
        if(bpp == -1)
            bpp = SDL_GetVideoInfo()->vfmt->BitsPerPixel;  //try desktop resolution

        okBPP = SDL_VideoModeOK(width, height, bpp, vidFlags);
        if(!okBPP)
        {
            ReportError(ZERR_ERROR,"Error creating display: %dx%d not supported in any depth.",width,height);
            return false;   //return now
        }
        else if(okBPP != bpp)
        {
            ReportError(ZERR_WARNING,"Error creating display: %dx%d not supported in %dBPP, trying %dBPP.",width,height,bpp,okBPP);
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
        ReportError(ZERR_CRITICAL,"Error creating display: Unknown Error. %dx%d %dBPP (%s)", width, height, bpp, SDL_GetError());

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
            ReportError(ZERR_ERROR,"Error initializing SDL_ttf: %s",TTF_GetError());
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
    CreateDisplay(mScreen->w,mScreen->h,mScreen->format->BitsPerPixel,!mFullscreen);    //replacement for WM_TF on Windows
#endif
    SetReloadNeed(true);    //images need to be reloaded on fullscreen swap
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
}

#if (GFX_BACKEND == ZE_OGL)

void ZEngine::ClearDisplay(Uint8 red, Uint8 green, Uint8 blue)
{
    glClearColor(red/255.0f,green/255.0f,blue/255.0f,1.0f);
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

bool ZEngine::TimerIsPaused()
{
    return mPaused;
}

double ZEngine::GetFrameSpeed()
{
    return mSecPerFrame;
}

double ZEngine::GetFramerate()
{
    return mSecPerFrame ? 1/mSecPerFrame : 0;   //avoid /0
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

bool ZEngine::MouseInRect(const SDL_Rect &rect)
{
    //useful function, needed so much it made it into ZEngine
    return (mMouseX >= rect.x && mMouseX <= rect.x+rect.w && 
        mMouseY >= rect.y && mMouseY <= rect.y+rect.h);
}

bool ZEngine::MouseInRect(const ZRect &rect)
{
    return rect.Contains(static_cast<float>(mMouseX),static_cast<float>(mMouseY));
}

void ZEngine::CheckEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        //only process event if filter doesn't exist or if filter returns a nonzero value
        //the SDL spec says that filters return 0 when they wish to remove an item from the event queue
        if(!mEventFilter || mEventFilter(&event))
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

void ZEngine::ReportError(ZErrorSeverity severity, std::string desc, ...)
{
    static std::string prefix[] = { 
        "VERBOSE: ",
        "DEPRECIATED: ",
        "WARNING: ",
        "ERROR: ",
        "CRITICAL: "
        " ",
    };

    static std::string style[] = { 
        "verbose",
        "depr",
        "warning",
        "error",
        "critical",
        "note"
    };

    if(mLogStyle != ZLOG_NONE)
    {
        char buf[1024];
        std::va_list args;

        va_start(args,desc);
        std::vsprintf(buf,desc.c_str(),args);
        va_end(args);

        if(mLogStyle == ZLOG_TEXT)
        {
            fprintf(mErrlog,"%s%s\n",prefix[static_cast<int>(severity)].c_str(),buf);
        }
        else if(mLogStyle == ZLOG_HTML)
        {
            fprintf(mErrlog,"<p class=\"%s\">%s%s</p>\n",style[static_cast<int>(severity)].c_str(),prefix[static_cast<int>(severity)].c_str(),buf);
        }

        std::fflush(mErrlog);
    }
}

void ZEngine::WriteLog(std::string str, ...)
{
    std::va_list args;
    char buf[1024];

    va_start(args,str);
    std::vsprintf(buf,str.c_str(),args);
    va_end(args);

    ReportError(ZERR_NOTE, buf);
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

void ZEngine::SetResourceFile(std::string filename)
{
    rZRF.LoadFile(filename);
    if(rZRF.Error())
        ReportError(ZERR_ERROR,"Error loading resource file %s.",filename.c_str());
}

std::string ZEngine::GetStringResource(std::string type, std::string id, std::string element)
{
    TiXmlElement *elem = FindElement(type,id);
    if(elem)
        return elem->Attribute(element.c_str());
    else
    {
        ReportError(ZERR_WARNING,"GetStringResource(%s,%s,%s) failed.",type.c_str(),id.c_str(),element.c_str());
        return "";  //empty string
    }
}

int ZEngine::GetIntResource(std::string type, std::string id, std::string element)
{
    TiXmlElement *elem = FindElement(type,id);
    int ret=0;

    if(!elem || (elem->QueryIntAttribute(element.c_str(),&ret) != TIXML_SUCCESS))
    {
        if(!elem)
            ReportError(ZERR_WARNING,"GetIntResource(%s,%s,%s) failed, no tags of that type.",type.c_str(),id.c_str(),element.c_str());
        else if(elem->QueryIntAttribute(element.c_str(),&ret) == TIXML_NO_ATTRIBUTE)
            ReportError(ZERR_WARNING,"GetIntResource(%s,%s,%s) failed, no tag with that ID.",type.c_str(),id.c_str(),element.c_str());
        else if(elem->QueryIntAttribute(element.c_str(),&ret) == TIXML_WRONG_TYPE)
            ReportError(ZERR_WARNING,"GetIntResource(%s,%s,%s) failed, not an integer.",type.c_str(),id.c_str(),element.c_str());
    }
    return ret;
}

double ZEngine::GetDoubleResource(std::string type, std::string id, std::string element)
{
    TiXmlElement *elem = FindElement(type,id);
    double ret=0;

    if(!elem || (elem->QueryDoubleAttribute(element.c_str(),&ret) != TIXML_SUCCESS))
    {
        if(!elem)
            ReportError(ZERR_WARNING,"GetDoubleResource(%s,%s,%s) failed, no tags of that type.",type.c_str(),id.c_str(),element.c_str());
        else if(elem->QueryDoubleAttribute(element.c_str(),&ret) == TIXML_NO_ATTRIBUTE)
            ReportError(ZERR_WARNING,"GetDoubleResource(%s,%s,%s) failed, no tag with that ID.",type.c_str(),id.c_str(),element.c_str());
        else if(elem->QueryDoubleAttribute(element.c_str(),&ret) == TIXML_WRONG_TYPE)
            ReportError(ZERR_WARNING,"GetDoubleResource(%s,%s,%s) failed, not a double.",type.c_str(),id.c_str(),element.c_str());
    }
    return ret;
}

#if SND_BACKEND == ZE_AUDIERE
audiere::AudioDevicePtr ZEngine::GetSoundDevice()
{
    return mAudiereDevice;
}
#endif

SDL_Surface *ZEngine::GetDisplayPointer()
{
    return mScreen;
}

bool ZEngine::DisplayCreated()
{
    return mInitialized;
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

bool ZEngine::IsFullscreen()
{
    return mFullscreen;
}

}
