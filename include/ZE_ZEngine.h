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
    <br>$Id: ZE_ZEngine.h,v 1.42 2003/07/05 00:40:45 cozman Exp $<br>
    \author James Turk
**/

//revision on this is so high.. can this be lowered?

#ifndef __ze_zengine_h__
#define __ze_zengine_h__

#include "ZE_Defines.h"
#include "ZE_Utility.h"
#include "ZE_Includes.h"
#include "ZE_ZError.h"
#include "ZE_ZRandGen.h"
#include "VersionInfo.h"

/*!
    \brief ZEngine Namespace.
    
    Namespace for ZEngine classes and utility functions.
**/
namespace ZE
{

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
        //! Width of Display
        int mWidth;
        //! Height of Display
        int mHeight;
        //! BPP Setting of Display
        int mBPP;
        //! Fullscreen setting of Display
        bool mFullscreen;
        //! If ZEngine display has been setup.
        bool mInitialized;
        //! Pointer to Display
        SDL_Surface *mScreen;
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
        //! Seconds per frame.
        double mSecPerFrame;
        //! bool which is only set to true if the engine thinks the images need to be reloaded (loss of focus in fullscreen).
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
        //! Stack of Errors which have occured.
        std::queue<ZError> mErrorQueue;
        //! Current error.
        ZError mCurError;
        //! Option controlling how logfile is used.
        bool mLogAllErrors;
        //! C-style FILE* for error logging.
        std::FILE *mErrlog;
        //! Event filter, for users who need to process their own events.
        SDL_EventFilter mEventFilter;
        //! Random Generator for general use.
        ZRandGen mRandGen;

#ifdef USE_SDL_MIXER 
        //! Sound Bitrate
        int mRate;
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
            \brief Setup Display for SDL.

            Sets display parameters to specified parameters. (called before CreateDisplay)

            \param width Desired width of screen or window.
            \param height Desired height of screen or window.
            \param bpp Desired BPP for screen, generally use 8,16 or 32, pass -1 if you want ZEngine to guess the best choice.
            \param fullscreen A bool for fullscreen setting.
        **/
        void SetupDisplay(int width, int height, int bpp, bool fullscreen);

#ifdef USE_SDL_MIXER
        /*!
            \brief Initialize Sound for SDL.

            Set sound settings to specified parameters. (If not called before CreateDisplay rate will default to 22050+mono)

            \param rate Desired sound bitrate.
            \param stereo A bool for stereo setting.
        **/
        void SetupSound(int rate, bool stereo);
#endif 

        /*!
            \brief Create Display with predefined settings.

            SetupDisplay and SetupSound should be called prior to this to change settings, settings from those do not go into effect 
            until this function is called.  Specify no icon file to use default icon for OS.  Returns result of setting up ZEngine, and logs 
            error if false is returned (Trys not to fail + returns bool in versions >= 0.8.2).

            \param title Window Title.
            \param icon Path to Icon File.
            \return result of setting up the display, true if everything went ok, false if any setup failed (check GetLastError).
        **/
        bool CreateDisplay(std::string title, std::string icon="");

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
            \param red Red component (0.0-1.0) of new color.
            \param green Green component (0.0-1.0) of new color.
            \param blue Blue component (0.0-1.0) of new color.
            \param alpha Alpha component (0.0-1.0) of new color.
        **/
        void Clear(float red=0.0f, float green=0.0f, float blue=0.0f, float alpha=1.0f);

    /////////////////////////////
    //OpenGL Specific Functions//
    /////////////////////////////

        /*!
            \brief Setup OpenGL ortho mode.

            Sets the OpenGL scaled orthographic mode, called once at beginning, no need to call
            unless you change the OpenGL mode manually.
        **/
        void SetGL2D();

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
            \param key Code of key to find status of.
            \return State of requested key.
        **/
        bool KeyIsPressed(SDLKey key);

        /*!
            \brief Find if key has been pressed since last check.

            Function returns true/false based on if key has been pressed since last check.
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
            \brief Check if mouse is in given rectangle.

            Return status of mouse in current rectangle (used for buttons)
            \param rect Rectangle to check if mouse is in.
            \return true if mouse is in rectangle, false otherwise
        **/
        bool MouseInRect(SDL_Rect *rect);

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

#ifdef USE_PHYSFS
    ////////////////////
    //Physfs Utilities//
    ////////////////////
        /*!
            \brief Initialize PhysicsFS

            Sets up PhysicsFS, must be called when application is started.
            \param argv argv[0] from application's main.
        **/
        void InitPhysFS(std::string argv);

        /*!
            \brief Add Directory to PhysFS Search Path.

            Add Directory to PhysicsFS search path, the path it looks in for files when attempting to load.
            \param dir Directory to add to search path.
        **/
        void AddPhysFSDir(std::string dir);

#endif    //USE_PHYSFS

    /////////////////
    //Error Logging//
    /////////////////
    private:
        /*!
            \brief Writes an error to file.

            Writes error to current error file.
            \since 0.8.2
            \param error ZError to write to file.
        **/
        void LogError(ZError error);

    public:
        /*!
            \brief Modify Error Logging.

            Change the way errors are logged and the file they are logged to, before calling this errors are logged to stderr.
            (SDL may define stderr.txt on some platforms.)
            \since 0.8.2
            \param logAll If set to true every error will be written to file instead of stored in the logfile.
            \param logFile Name of file to use as log, passing in stderr or stdio will set the log to the C streams. 
            Passing in nothing will not change the current error log file, which defaults to stderr.
        **/
        void SetErrorLog(bool logAll, std::string logFile="");

        /*!
            \brief Report an error.

            Adds the error to the the error queue, and sets the current error to this error.
            \since 0.8.2
            \param code ZErrorCode of error.
            \param desc Optional std::string describing error.
            \param file Optional argument specifying the file the error occured in.
            \param line Optional argument specifying the line the error occured on.
        **/
        void ReportError(ZErrorCode code, std::string desc="", std::string file="", unsigned int line=0);

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

    ////////////////////////////
    //Data Loading + Unloading//
    ////////////////////////////
        /*!
            \brief Load an Image.

            Loads an Image to an ImageData class which keeps vital information on the Image.
            \param filename path to file to load.
            \return A SDL_Surface pointer to data.
        **/
        SDL_Surface* LoadImage(std::string filename);

#ifdef USE_SDL_MIXER
        /*!
            \brief Load a Sound

            Loads a Sound to a SoundData class which keeps vital information on the Sound
            \param filename path to file to load.
            \return A Mix_Chunk pointer to data.
        **/
        Mix_Chunk* LoadSound(std::string filename);

        /*!
            \brief Load a Music File

            Loads a Music Clip to a MusicData class which keeps vital information on the Music Data
            \param filename path to file to load.
            \return A Mix_Music pointer to data.
        **/
        Mix_Music* LoadMusic(std::string filename);
#endif

#ifdef USE_SDL_TTF
        /*!
            \brief Load a Font.

            Loads a Font to a FontData class which keeps vital information on the Font
            \param filename path to file to load.
            \param size point size of font
            \return A TTF_Font pointer to data.
        **/
        TTF_Font* LoadFont(std::string filename, int size);
#endif 

    /////////////
    //Accessors//
    /////////////

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

        /*!
            \brief Get Fullscreen setting.

            Get Fullscreen setting of Display.
            \return True if Fullscreen, False if Windowed
        **/
        bool IsFullscreen();
};

}

#endif //__ze_zengine_h__
