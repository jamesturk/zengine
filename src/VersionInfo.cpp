#include "VersionInfo.h"

/*!
    \file VersionInfo.cpp
    \brief Implementation file for VersionInfo class.

    Implementation file for VersinInfo class, simple class for containing and comparing 
    version numbers.
    <br>$Id: VersionInfo.cpp,v 1.5 2003/07/12 01:25:42 cozman Exp $<br>
    \author James Turk
**/

VersionInfo::VersionInfo(unsigned int maj, unsigned int min, unsigned int rel, std::string ext) :
    Major(maj), Minor(min), Release(rel), Extra(ext)
{
}


std::string VersionInfo::GetString() const
{
    if(Extra.length())
        return ZE::FormatStr("%d.%d.%d [%s]",Major,Minor,Release,Extra.c_str());
    else
        return ZE::FormatStr("%d.%d.%d",Major,Minor,Release);
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
