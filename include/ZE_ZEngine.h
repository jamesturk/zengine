/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZEngine.h
    \brief Definition file for core ZEngine class.

    ZEngine Game Engine core Engine definition.
    <br>$Id: ZE_ZEngine.h,v 1.55 2003/11/23 19:30:26 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zengine_h__
#define __ze_zengine_h__

#include "ZE_Defines.h"
#include "ZE_Utility.h"
#include "ZE_Includes.h"
#include "ZE_ZRandGen.h"
#include "VersionInfo.h"

/*!
    \brief ZEngine Namespace.
    
    Namespace for ZEngine classes and utility functions.
**/
namespace ZE
{

class ZRect;

/*!
    \brief Enumeration of ZEngine error codes.

    All the error codes currently possibly by ZEngine, note that ZERR_LAST is not used as an error code, but instead
    as a range check on the others.
**/
enum ZErrorCode 
{
    ZERR_NONE,          /*!< No error has occured.  */
    ZERR_SDL_INTERNAL,  /*!< Error internal to SDL has occured, usually more detail is given by SDL. */
    ZERR_SDL_INIT,      /*!< Error Initializing SDL. */
    ZERR_MIX_INIT,      /*!< Error Initializing SDL_mixer. */
    ZERR_TTF_INIT,      /*!< Error Initializing SDL_ttf. */
    ZERR_VIDMODE,       /*!< Error setting up the display. */
    ZERR_LOAD_IMAGE,    /*!< Error loading an image. */
    ZERR_LOAD_SOUND,    /*!< Error loading a sound sample. */
    ZERR_LOAD_MUSIC,    /*!< Error loading music. */
    ZERR_LOAD_FONT,     /*!< Error loading a font. */
    ZERR_NOIMAGE,       /*!< Error trying to use a ZImage without properly loading an image. */
    ZERR_NOSOUND,       /*!< Error trying to use a ZSound without properly loading a sound. */
    ZERR_NOMUSIC,       /*!< Error trying to use a ZMusic without properly loading music. */
    ZERR_NOFONT,        /*!< Error trying to use a ZFont without properly loading a font. */
    ZERR_LAST           /*!< Value used as range index, not a valid error code. */
};

/*!
    \brief Main ZEngine Singleton Class

    ZEngine Singleton Class, accessible from anywhere in a ZEngine-based program by nature.  Controls core elements of program and does 
    majority of SDL and OpenGL wrapping.
**/
class ZEngine
{
    public:
        //! Static version information.
        static VersionInfo Version;

    private:        
        //! Static Pointer to Instance of ZEngine for Singleton.
        static ZEngine *sInstance;
        //! Pointer to Display
        SDL_Surface *mScreen;
        //! Fullscreen setting of Display
        bool mFullscreen;
        //! If ZEngine display has been setup.
        bool mInitialized;
        //! Keep track of paused state of game.
        bool mPaused;
        //! Keep track of if ZEngine should unpause on active event.
        bool mUnpauseOnActive;
        //! Value framerate strives to be at, set by SetDesiredFramerate.
        Uint8 mDesiredFramerate;
        //! Time scheduled for next update (used for framerate locked movement).
        Uint32 mNextUpdate;
        //! Keep track of time game was last paused.
        Uint32 mLastPause;
        //! Keep track of total globally paused time.
        Uint32 mPausedTime;
        //! Keep track of last screen update time.
        Uint32 mLastTime;
        //! Seconds per frame. (1/FPS)
        double mSecPerFrame;
        //! Keeps track of when engine thinks the images need to be reloaded (loss of focus in fullscreen).
        bool mNeedReload;
        //! bool describing Active or Inactive State of Game
        bool mActive;
        //! bool for checking if a Quit event has been detected
        bool mQuit;
        //! Pointer to array of Keys
        Uint8 *mKeyIsPressed;
        //! Array of keys, used by KeyPress
        bool mKeyPress[SDLK_LAST];
        //! X Position of Mouse
        int mMouseX;
        //! Y Position of Mouse
        int mMouseY;
        //! Mouse Button Information
        Uint8 mMouseB;
        //! C-style FILE* for error logging.
        std::FILE *mErrlog;
        //! Static Array of Error Identifiers
        std::string mErrorDesc[ZERR_LAST];
        //! Event filter, for users who need to process their own events.
        SDL_EventFilter mEventFilter;
        //! Random Generator for general use.
        ZRandGen mRandGen;

#ifdef USE_SDL_MIXER 
        //! Sound Initialized
        bool mSoundInitialized;
        //! Sound Bitrate
        int mSoundRate;
        //! Stereo setting of Sound Subsystem
        bool mStereo;
#endif 

    /////////////////////////////////
    //Singleton + Memory Management//
    /////////////////////////////////

    private:
        /*!
            \brief Constructor for ZEngine.
            
            Initialize ZEngine values to defaults. (Private so that only one instance may be created.)
        **/
        ZEngine();

    public:

        /*!
            \brief Get Instance.

            Static function, returns pointer to instance of ZEngine, creating an instance if none exist.
            \return Instance to the ZEngine.
        **/
        static ZEngine* GetInstance();

        /*!
            \brief Release Instance.

            Release memory held by instance of engine and closes window.
        **/
        static void ReleaseInstance();

    //////////////////
    //Initialization//
    //////////////////

        /*!
            \brief Create Display (window or fullscreen).

            Create a window or fullscreen display given the screen options, a title, icon, 

            \param width Desired width of screen or window.
            \param height Desired height of screen or window.
            \param bpp Desired BPP for screen, generally use 8,16 or 32, pass -1 if you want ZEngine to guess the best choice.
            \param fullscreen A bool for fullscreen setting.
            \param soundRate Desired sound bitrate.
            \param stereo A bool for stereo setting.
            \param title Window Title.
            \param icon Path to Icon File.
            \return result of setting up the display, true if everything went ok, false if any setup failed (check GetLastError).
        **/
        bool CreateDisplay(int width, int height, int bpp, bool fullscreen, std::string title, 
            int soundRate=22050, bool stereo=false, std::string icon="");

        /*!
            \brief Quit SDL and any Subsystems.

            Shut down SDL (and SDL_ttf,SDL_mixer if necessary) You shouldn't ever have to call this, ReleaseInstance calls this for you.
        **/
        void CloseDisplay();

        /*!
            \brief Toggle fullscreen/windowed mode.

            Safely toggles fullscreen/windowed mode, generally toggling modes will bring the need to reload images so it will
            set the ImagesNeedReload state to true.
            \since 0.8.2
        **/
        void ToggleFullscreen();

        /*!
            \brief Check state of ZEngine.

            Checks if ZEngine display has been properly setup.
            \since 0.8.2
            \return Boolean status of ZEngine, true if CreateDisplay has been successfully called, false if ZEngine has no display.
        **/
        bool Initialized();

    /////////////////
    //Screen Access//
    /////////////////

        /*!
            \brief Allow access to Screen Surface.

            Get pointer to screen SDL_Surface, allowing direct screen manipulation using SDL.
            \return Pointer to Display Surface.
        **/
        SDL_Surface *Display();

        /*!
            \brief Update display contents.

            Swap OpenGL buffers, and update screen, if a desired framerate is set it will delay to stay under that rate.
            Must be called every frame.
        **/
        void Update();

        /*!
            \brief Clear screen to a certain color (Black by default).

            Clears a rectangle on screen to a color, defaults to solid black.
            \param red Red component (0-255) of new color.
            \param green Green component (0-255) of new color.
            \param blue Blue component (0-255) of new color.
            \param alpha Alpha component (0-255) of new color.
        **/
        void Clear(Uint8 red=0, Uint8 green=0, Uint8 blue=0, Uint8 alpha=255);

#if (GFX_BACKEND == ZE_OGL)
    /////////////////////////////
    //OpenGL Specific Functions//
    /////////////////////////////

        /*!
            \brief Setup OpenGL ortho mode.

            Sets the OpenGL scaled orthographic mode, called once at beginning, no need to call
            unless you change the OpenGL mode manually.
        **/
        void SetGL2D();
#endif //GFX_BACKEND

    ////////////////////////////////////////////
    //Timer and Framerate Independent Movement//
    ////////////////////////////////////////////

        /*!
            \brief Sleep for a certain amount of time.

            Freeze everything for given number of milliseconds.
            \param milliseconds Number of milliseconds to freeze.
        **/
        void Delay(Uint32 milliseconds);

        /*!
            \brief Get Global ZEngine time.

            Get active time since ZEngine initialization in milliseconds, paused time doesn't count.
            \return Number of active milliseconds since initialization.
        **/
        Uint32 GetTime();

        /*!
            \brief Pause ZEngine.

            Pause ZEngine timer and all ZTimer objects that rely on ZEngine.
        **/
        void PauseTimer();

        /*!
            \brief Unpause ZEngine.

            Unpause ZEngine timer and all ZTimer objects that rely on ZEngine.
        **/
        void UnpauseTimer();

        /*!
            \brief Get Seconds Per Frame.

            Get double that describes the time passed between screen updates. (should be used for Framerate Independant Movement)
            \return Time between screen updates.
        **/
        double GetFrameTime();

        /*!
            \brief Get Frames Per Second.

            Get double representing current (approximate) FPS.  This value is always the same as 1/GetFrameTime().
            \since 0.8.2
            \return Current Framerate.
        **/
        double GetFramerate();

        /*!
            \brief Set Desired Framerate.

            Sets desired framerate, if engine gets ahead of desired rate during a frame it will stall in Update until
            current framerate is closer to that desired.  Acceptable values are 1-255, setting this value to 0 will disable this
            feature.  (Desired framerate is disabled upon initialization of ZEngine.)
            \since 0.8.2
            \param rate Desired framerate 1-255, or 0 to disable.
        **/
        void SetDesiredFramerate(Uint8 rate);

        /*!
            \brief Get Desired Framerate.

            Get desired framerate set by SetDesiredFramerate.
            \since 0.8.2
            \return Current setting for desired framerate.
        **/
        Uint8 GetDesiredFramerate();

        /*!
            \brief Check Engine Paused State.

            Find out if engine timer is paused.
            \return Paused State of engine.
        **/
        bool IsPaused();

    ////////////////////////////
    //Event and Input Handling//
    ////////////////////////////

        /*!
            \brief Find out if application is active.

            Function to find out if application currently has focus.
            \return bool telling active/inactive state of application.
        **/
        bool IsActive();

        /*!
            \brief Request A Quit.

            Tell the engine that it should behave as if a Quit was requested, does not call 
            any shutdown functions.
        **/
        void RequestQuit();

        /*!
            \brief Find out if user has requested to quit.

            Function to find out if user or operating system has requested program cease execution, can be 
            set by Alt-F4, SDL_Quit event or ZEngine::RequestQuit().
            \return bool telling if quit has been requested.
        **/
        bool QuitRequested();

        /*!
            \brief Set State of ImagesNeedReload.
            \param state False if images need to be reloaded, True if images have been reloaded.
        **/
        void SetReloadNeed(bool state);

        /*!
            \brief Find out if images should be reloaded.

            Function that is good to call every frame to check if images should be reloaded, usually only caused by loss of focus in 
            fullscreen.
            \return bool, True if images should be reloaded, false otherwise.
        **/
        bool ImagesNeedReload();
        
        /*!
            \brief Set Key repeat rate.

            Calls SDL_EnableKeyRepeat(rate,rate) because usually this is the desired movement style for games. 0 to disable.
            If 2 different values are needed SDL_EnableKeyRepeat can be called separately: http://sdldoc.csn.ul.ie/sdlenablekeyrepeat.php.

            \param rate Desired key repeat rate.
        **/
        void SetKeyRepeatRate(int rate);

        /*!
            \brief Find the state of a key.

            Function returns true/false based on if key is currently pressed or not.
            This is used when using keys as buttons, and you need to check if the button/key
            is currently pressed (ex. arrow keys).
            \param key Code of key to find status of.
            \return State of requested key.
        **/
        bool KeyIsPressed(SDLKey key);

        /*!
            \brief Find if key has been pressed since last check.

            Function returns true/false based on if key has been pressed since last check.
            This is what is good to use if you are trying to get user input where a key is only 
            counted once per press. (ex. typing in a name for a high scores list)
            \param key Code of key to find status of.
            \return State of requested key.
        **/
        bool KeyPress(SDLKey key);

        /*!
            \brief Hide mouse cursor.
            
            Hide the system mouse cursor.
        **/
        void HideCursor();

        /*!
            \brief Show mouse cursor.
            
            Show the system mouse cursor.
        **/
        void ShowCursor();

        /*!
            \brief Get X Position of Mouse.

            Find X Position of Mouse on screen.
            \return X Position of Mouse.
        **/
        int MouseX();

        /*!
            \brief Get Y Position of Mouse.

            Find Y Position of Mouse on screen.
            \return Y Position of Mouse.
        **/
        int MouseY();

        /*!
            \brief Get Status of Left Button.

            Get pressed status of left button of mouse.
            \return true if left button is pressed, false otherwise.
        **/
        bool LButtonPressed();

        /*!
            \brief Get Status of Right Button.

            Get pressed status of right button of mouse.
            \return true if right button is pressed, false otherwise.
        **/
        bool RButtonPressed();

        /*!
            \brief Get status of Middle Button.

            Get pressed status of middle button if available.
            \return true if middle button is pressed, false if it is not or if it does not exist.
            \since 0.8.5
        **/
        bool MButtonPressed();

        /*!
            \brief Check if mouse is in given rectangle.

            Return status of mouse in current rectangle (eg. GUI buttons).
            \param rect Rectangle to check if mouse is in.
            \return true if mouse is in rectangle, false otherwise
        **/
        bool MouseInRect(SDL_Rect *rect);

        /*!
            \brief Check if mouse is in given rectangle.

            Return status of mouse in current rectangle (eg. GUI buttons).
            \param rect Rectangle to check if mouse is in.
            \return true if mouse is in rectangle, false otherwise
        **/
        bool MouseInRect(ZRect rect);

        /*!
            \brief Check for Activation, Window Manager, and Quit Events.

            Cycle through event queue, processing events, updating all Event Related variables, should be called once per frame.
        **/
        void CheckEvents();

        /*!
            \brief Add a SDL Event Filter for user processing of events.

            This is only needed when you need tight control with ZEngine.  The parameter processed as if it were passed to 
            SDL_SetEventFilter, generally only those with a good amount of SDL experience should use this function or 
            ZEngine's internal message state could be corrupted.  For more information on SDL_SetEventFilter see 
            http://sdldoc.csn.ul.ie/sdlseteventfilter.php.  (FYI: The parameter is now actually processed in check events, 
            not passed to the SDL function, this is done because of problems with singletons and event threading.)
            \since 0.8.2
            \param filter An SDL_EventFilter (A function that takes a const SDL_Event* and returns 0 if the event should be removed from 
            the event queue and 1 otherwise.)
        **/
        void SetEventFilter(SDL_EventFilter filter);

    /////////////////
    //Error Logging//
    /////////////////

    public:
        /*!
            \brief Modify Error Logging.

            Change the way errors are logged and the file they are logged to, before calling this errors are logged to stderr.
            (SDL may define stderr.txt on some platforms.)
            \since 0.8.6
            \param logFile Name of file to use as log, passing in stderr or stdio will set the log to the respective C stream.
            Passing in nothing will not change the current error log file, which defaults to stderr.
        **/
        void SetErrorLog(std::string logFile);

        void DisableErrorLog();


        /*!
            \brief Report an error.

            Adds the error to the the error queue, and sets the current error to this error.
            \since 0.8.2
        **/
        void ReportError(ZErrorCode type, std::string desc="", ...);

        /*!
            \brief Get the last error.

            Get the last error reported.
            \since 0.8.2
            \return ZErrorCode of last error reported.
        **/
        ZErrorCode GetLastError();

        /*!
            \brief Write to the log.

            Write a std::string to the log, allowing special usage of the error log.
            \since 0.8.2
            \param str String to write to log file.
        **/
        void WriteLog(std::string str);

        /*!
            \brief Flush Stack of Errors to file.

            Write the error stack to the error log.
            \since 0.8.2
        **/
        void FlushErrors();

    ////////////////////////////
    //Random Number Generation//
    ////////////////////////////
        /*!
            \brief Seed random number generator. 

            Reseed Mersenne Twister random number generator.  NOTE: Generator is initialized upon creation of object using time.
            \param seed Seed for random sequence.
        **/
        void SeedRandGen(unsigned long seed);

        /*!
            \brief Obtain random integer [0,max).

            Obtain random int l where 0 <= l < max.
            \param max Limit for random number.
            \return Random unsigned int.
        **/
        unsigned int Rand(unsigned int max);

        /*!
            \brief Obtain random integer [0,max).

            Obtain random long l where 0 <= l < max.
            \param max Limit for random number.
            \return Random unsigned long.
        **/
        unsigned long Rand(unsigned long max);

        /*!
            \brief Obtain random integer [min,max].

            Obtain random int l where min <= l <= max.
            \param min Lower limit for random number.
            \param max Upper limit for random number.
            \return Random int.
        **/
        int Rand(int min, int max);

        /*!
            \brief Obtain random integer [min,max].

            Obtain random long l where min <= l <= max.
            \param min Lower limit for random number.
            \param max Upper limit for random number.
            \return Random long.
        **/
        long Rand(long min, long max);

        /*!
            \brief Obtain random integer [min,max].

            Obtain random float l where min <= l <= max.
            \param min Lower limit for random number.
            \param max Upper limit for random number.
            \return Random float.
        **/
        float Rand(float min, float max);

        /*!
            \brief Obtain random integer [min,max].

            Obtain random double l where min <= l <= max.
            \param min Lower limit for random number.
            \param max Upper limit for random number.
            \return Random double.
        **/
        double Rand(double min, double max);

        /*!
            \brief Obtain random double [0,1).

            Obtain random double d where 0 <= d < 1.
            \return Random double [0,1).
        **/
        double RandDouble();

    /////////////
    //Accessors//
    /////////////

        /*!
            \brief Get Current Display Width.

            Get Width of Window or Fullscreen mode.
            \return Width of Display.
        **/
        int DisplayWidth();

        /*!
            \brief Get Current Display Height.

            Get Height of Window or Fullscreen mode.
            \return Height of Display.
        **/
        int DisplayHeight();

        /*!
            \brief Get Current Display BPP.

            Get color depth of Window or Fullscreen mode. BPP means bits per pixel.
            \return BPP or depth of Display.
        **/
        int DisplayDepth();

#ifdef DEPRECIATED
        /*!
            \brief Get Current Display Width.

            Get Width of Window or Fullscreen mode.
            \return Width of Display.
        **/
        int Width();

        /*!
            \brief Get Current Display Height.

            Get Height of Window or Fullscreen mode.
            \return Height of Display.
        **/
        int Height();

        /*!
            \brief Get Current Display BPP.

            Get BPP of Window or Fullscreen mode.
            \return BPP of Display.
        **/
        int BPP();
#endif //DEPRECIATED

        /*!
            \brief Get Fullscreen setting.

            Get Fullscreen setting of Display.
            \return True if Fullscreen, False if Windowed
        **/
        bool IsFullscreen();
};

}

#endif //__ze_zengine_h__
