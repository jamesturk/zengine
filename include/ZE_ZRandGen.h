/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zrandgen_h__
#define __ze_zrandgen_h__

#include "ZE_Utility.h"

namespace ZE
{

class ZRandGen
{
    protected:
        static const unsigned long N = 624;
        static const unsigned long M = 397;
        static const unsigned long MATRIX_A = 0x9908b0dfUL;
        static const unsigned long UPPER_MASK = 0x80000000UL;
        static const unsigned long LOWER_MASK = 0x7fffffffUL;

        unsigned long rStateVector[N];
        unsigned long rStateVectorIndex;

        unsigned long genrand_int32();

    public:
        ZRandGen();
        ZRandGen(unsigned long seed);

        void Seed(unsigned long seed);

        unsigned int Rand(unsigned int max);
        unsigned long Rand(unsigned long max);
        int Rand(int min, int max);
        long Rand(long min, long max);
        float Rand(float min, float max);
        double Rand(double min, double max);
        double RandDouble();
};

}

#endif //__ze_zrandgen_h__

