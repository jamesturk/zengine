#include "VersionInfo.h"

/*!
    \file VersionInfo.cpp
    \brief Implementation file for VersionInfo class.

    Implementation file for VersinInfo class, simple class for containing and comparing 
    version numbers.
    <br>$Id: VersionInfo.cpp,v 1.2 2003/06/10 23:24:47 cozman Exp $<br>
    \author James Turk
**/

VersionInfo::VersionInfo(unsigned int maj, unsigned int min, unsigned int rel, string ext) :
    major(maj), minor(min), release(rel), extra(ext)
{
}


string VersionInfo::GetString() const
{
    if(extra.length())
        return ZE::FormatStr("%d.%d.%d [%s]",major,minor,release,extra.c_str());
    else
        return ZE::FormatStr("%d.%d.%d",major,minor,release);
}

bool VersionInfo::operator<(const VersionInfo &rhs) const
{
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
                if(this->extra.length() == 0 && rhs.extra.length() != 0)
                    return true;
                else if(this->extra.length() && rhs.extra.length())
                {
                    return this->extra[0] < rhs.extra[0];
                }
            }
        }
    }
    return false;
}

bool VersionInfo::operator==(const VersionInfo &rhs) const
{
    return this->GetString() == rhs.GetString();
}

bool VersionInfo::operator>(const VersionInfo &rhs) const
{
    return !((*this) < rhs || (*this) == rhs);
}
