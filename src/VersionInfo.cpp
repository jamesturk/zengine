#include "VersionInfo.h"

/*!
    \file VersionInfo.cpp
    \brief Implementation file for VersionInfo class.

    Implementation file for VersinInfo class, simple class for containing and comparing 
    version numbers.
    <br>$Id: VersionInfo.cpp,v 1.4 2003/06/11 05:51:15 cozman Exp $<br>
    \author James Turk
**/

VersionInfo::VersionInfo(unsigned int maj, unsigned int min, unsigned int rel, std::string ext) :
    major(maj), minor(min), release(rel), extra(ext)
{
}


std::string VersionInfo::GetString() const
{
    if(extra.length())
        return ZE::FormatStr("%d.%d.%d [%s]",major,minor,release,extra.c_str());
    else
        return ZE::FormatStr("%d.%d.%d",major,minor,release);
}

bool VersionInfo::operator<(const VersionInfo &rhs) const
{
    //chained compares, compare numbers in order of importance
    if(this->major < rhs.major)
        return true;
    else if(this->major == rhs.major)
    {
        if(this->minor < rhs.minor)
            return true;
        else if(this->minor == rhs.minor)
        {
            if(this->release < rhs.release)
                return true;
            else if(this->release == rhs.release)
            {
                return this->extra < rhs.extra; //just compare the strings at the end
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
