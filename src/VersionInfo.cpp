/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "VersionInfo.h"

VersionInfo::VersionInfo(unsigned int maj, unsigned int min, unsigned int rel, std::string ext) :
    Major(maj), Minor(min), Release(rel), Extra(ext)
{
}

char* VersionInfo::GetString() const
{
    static char verStr[100];

    if(Extra.length())
        sprintf(verStr,"%d.%d.%d [%s]",Major,Minor,Release,Extra.c_str());
    else
        sprintf(verStr,"%d.%d.%d",Major,Minor,Release);

    return verStr;
}

bool VersionInfo::operator<(const VersionInfo &rhs) const
{
    //chained compares, compare numbers in order of importance
    if(this->Major < rhs.Major)
        return true;
    else if(this->Major == rhs.Major)
    {
        if(this->Minor < rhs.Minor)
            return true;
        else if(this->Minor == rhs.Minor)
        {
            if(this->Release < rhs.Release)
                return true;
            else if(this->Release == rhs.Release)
            {
                return this->Extra < rhs.Extra; //just compare the strings at the end
            }
        }
    }
    return false;   //if it reaches this point rhs is >=
}

bool VersionInfo::operator==(const VersionInfo &rhs) const
{
    return this->GetString() == rhs.GetString();    //only equal data produces equal strings
}

bool VersionInfo::operator>(const VersionInfo &rhs) const
{
    return !((*this) < rhs || (*this) == rhs);  //if not < and not ==, must be >
}
