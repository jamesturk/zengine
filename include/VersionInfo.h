/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __versioninfo_h__
#define __versioninfo_h__

#include "ZE_Utility.h"


class VersionInfo
{
    public:
        unsigned int Major;
        unsigned int Minor;
        unsigned int Release;
        std::string Extra;

        VersionInfo(unsigned int maj, unsigned int min, unsigned int rel, std::string ext="");
        char* GetString() const;
        bool operator<(const VersionInfo &rhs) const;
        bool operator==(const VersionInfo &rhs) const;
        bool operator>(const VersionInfo &rhs) const;
};

#endif //__versioninfo_h__
