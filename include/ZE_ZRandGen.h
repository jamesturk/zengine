/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZRandGen.h
    \brief Definition file for ZRandGen.

    Definition file for ZRandGen, an OO encapsulated version of the Mersenne Twister.
    This class usually isn't needed by the average user, ZEngine contains an instance which 
    should suffice unless you want objects to have their ownrandom streams.  This 
    implementation is derived from the original mt19937ar.c source from
    http://www.math.keio.ac.jp/matumoto/emt.html. See source of ZE_ZRandGen.cpp for license.
    <br>$Id: ZE_ZRandGen.h,v 1.1 2003/07/05 01:05:47 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zrandgen_h__
#define __ze_zrandgen_h__

#include "ZE_Utility.h"
#include <ctime>

namespace ZE
{

/*!
    \brief ZRandGen class for OO encapsulation of superb random generator "Mersenne Twister."

    This class usually isn't needed by the average user, ZEngine contains an instance which 
    should suffice unless you want objects to have their ownrandom streams.  This 
    implementation is derived from the original mt19937ar.c source from
    http://www.math.keio.ac.jp/matumoto/emt.html. See source of ZE_ZRandGen.cpp for license.
    \since 0.8.4
**/
class ZRandGen
{
    protected:
        //! Number of random numbers to generate at once.
        static const unsigned long N = 624;
        //! A constant used internally by Mersenne Twister.
        static const unsigned long M = 397;
        //! Constant vector A, used internally by Mersenne Twister.
        static const unsigned long MATRIX_A = 0x9908b0dfUL;
        //! Most signifigan w-r bits, used internally by Mersenne Twister.
        static const unsigned long UPPER_MASK = 0x80000000UL;
        //! Least signifigant r bits, used internally by Mersenne Twister.
        static const unsigned long LOWER_MASK = 0x7fffffffUL;

        //! Each instance of the algorithm requires a state vector.
        unsigned long rStateVector[N];
        //! Used internally to traversing the rStateVector.
        int rStateVectorIndex;

        /*!
            \brief Workhorse of random generator, only used internally.

            Generates N random numbers and then serves them up, all Rand functions rely
            on this.
            \return A random unsigned long.
        **/
        unsigned long genrand_int32();

    public:
        /*!
            \brief Constructor which does an initial seeding using time.

            Creates internal vector and calls Seed(time(NULL)) to initialize the MT state.
        **/
        ZRandGen();

        /*!
            \brief Constructor which does an initial seeding.

            Creates internal vector and calls seed to initialize the MT state.
        **/
        ZRandGen(unsigned long seed);

        /*!
            \brief Seed random number generator. 

            Reseed Mersenne Twister random number generator.  NOTE: Generator is initialized upon creation of object using time.
            \param seed Seed for random sequence.
        **/
        void Seed(unsigned long seed);

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
};

}

#endif //__ze_zrandgen_h__