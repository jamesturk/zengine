/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZAnimation.h
    \brief Definition file for ZAnimation.

    Definition file for ZAnimation, a class for animations using ZImage.
    <br>$Id: ZE_ZAnimation.h,v 1.2 2003/12/24 04:46:48 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zanimation_h__
#define __ze_zanimation_h__

#include "ZE_ZEngine.h"
#include "ZE_ZImage.h"

namespace ZE
{

enum ZAnimType
{
    ZANIM_NONE,
    ZANIM_ONCE,
    ZANIM_LOOP,
    ZANIM_REVERSE
};


class ZAnimation
{
    protected:
        //! Pointer to ZEngine object.
        ZEngine *rEngine;
        //! Pointer to dynamic array of images.
        ZImage *rAnimImages;
        //! Current frame.
        int rCurFrame;
        //! Number of frames in animation.
        int rNumFrames;
        //! Frame increment, will always be -1,0, or 1. 
        int rFrameStep;
        //! Delay between frames in ms.
        Uint32 rFrameDelay;
        //! Time of next step.
        Uint32 rNextFrameTime;
        //! Behavior of animation.
        ZAnimType rAnimType;
        //! Boolean, true if image is to be run backwards, false otherwise.
        bool rBackwards;

    public:
        /*!
            \brief Default constructor for ZAnimation.

            Sets all members to default values.
        **/
        ZAnimation();

        /*!
            \brief Complete constructor for ZAnimation.

            Assigns values of members to given arguments via call to Create.
            \param images Array of images for animation.  (Note: array is not copied)
            \param numFrames Number of images in array pointed to by 'images'
            \param frameDelay Delay (in milliseconds) between frames.
            \param type One of the ZAnimType enums that control what animation does after last frame is reached.
            \param backwards Boolean, true if image is to be run backwards, false otherwise (defaults to false).
        **/
        ZAnimation(ZImage *images, int numFrames, Uint32 frameDelay, ZAnimType type, bool backwards=false);

        /*!
            \brief All-at-once function for setting up ZAnimation.

            Calls SetAnimImages,SetFrameDelay,SetAnimType and SetAnimSize with passed parameters.
            \param images Array of images for animation.  (Note: array is not copied)
            \param numFrames Number of images in array pointed to by 'images'
            \param frameDelay Delay (in milliseconds) between frames.
            \param type One of the ZAnimType enums that control what animation does after last frame is reached.
            \param backwards Boolean, true if image is to be run backwards, false otherwise (defaults to false).
        **/
        void Create(ZImage *images, int numFrames, Uint32 frameDelay, ZAnimType type, bool backwards=false);

        /*!
            \brief Sets images for animation.

            Sets images for animation to use, should be array of images
            \param images Array of images for animation.  (Note: array is not copied)
            \param numFrames Number of images in array pointed to by 'images'
        **/
        void SetAnimImages(ZImage *images, int numFrames);

        /*!
            \brief Sets frame delay between images.

            Set delay between images in milliseconds.
            \param frameDelay Delay (in milliseconds) between frames.
        **/
        void SetFrameDelay(Uint32 frameDelay);

        /*!
            \brief Sets behavior of animation after last frame is reached and direction of animation.

            Sets behavior of animation after last frame as well as the initial direction of the animation.
            \param type One of the ZAnimType enums that control what animation does after last frame is reached.
            \param backwards Boolean, true if image is to be run backwards, false otherwise (defaults to false).
        **/
        void SetAnimType(ZAnimType type, bool backwards=false);

        /*!
            \brief Resets animation.

            Sets frame to first frame and pauses animation.
        **/
        void Reset();

        /*!
            \brief Starts animation.

            Starts animation, this must once be called to begin animation.
        **/
        void Start();

        /*!
            \brief Pauses animation.

            Halts animation at current frame.
        **/
        void Pause();

        /*!
            \brief Sets displayed frame manually.

            Sets displayed frame, uses bounds checking, also accepts negative indices.
            \param frame Frame to display.  In an animation with N frames, valid frames are 0 to N-1, and also -1 to -N
                    where negative indices work so that -1 is the last frame, -2 is the second to last, and so on.
        **/
        void SetFrame(int frame);

        /*!
            \brief Updates animation.

            Updates the animation, changing the frame if needed.  This function should be called every frame
            so that the frame may be changed.
        **/
        void Update();

        /*!
            \brief Draws current frame to screen.

            Draws current frame to screen at given position, should be called every frame that animation is to be drawn.
            If stopped, draws first frame, if paused draws frame paused on.
            \param x X position for animation to be drawn at.
            \param y Y position for animation to be drawn at.
        **/
        void Draw(float x, float y) const;

        /*!
            \brief Gets running status of animation.

            Returns status of animation, running or halted.
            \return True if animation is running, false if it is paused or stopped.
        **/
        bool Running() const;
};

}

#endif //__ze_zanimation_h__
