/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zbaseparticlesystem_h__
#define __ze_zbaseparticlesystem_h__

#include "ZEngine.h"

namespace ZE
{

class ZBaseParticle
{
    public:      
        virtual ~ZBaseParticle() 
        {}  // empty definition here, since ZBaseParticleSystem has no cpp file and this would be all that would be in it

        float xPos;
        float yPos;
        float energy;
};

template <class particleType>
class ZBaseParticleSystem
{
    protected:
        ZEngine *rEngine;
        particleType *rParticles;
        unsigned int rMaxParticles;
        unsigned int rCurParticles;
        unsigned int rNumParticlesPerSec;
        Uint32 rLastUpdate;
        bool rPaused;

        void AddParticle();
        virtual particleType NewParticle()=0;
        virtual void UpdateParticle(int index, float elapsedTime)=0;

    public:
        ZBaseParticleSystem();
        virtual ~ZBaseParticleSystem();

        virtual void Render()=0;
        void Emit(int numParticles);       
        virtual void Update();

        void Clear();
        void Pause();
        void Unpause();
        void Stop();

        void SetMaxParticles(unsigned int max);     
        void SetRate(unsigned int rate);

        bool IsPaused();
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
    rPaused = false;
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

    if(!rPaused)
    {
        //update every particle and remove dead particles
        for(unsigned int i=0; i < rCurParticles; ++i)
        {
            UpdateParticle(i,elapsed);
            if(rParticles[i].xPos < 0 || rParticles[i].xPos > rEngine->DisplayWidth() 
                || rParticles[i].yPos < 0 || rParticles[i].yPos > rEngine->DisplayHeight() || rParticles[i].energy <= 0)
            {
                rParticles[i] = rParticles[--rCurParticles];
                --i;    //go back one to process that particle
            }
        }

        emitAmount = elapsed*rNumParticlesPerSec;
        overflow += emitAmount - static_cast<int>(emitAmount); //only floating point portion of emitAmount
        Emit(static_cast<int>(emitAmount));
        if(overflow >= .95) //a little lower than one, for tolerance
        {
            Emit(1);
            overflow = 0;   //dump & clear overflow
        }
    }

    rLastUpdate = rEngine->GetTime();
}


template <class particleType>
void ZBaseParticleSystem<particleType>::Clear()
{
    rCurParticles = 0;
}

template <class particleType>
void ZBaseParticleSystem<particleType>::Pause()
{
    rPaused = true;
}

template <class particleType>
void ZBaseParticleSystem<particleType>::Unpause()
{
    rPaused = false;
}

template <class particleType>
void ZBaseParticleSystem<particleType>::Stop()
{
    Clear();
    Pause();
}

template <class particleType>
bool ZBaseParticleSystem<particleType>::IsPaused()
{
    return rPaused;
}

template <class particleType>
void ZBaseParticleSystem<particleType>::SetMaxParticles(unsigned int max)
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
void ZBaseParticleSystem<particleType>::SetRate(unsigned int rate)
{
    rNumParticlesPerSec = rate;
}

}   //namespace ZE

#endif //__ze_zbaseparticlesystem_h__
