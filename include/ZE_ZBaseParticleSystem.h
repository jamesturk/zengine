/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZBaseParticleSystem.h
    \brief Definition and implementation file for the base of the ZEngine Particle System.

    Definition and implementation file for ZEngine particle system class ZBaseParticleSystem.
    Due to problems with template classes the template implementation needs to be in the same file as the declaration.
    <br>$Id: ZE_ZBaseParticleSystem.h,v 1.2 2003/07/10 19:20:56 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zbaseparticlesystem_h__
#define __ze_zbaseparticlesystem_h__

#include "ZEngine.h"

namespace ZE
{

/*!
    \brief Basic particle class for ZEngine particle systems.

    Basic particle class, all particles used should derive from this class so that needed members are available.
    (No default constructor is needed because NewParticle should initialize members.)
**/
class ZBaseParticle
{
    public:
        /*!
            \brief Virtual destructor.

            Empty virtual destructor to make inheritance safe.
        **/
        virtual ~ZBaseParticle() 
        {}  // empty definition here, since ZBaseParticleSystem has no cpp file and this would be all that would be in it

        //! X Position of particle.
        float xPos;
        //! Y Position of particle.
        float yPos;
        //! Energy of particle (particles die if energy is 0).
        float energy;
};

/*!
    \brief Base particle system, a virtual class defining an outline for a fully functional particle system.

    Virtual class providing outline of basic particle system, designed so that a working particle system can be
    derived with minimal waste.  Uses templated system to allow particle systems to work with their own types of 
    particles, the particleType template parameter must be a type that has the members of ZBaseParticle.
    (Note: If you need a very specific particle system it's probably best to write your own fit to your needs.)
**/
template <class particleType>
class ZBaseParticleSystem
{
    protected:
        //! Pointer to ZEngine singleton.
        ZEngine *rEngine;
        //! Pointer to array of particles.
        particleType *rParticles;
        //! Maximum number of particles, and size of rParticles array.
        unsigned int rMaxParticles;
        //! Current number of particles.
        unsigned int rCurParticles;
        //! Number of particles to release per second.
        unsigned int rNumParticlesPerSec;
        //! Millisecond format time of last update.
        Uint32 rLastUpdate;

        /*!
            \brief Adds a new particle.

            Finds room in array with dead particle, and adds new particle using NewParticle, called by Emit.
        **/
        void AddParticle();

        /*!
            \brief Pure virtual function to initialize and return a new particle.

            Pure virtual function, overload should set up a new particle with desired traits, called by AddParticle.
        **/
        virtual particleType NewParticle()=0;

        /*!
            \brief Pure virtual function to update a particle.

            Pure virtual function, overload should update the particle `rParticles[index]`, called by Update.
            \param index Index of particle in rParticles array to update.
            \param elapsedTime Decimal portion of a second since last call.
        **/
        virtual void UpdateParticle(int index, float elapsedTime)=0;

    public:
        /*!
            \brief Basic constructor for ZBaseParticleSystem.

            Basic constructor for ZBaseParticle system, initializes all values to 0.
        **/
        ZBaseParticleSystem();

        /*!
            \brief Virtual destructor for ZBaseParticleSystem.

            Virtual destructor for ZBaseParticleSystem, destroys all particles, virtual to make class inheritance-safe.
        **/
        virtual ~ZBaseParticleSystem();

        /*!
            \brief Pure virtual function, renders the particles.
            
            Pure virtual so that each particle system can render it's member particles in it's own way.
        **/
        virtual void Render()=0;

        /*!
            \brief Emit a given number of particles.

            Emits a given number of particles, will not emit particles if system is full.
            \param numParticles Number of particles to emit.
        **/
        void Emit(int numParticles);

        /*!
            \brief Updates status of particle system.
            
            Updates entire particle system, calling update on every particle, emitting necessary new
            particles, removing particles which have an energy <= 0 or are off the screen.
        **/
        void Update();
                
        /*!
            \brief Sets max particles allowed in system.

            Set maximum number of particles allowed in system, particles are not emitted when system is full.
            When this resizes the array contents are moved to the new array, if it shrinks the array particles may be lost.
            \param max Maximum number of particles for system.
        **/
        void SetMaxParticles(int max);

        /*!
            \brief Sets release rate of particles.

            Set number of particles to release per second.
            \param rate Number of particles to release over the duration of one second.
        **/
        void SetRate(int rate);    
};

//implementation//

template <class particleType>
void ZBaseParticleSystem<particleType>::AddParticle()
{
    //empty space is always at end, function is private so no checking is needed (Emit does that)
    rParticles[rCurParticles] = NewParticle();  
    ++rCurParticles;
}

template <class particleType>
ZBaseParticleSystem<particleType>::ZBaseParticleSystem()
{
    rEngine = ZEngine::GetInstance();
    rParticles = NULL;
    rMaxParticles = rCurParticles = rNumParticlesPerSec = 0;
    rLastUpdate = rEngine->GetTime();
}

template <class particleType>
ZBaseParticleSystem<particleType>::~ZBaseParticleSystem()
{
    if(rParticles)
        delete []rParticles;
}

template <class particleType>
void ZBaseParticleSystem<particleType>::Emit(int numParticles)
{
    while(numParticles > 0 && rCurParticles < rMaxParticles)
    {
        AddParticle();
        --numParticles;
    }
}

template <class particleType>
void ZBaseParticleSystem<particleType>::Update()
{
    float elapsed = (rEngine->GetTime()-rLastUpdate)/1000.0f;
    double emitAmount;
    static double overflow=0;

    //update every particle and remove dead particles
    for(unsigned int i=0; i < rCurParticles; ++i)
    {
        UpdateParticle(i,elapsed);
        if(rParticles[i].xPos < 0 || rParticles[i].xPos > rEngine->Width() 
            || rParticles[i].yPos < 0 || rParticles[i].yPos > rEngine->Height() || rParticles[i].energy <= 0)
        {
            rParticles[i] = rParticles[--rCurParticles];
            --i;    //go back one to process that particle
        }
    }

    rLastUpdate = rEngine->GetTime();

    emitAmount = elapsed*rNumParticlesPerSec;
    overflow += emitAmount - static_cast<int>(emitAmount); //only floating point portion of emitAmount
    Emit(static_cast<int>(emitAmount));
    if(overflow >= .95) //a little lower than one, for tolerance
    {
        Emit(1);
        overflow = 0;   //dump & clear overflow
    }
}

template <class particleType>
void ZBaseParticleSystem<particleType>::SetMaxParticles(int max)
{
    particleType *temp;
    unsigned int i;

    if(max)
    {
        if(max != rMaxParticles)    //only do this if size changed
        {
            if(rCurParticles)
            {
                rCurParticles %= max;
                //copy current particles to temp
                temp = new particleType[rCurParticles];
                for(i=0; i < rCurParticles; ++i)
                    temp[i] = rParticles[i];
            }

            //change size of rParticles
            if(rParticles)
                delete []rParticles; 
            rParticles = new particleType[max];
            rMaxParticles = max;

            if(rCurParticles)
            {
                //copy particles from temp back to rParticles
                for(i=0; i < rCurParticles; ++i)
                    rParticles[i] = temp[i];

                delete []temp;
            }
        }
    }
    else
    {
        rMaxParticles = rCurParticles = 0;
        if(rParticles)
            delete []rParticles;
    }
}

template <class particleType>
void ZBaseParticleSystem<particleType>::SetRate(int rate)
{
    rNumParticlesPerSec = rate;
}

}   //namespace ZE

#endif //__ze_zbaseparticlesystem_h__
