/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZSimpleParticleSystem.h
    \brief Definition and implementation file for a simple particle system for ZEngine.

    Definition and implementation file for ZEngine simple particle system, ZSimpleParticleSystem based on ZBaseParticleSystem.
    Due to problems with template classes the template implementation needs to be in the same file as the declaration.
    <br>$Id: ZE_ZSimpleParticleSystem.h,v 1.3 2003/07/10 23:45:09 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zsimpleparticlesystem_h__
#define __ze_zsimpleparticlesystem_h__

#include "ZEngine.h"

namespace ZE
{

/*!
    \brief Simple particle class for ZSimpleParticleSystem.

    General purpose particle, contains needed variables for a functional particle system.
**/
class ZSimpleParticle : public ZBaseParticle
{
    public:
        //! Previous X position of particle.
        float xPrev;
        //! Previous Y position of particle.
        float yPrev;
        //! X Velocity of particle per second.
        float xVel;
        //! Y Velocity of particle per second.
        float yVel;
        //! Energy change per second.
        float energyDelta;
        //! Size of particle.
        float size;
        //! Size change per second.
        float sizeDelta;
        //! Red component of particle color.
        Uint8 r;
        //! Green component of particle color.
        Uint8 g;
        //! Blue component of particle color.
        Uint8 b;
        //! Alpha component of particle color.
        Uint8 a;
};

/*!
    \brief Possible draw styles for ZSimpleParticleSystem.

    Possible draw styles for ZSimpleParticleSystem, each specifies different code with which the particles will be drawn.
**/
enum ParticleDrawStyle 
{ 
    DS_POINT,   /*!< Draw particles as simple points.  */
    DS_LINE,    /*!< Draw particles as lines between the current position and the last.  */
    DS_IMAGE    /*!< Draw particles as an image.  */
};

/*!
    \brief ZSimpleParticleSystem class, a simple particle system provided originally as an example.

    ZSimpleParticleSystem class, example of implementation of a particle system on top of ZBaseParticleSystem base, 
    designed for flexibility and ease of use over speed.  More specific, therefore even less optimized for specific 
    circumstances.  Should be concidered usable but not optimal. (Although it is a great source of code for your 
    own implementations.)
**/
template <class particleType>
class ZSimpleParticleSystem : public ZBaseParticleSystem<particleType>
{
    protected:
        //! Draw style, one of the three enumerated values specifying how particles will be drawn.
        ParticleDrawStyle rStyle;
        //! Image to draw (only used if rStyle is DS_IMAGE).
        ZImage rImage;
        //! Minimum X value for starting position.
        float rMinX;
        //! Maximum X value for starting position.
        float rMaxX;
        //! Minimum Y value for starting position.
        float rMinY;
        //! Maximum Y value for starting position.
        float rMaxY;
        //! Minimum X velocity, particle moves it's velocity every second.
        float rMinXVel;
        //! Maximum X velocity, particle moves it's velocity every second.
        float rMaxXVel;
        //! Minimum Y velocity, particle moves it's velocity every second.
        float rMinYVel; 
        //! Maximum Y velocity, particle moves it's velocity every second.
        float rMaxYVel;
        //! Minimum starting energy. (Remember particles with energy values <= 0 are removed.)
        float rMinEnergy;
        //! Maximum starting energy.
        float rMaxEnergy;
        //! Minimum energy change per second.
        float rMinEnergyDelta;
        //! Maximum energy change per second.
        float rMaxEnergyDelta;
        //! Minimum starting size.
        float rMinSize;
        //! Maximum starting size.
        float rMaxSize;
        //! Minimum size change per second.
        float rMinSizeDelta;
        //! Maximum size change per second.
        float rMaxSizeDelta;
        //! Minimum red component of color, 0-255.
        Uint8 rMinRed;
        //! Maximum red component of color, 0-255.
        Uint8 rMaxRed;
        //! Minimum green component of color, 0-255.
        Uint8 rMinGreen;
        //! Maximum green component of color, 0-255.
        Uint8 rMaxGreen;
        //! Minimum blue component of color, 0-255.
        Uint8 rMinBlue;
        //! Maximum blue component of color, 0-255.
        Uint8 rMaxBlue;
        //! Minimum alpha of particle, 0-255.
        Uint8 rMinAlpha;
        //! Maximum alpha of particle, 0-255.
        Uint8 rMaxAlpha;

        /*!
            \brief Function which creates a new particle.

            Implementation of pure virtual NewParticle from ZBaseParticleSystem, creates a new particle with 
            it's members set to values between their min and max value as set by the system.
        **/
        virtual particleType NewParticle();

        /*!
            \brief Updates a given particle given it's index and the elapsedTime.

            Implementation of pure virtual UpdateParticle from ZBaseParticleSystem, updates a given particle
            relative to the elapsed time.
            \param index Index of particle in rParticles array to update.
            \param elapsedTime Decimal portion of a second since last call.
        **/
        virtual void UpdateParticle(int index, float elapsedTime);

    public:
        /*!
            \brief Draws all particles.

            Implementation of pure virtual Render from ZBaseParticleSystem, draws all particles in specified
            ParticleDrawStyle.
        **/
        virtual void Render();

        /*!
            \brief Reload image.

            Reload image if mode is DS_IMAGE, usage is same as ZImage::Reload.
        **/
        void ReloadImage();

        /*!
            \brief Sets ParticleDrawStyle for this system.

            Sets the method of drawing particles, point, line, or image particles.
            \param style ParticleDrawStyle for this particle system to use.
        **/
        void SetDrawStyle(ParticleDrawStyle style);

        /*!
            \brief Sets image for particle system.

            Sets image for particle system to use, assuming the drawing style is DS_IMAGE.
            \brief filename Filename of image to load for the system.
        **/
        void SetImage(std::string filename);

        /*!
            \brief Sets the range of initial positions.

            Sets the range of initial positions for a new particle.
            \param minX Minimum X coordinate for new particles.
            \param minY Minimum Y coordinate for new particles.
            \param maxX Maximum X coordinate for new particles.
            \param maxY Maximum Y coordinate for new particles.
        **/
        void SetPosRange(float minX, float minY, float maxX, float maxY);

        /*!
            \brief Sets range of velocities for particles.

            Sets range from which a new particle obtains it's random velocity,
            \param minXVel Minimum X velocity of a particle.
            \param minYVel Minimum Y velocity of a particle.
            \param maxXVel Maximum X velocity of a particle.
            \param maxYVel Maximum Y velocity of a particle.
        **/
        void SetVelocityRange(float minXVel, float minYVel, float maxXVel, float maxYVel);

        /*!
            \brief Sets range of initial energy and energyDelta. 

            Sets the possible ranges for a particles starting energy and it's energyDelta.  Particles with
            energy less than or equal to 0 are deleted by ZBaseParticleSystem::Update.
            \param minEnergy Minimum initial energy.
            \param maxEnergy Maximum initial energy.
            \param minEnergyDelta Minimum energy delta.
            \param maxEnergyDelta Maximum energy delta.
        **/
        void SetEnergyRange(float minEnergy, float maxEnergy, float minEnergyDelta=0, float maxEnergyDelta=0);

        /*!
            \brief Sets range of initial size and sizeDelta. 

            Sets the possible ranges for a particles starting size and it's sizeDelta.
            \param minSize Minimum initial size.
            \param maxSize Maximum initial size.
            \param minSizeDelta Minimum size delta.
            \param maxSizeDelta Maximum size delta.
        **/
        void SetSizeRange(float minSize, float maxSize, float minSizeDelta=0, float maxSizeDelta=0);

        /*!
            \brief Set range of color for a new particle.

            Sets range of possible colors, by component, for a new particle.
            \param minRed Minimum value of red component (0-255).
            \param maxRed Minimum value of red component (0-255).
            \param minGreen Minimum value of green component (0-255).
            \param maxGreen Minimum value of green component (0-255).
            \param minBlue Minimum value of blue component (0-255).
            \param maxBlue Minimum value of blue component (0-255).
            \param minAlpha Minimum value of alpha value (0-255).
            \param maxAlpha Minimum value of alpha value (0-255).
        **/
        void SetColorRange(Uint8 minRed, Uint8 maxRed, Uint8 minGreen, Uint8 maxGreen, 
                            Uint8 minBlue, Uint8 maxBlue, Uint8 minAlpha, Uint8 maxAlpha);
};

//implementation//

template <class particleType>
particleType ZSimpleParticleSystem<particleType>::NewParticle()
{
    particleType p;
    
    p.xPrev = p.xPos = rEngine->Rand(rMinX,rMaxX);
    p.yPrev = p.yPos = rEngine->Rand(rMinY,rMaxY);
    p.xVel = rEngine->Rand(rMinXVel,rMaxXVel);
    p.yVel = rEngine->Rand(rMinYVel,rMaxYVel);
    p.energy = rEngine->Rand(rMinEnergy,rMaxEnergy);
    p.energyDelta = rEngine->Rand(rMinEnergyDelta,rMaxEnergyDelta);
    p.size = rEngine->Rand(rMinSize,rMaxSize);
    p.sizeDelta = rEngine->Rand(rMinSizeDelta,rMaxSizeDelta);
    p.r = rEngine->Rand(rMinRed,rMaxRed);
    p.g = rEngine->Rand(rMinGreen,rMaxGreen);
    p.b = rEngine->Rand(rMinBlue,rMaxBlue);
    p.a = rEngine->Rand(rMinAlpha,rMaxAlpha);

    return p;
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::UpdateParticle(int index, float elapsedTime)
{
    rParticles[index].xPrev = rParticles[index].xPos;
    rParticles[index].yPrev = rParticles[index].yPos;
    rParticles[index].xPos += rParticles[index].xVel*elapsedTime;
    rParticles[index].yPos += rParticles[index].yVel*elapsedTime;
    rParticles[index].size += rParticles[index].sizeDelta*elapsedTime;
    rParticles[index].energy += rParticles[index].energyDelta*elapsedTime;
    if(rParticles[index].size <= 0)
        rParticles[index].energy = 0;
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::Render()
{
    switch(rStyle)
    {
        case DS_POINT:
            glBindTexture(GL_TEXTURE_2D,0);
            for(unsigned int i=0; i < rCurParticles; i++)
            {
                glPointSize(rParticles[i].size);
                glBegin(GL_POINTS);
                glColor4ub(rParticles[i].r,rParticles[i].g,rParticles[i].b,rParticles[i].a);
                glVertex2f(rParticles[i].xPos,rParticles[i].yPos);
                glEnd();
            }            
            break;
        case DS_LINE:
            glBindTexture(GL_TEXTURE_2D,0);
            for(unsigned int i=0; i < rCurParticles; i++)
            {
                glLineWidth(rParticles[i].size);
                glBegin(GL_LINES);
                glColor4ub(rParticles[i].r,rParticles[i].g,rParticles[i].b,rParticles[i].a);
                glVertex2f(rParticles[i].xPos,rParticles[i].yPos);
                glVertex2f(rParticles[i].xPrev,rParticles[i].yPrev);
                glEnd();
            }
            break;
        case DS_IMAGE:
            float x,y,size;
            rImage.Bind();
            glBegin(GL_QUADS);
            for(unsigned int i=0; i < rCurParticles; i++)
            {
                x = rParticles[i].xPos;
                y = rParticles[i].yPos;
                size = rParticles[i].size;

                glColor4ub(rParticles[i].r,rParticles[i].g,rParticles[i].b,rParticles[i].a);
                glTexCoord2f(0,1);  glVertex2f(x,y);
                glTexCoord2f(1,1);  glVertex2f(x+size,y);
                glTexCoord2f(0,1);  glVertex2f(x+size,y-size);
                glTexCoord2f(0,0);  glVertex2f(x,y-size);
            }
            glEnd();
            break;
    }
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::ReloadImage()
{
    if(rStyle == DS_IMAGE)
        rImage.Reload();
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::SetDrawStyle(ParticleDrawStyle style)
{
    rStyle = style;
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::SetImage(std::string filename)
{
    rImage.Open(filename);
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::SetPosRange(float minX, float minY, float maxX, float maxY)
{
    rMinX = minX;
    rMaxX = maxX;
    rMinY = minY;
    rMaxY = maxY;
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::SetVelocityRange(float minXVel, float minYVel, float maxXVel, float maxYVel)
{
    rMinXVel = minXVel;
    rMaxXVel = maxXVel;
    rMinYVel = minYVel;
    rMaxYVel = maxYVel;
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::SetEnergyRange(float minEnergy, float maxEnergy, float minEnergyDelta, float maxEnergyDelta)
{
    rMinEnergy = minEnergy;
    rMaxEnergy = maxEnergy;
    rMinEnergyDelta = minEnergyDelta;
    rMaxEnergyDelta = maxEnergyDelta;
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::SetSizeRange(float minSize, float maxSize, float minSizeDelta, float maxSizeDelta)
{
    rMinSize = minSize;
    rMaxSize = maxSize;
    rMinSizeDelta = minSizeDelta;
    rMaxSizeDelta = maxSizeDelta;
}

template <class particleType>
void ZSimpleParticleSystem<particleType>::SetColorRange(Uint8 minRed, Uint8 maxRed, Uint8 minGreen, Uint8 maxGreen, 
                            Uint8 minBlue, Uint8 maxBlue, Uint8 minAlpha, Uint8 maxAlpha)
{
    rMinRed = minRed;
    rMaxRed = maxRed;
    rMinGreen = minGreen;
    rMaxGreen = maxGreen;
    rMinBlue = minBlue;
    rMaxBlue = maxBlue;
    rMinAlpha = minAlpha;
    rMaxAlpha = maxAlpha;
}

}   //namespace ZE

#endif //__ze_zsimpleparticlesystem_h__
