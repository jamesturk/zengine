/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZRandGen.cpp
    \brief Source file for ZRandGen.

    Implementation file for ZRandGen, an OO encapsulated version of the Mersenne Twister.
    This implementation is derived from the original mt19937ar.c source from
    http://www.math.keio.ac.jp/matumoto/emt.html. See source for MT license.
    <br>$Id: ZE_ZRandGen.cpp,v 1.1 2003/07/05 00:58:08 cozman Exp $<br>
    \author James Turk, some code from Mersenne Twister.
**/

#include "ZE_ZRandGen.h"

namespace ZE
{

/*
    The source in this file is based on MT19937, with much of the source
    replicated from mt19937ar.c, because of this the original license
    for that file is below.
                            -James

 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.keio.ac.jp/matumoto/emt.html
   email: matumoto@math.keio.ac.jp
*/

//adapted directly from mt19937ar : unsigned long genrand_int32(void)
unsigned long ZRandGen::genrand_int32()
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (rStateVectorIndex >= N) { /* generate N words at one time */
        int kk;

        //removed uninitialized check, class initializes in constructor

        for (kk=0;kk<N-M;++kk) {
            y = (rStateVector[kk]&UPPER_MASK)|(rStateVector[kk+1]&LOWER_MASK);
            rStateVector[kk] = rStateVector[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;++kk) {
            y = (rStateVector[kk]&UPPER_MASK)|(rStateVector[kk+1]&LOWER_MASK);
            rStateVector[kk] = rStateVector[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (rStateVector[N-1]&UPPER_MASK)|(rStateVector[0]&LOWER_MASK);
        rStateVector[N-1] = rStateVector[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        rStateVectorIndex = 0;
    }
  
    y = rStateVector[rStateVectorIndex++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

ZRandGen::ZRandGen()
{
    Seed(static_cast<unsigned long>(std::time(NULL)));
}

ZRandGen::ZRandGen(unsigned long seed)
{
    Seed(seed);
}

//adapted directly from mt19937ar : void init_genrand(unsigned long s)
void ZRandGen::Seed(unsigned long s)
{
    rStateVector[0]= s & 0xffffffffUL;
    for(rStateVectorIndex=1; rStateVectorIndex<N; ++rStateVectorIndex) 
    {
        rStateVector[rStateVectorIndex] = 
	    (1812433253UL * (rStateVector[rStateVectorIndex-1] ^ (rStateVector[rStateVectorIndex-1] >> 30)) + rStateVectorIndex); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array rStateVector[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        rStateVector[rStateVectorIndex] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

unsigned int ZRandGen::Rand(unsigned int max)
{
    return genrand_int32()%max;
}

unsigned long ZRandGen::Rand(unsigned long max)
{
    return genrand_int32()%max;
}

int ZRandGen::Rand(int min, int max)
{
    return min + genrand_int32()%(max-min+1);
}

long ZRandGen::Rand(long min, long max)
{
    return min + genrand_int32()%(max-min+1);
}

//partly adapted from mt19937ar : double genrand_real1(void)
float ZRandGen::Rand(float min, float max)
{
    return min + ((genrand_int32()*(1.0f/4294967295.0f))*(max-min));
}

//partly adapted from mt19937ar : double genrand_real1(void)
double ZRandGen::Rand(double min, double max)
{
    return min + ((genrand_int32()*(1.0/4294967295.0))*(max-min));
}

//adapted directly from mt19937ar : double genrand_real2(void)
double ZRandGen::RandDouble()
{
    return genrand_int32()*(1.0/4294967296.0); 
}

}
