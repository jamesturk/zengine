/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header:
File: ZE_ZEngine.h <br>
Description: Header file for ZEngine class, the core of the ZEngine. <br>
Author(s): James Turk <br>
$Id: ZE_ZEngine.h,v 1.1.1.1 2002/11/21 05:41:10 cozman Exp $<br>

    \file ZE_ZEngine.h
    \brief Definition file for core ZEngine class.

    ZEngine Game Engine core Engine definition.
**/

#ifndef __ze_zengine_h__
#define __ze_zengine_h__

#include "ZE_DataPtr.h"
#include "ZE_Error.h"
#include "ZE_Defines.h"
#include "ZE_Includes.h"

/*!
    \brief ZEngine Namespace.
    
    Namespace for ZEngine classes and utility functions.
**/
namespace ZE
{

/*!
    \brief Main ZEngine Singleton Class

    ZEngine Singleton Class, accessible from anywhere in a ZEngine-based program by nature.  Controls core elements of program and does 
    majority of SDL wrapping.  Also keeps track of loaded data and helps programs avoid memory leaks and dangling pointers.
**/
class ZEngine
{
    /////////////////////////////////
    //Singleton + Memory Management//
    /////////////////////////////////

    private:
        //! Static Pointer to Instance of ZEngine for Singleton.
        static ZEngine *sInstance;

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

        /*!
            \brief Get Current Version.

            Get Version Number of ZEngine. (Major.Minor.Extension#)
            \return string containing version number
        **/
        static string GetVersion();

    //////////////////
    //Initialization//
    //////////////////

    private:
        //! Width of Display
        int mWidth;
        //! Height of Display
        int mHeight;
        //! BPP Setting of Display
        int mBPP;
        //! Fullscreen setting of Display
        bool mFullscreen;

#ifdef USE_SDL_MIXER 
        //! Sound Bitrate
        int mRate;
        //! Stereo setting of Sound Subsystem
        bool mStereo;
#endif 


    public:
        //add initialization

        /*!
            \brief Setup Display for SDL.

            Sets display parameters to specified parameters. (called before CreateDisplay)

            \param width Desired width of screen or window.
            \param height Desired height of screen or window.
            \param bpp Desired BPP for screen (only works in fullscreen).
            \param fullscreen A bool for fullscreen setting.
        **/
        void SetupDisplay(int width, int height, int bpp, bool fullscreen);

#ifdef USE_SDL_MIXER
        /*!
            \brief Initialize Sound for SDL.

            Set sound settings to specified parameters. (called before CreateDisplay)

            \param rate Desired sound bitrate.
            \param stereo A bool for stereo setting.
        **/
        void SetupSound(int rate, bool stereo);
#endif 

        /*!
            \brief Create Window with predefined settings.

            SetupDisplay and SetupSound should be called prior to this to change settings, settings from those do not go into effect 
            until this function is called.  Specify no icon file to use default OS icon.

            \param title Window Title.
            \param icon Path to Icon File.
        **/
        void CreateWindow(string title, string icon="");

        /*!
            \brief Quit SDL and any Subsystems.

            Shut down SDL (and SDL_ttf,SDL_mixer if necessary).
        **/
        void CloseWindow();

    /////////////////
    //Screen Access//
    /////////////////

    private:
        //! Pointer to Display
        SDL_Surface *mScreen;

    public:
        /*!
            \brief Allow access to Screen Surface.

            Get pointer to screen SDL_Surface, allowing direct screen manipulation using SDL.
            \return Pointer to Display Surface.
        **/
        SDL_Surface *GetDisplay();

        /*!
            \brief Update screen contents.

            Flip double buffer in SDL if double buffered, otherwise tell video to refresh entire screen.
        **/
        void UpdateScreen();

        /*!
            \brief Create Color in SDL Uint32 Format

            Turn RGBA values into SDL Uint32 color. (Alpha value will be ignored if not in use)

            \param r Red component of color (0-255).
            \param g Green component of color (0-255).
            \param b Blue component of color (0-255).
            \param a Alpha (translucency) component of color (0-255). [Default 255]
            \return Uint32 of color requested.
        **/
        Uint32 MapColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255);

        /*!
            \brief Clear screen or portion of screen to a color.

            Clears a rectangle on screen to a color.
            \param color Color to clear surface to, defaults to black.
            \param rect Rectangle of screen to clear or NULL for entire surface.
        **/
        void Clear(Uint32 color=0, SDL_Rect *rect=NULL);

    ////////////////////////////////////////////
    //Timer and Framerate Independent Movement//
    ////////////////////////////////////////////
    
    private:
        //! Keep track of paused state of game.
        bool mPaused;
        //! Keep track of if ZEngine should unpause on active event.
        bool mUnpauseOnActive;
        //! Keep track of time game was last paused.
        Uint32 mLastPause;
        //! Keep track of total globally paused time.
        Uint32 mPausedTime;
        //! Keep track of last screen update time.
        Uint32 mLastTime;
        //! Seconds per frame.
        double mSecPerFrame;

    public:
        /*!
            \brief Sleep for a certain amount of time.

            Freeze everything for given number of milliseconds.
            \param milliseconds Number of milliseconds to freeze.
        **/
        void Sleep(Uint32 milliseconds);

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

            Get double that describes the time passed between screen updates. (used for Framerate Independant Movement)
            \return Time between screen updates.
        **/
        double GetFrameTime();

        /*!
            \brief Check Engine Paused State.

            Find out if engine timer is paused.
            \return Paused State of engine.
        **/
        bool IsPaused();

    ////////////////////////////
    //Event and Input Handling//
    ////////////////////////////

    private:
        //! bool describing Active or Inactive State of Game
        bool mActive;
        //! bool for checking if a Quit event has been detected
        bool mQuit;
        //! Pointer to array of Keys
        Uint8 *mKeyPressed;
        //! X Position of Mouse
        int mMouseX;
        //! Y Position of Mouse
        int mMouseY;
        //! Mouse Button Information
        Uint8 mMouseB;

    public:
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
            \brief Find the state of a key.

            Function returns true/false based on if key is pressed or not.
            \param key code of key to find status of.
            \return bool state of requested key.
        **/
        bool KeyIsPressed(SDLKey key);

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
        int GetMouseX();

        /*!
            \brief Get Y Position of Mouse.

            Find Y Position of Mouse on screen.
            \return Y Position of Mouse.
        **/
        int GetMouseY();

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

#ifdef USE_PHYSFS
    ////////////////////
    //Physfs Utilities//
    ////////////////////
    public:
        /*!
            \brief Initialize PhysicsFS

            Sets up PhysicsFS, must be called when application is started.
            \param argv argv[0] from application's main.
        **/
        void InitPhysFS(string argv);

        /*!
            \brief Add Directory to PhysFS Search Path.

            Add Directory to PhysicsFS search path, the path it looks in for files when attempting to load.
            \param dir Directory to add to search path.
        **/
        void AddPhysFSDir(string dir);

#endif    //USE_PHYSFS


    ////////////////////////////
    //Data Loading + Unloading//
    ////////////////////////////
    public:
        /*!
            \brief Load an Image.

            Loads an Image to an ImageData class which keeps vital information on the Image.
            \param filename path to file to load.
            \return A ImageData class containing filename and pointer to data.
        **/
        ImageData LoadImage(string filename);

        /*!
            \brief Free an Image.

            Free memory of an Image in an ImageData class.
            \param image ImageData structure of image to free.
        **/
        void FreeImage(ImageData &image);

#ifdef USE_SDL_MIXER
        /*!
            \brief Load a Sound

            Loads a Sound to a SoundData class which keeps vital information on the Sound
            \param filename path to file to load.
            \return A SoundData class containing filename and pointer to data.
        **/
        SoundData LoadSound(string filename);

        /*!
            \brief Free a Sound.

            Free memory of a Sound in a SoundData class.
            \param sound SoundData structure of sound to free.
        **/
        void FreeSound(SoundData &sound);

        /*!
            \brief Load a Music File

            Loads a Music Clip to a MusicData class which keeps vital information on the Music Data
            \param filename path to file to load.
            \return A MusicData class containing filename and pointer to data.
        **/
        MusicData LoadMusic(string filename);

        /*!
            \brief Free a Music Sample.

            Free memory of Music in a MusicData class.
            \param music MusicData structure of music to free.
        **/
        void FreeMusic(MusicData &music);
#endif

#ifdef USE_SDL_TTF
        /*!
            \brief Load a Font.

            Loads a Font to a FontData class which keeps vital information on the Font
            \param filename path to file to load.
            \param size point size of font
            \return A FontData class containing filename and pointer to data.
        **/
        FontData LoadFont(string filename, int size);

        /*!
            \brief Free a Font.

            Free memory of a Font in a FontData class.
            \param font FontData structure of font to free.
        **/
        void FreeFont(FontData &font);
#endif 

    /////////////
    //Accessors//
    /////////////
    
    public:    
        /*!
            \brief Get Current Display Width.

            Get Width of Window or Fullscreen mode.
            \return Width of Display.
        **/
        int GetWidth();

        /*!
            \brief Get Current Display Height.

            Get Height of Window or Fullscreen mode.
            \return Height of Display.
        **/
        int GetHeight();

        /*!
            \brief Get Current Display BPP.

            Get BPP of Window or Fullscreen mode.
            \return BPP of Display.
        **/
        int GetBPP();

        /*!
            \brief Get Fullscreen setting.

            Get Fullscreen setting of Display.
            \return True if Fullscreen, False if Windowed
        **/
        bool IsFullscreen();
};

}

#endif //__ze_zengine_h__
