/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zsimpleparticlesystem_h__
#define __ze_zsimpleparticlesystem_h__

#include "ZEngine.h"

namespace ZE
{

class ZSimpleParticle : public ZBaseParticle
{
    public:
        float xPrev;
        float yPrev;
        float xVel;
        float yVel;
        float energyDelta;
        float size;
        float sizeDelta;
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
};

enum ParticleDrawStyle 
{ 
    DS_POINT,
    DS_LINE,
    DS_IMAGE
};

template <class particleType>
class ZSimpleParticleSystem : public ZBaseParticleSystem<particleType>
{
    protected:
        ParticleDrawStyle rStyle;
        ZImage rImage;
        float rMinX;
        float rMaxX;
        float rMinY;
        float rMaxY;
        float rMinXVel;
        float rMaxXVel;
        float rMinYVel;
        float rMaxYVel;
        float rMinEnergy;
        float rMaxEnergy;
        float rMinEnergyDelta;
        float rMaxEnergyDelta;
        float rMinSize;
        float rMaxSize;
        float rMinSizeDelta;
        float rMaxSizeDelta;
        Uint8 rMinRed;
        Uint8 rMaxRed;
        Uint8 rMinGreen;
        Uint8 rMaxGreen;
        Uint8 rMinBlue;
        Uint8 rMaxBlue;
        Uint8 rMinAlpha;
        Uint8 rMaxAlpha;
      
        virtual particleType NewParticle();
        virtual void UpdateParticle(int index, float elapsedTime);

    public:
        virtual void Render();

        void ReloadImage();

        void SetDrawStyle(ParticleDrawStyle style);
        void SetImage(std::string filename);
        void SetPosRange(float minX, float minY, float maxX, float maxY);
        void SetVelocityRange(float minXVel, float minYVel, float maxXVel, float maxYVel);
        void SetEnergyRange(float minEnergy, float maxEnergy, float minEnergyDelta=0, float maxEnergyDelta=0);
        void SetSizeRange(float minSize, float maxSize, float minSizeDelta=0, float maxSizeDelta=0);
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

#if (GFX_BACKEND == ZE_OGL)

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

#elif (GFX_BACKEND == ZE_SDL)

template <class particleType>
void ZSimpleParticleSystem<particleType>::Render()
{
    switch(rStyle)
    {
        case DS_POINT:
            for(unsigned int i=0; i < rCurParticles; i++)
            {
                //draw point
            }            
            break;
        case DS_LINE:
            for(unsigned int i=0; i < rCurParticles; i++)
            {
                //draw line 
            }
            break;
        case DS_IMAGE:
            for(unsigned int i=0; i < rCurParticles; i++)
            {
                //draw image
            }
            break;
    }
}

#endif //GFX_BACKEND

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
