/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZObject.h <br>
Description: Header file for ZEngine core Object ZObject, base of most ZEngine objects. <br>
Author(s): James Turk <br>
$Id: ZE_ZObject.h,v 1.1 2002/11/21 05:41:11 cozman Exp $<br>

    \file ZE_ZObject.h
    \brief Definition file for ZObject Base Class.

    Definition file for ZObject the Virtual Base Class for majority of the ZEngine Objects.
**/

#ifndef __ze_zobject_h__
#define __ze_zobject_h__

#include "ZE_ZEngine.h"

namespace ZE
{
/*!
    \brief ZObject base class for other ZEngine objects.

    This is the base class from which all ZEngine internal objects are derived from.
**/
class ZObject
{
    protected:
        //! Pointer to ZEngine Object
        ZEngine* rEngine;
    public:
        /*!
            \brief ZEngine Constructor.

            ZEngine Constructor, gets Engine pointer for Object.
        **/
        ZObject() { rEngine = ZEngine::GetInstance(); };

        /*!
            \brief ZEngine Virtual destructor.

            ZEngine destructor, provided to make class safely inheritable.
        **/
        virtual ~ZObject() {};
};
}

#endif //__ze_zobject_h__
