/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file VersionInfo.h
    \brief Definition file for VersionInfo class.

    Definition file for VersinInfo class, simple class for containing and comparing 
    version numbers.
    <br>$Id: VersionInfo.h,v 1.1 2003/06/10 23:15:31 cozman Exp $<br>
    \author James Turk
**/

#ifndef __versioninfo_h__
#define __versioninfo_h__

#include "ZE_Utility.h"

/*!
    \brief Class for holding version information.

    Class for holding version information on a library.
**/
class VersionInfo
{
    public:
        //! Major version number.
        unsigned int major;
        //! Minor version number, changes upon signifigant releases. (Often upon compatibility breaks.)
        unsigned int minor;
        //! Version release number, changes on every release.
        unsigned int release;
        //! String Description of release. (Often blank.)
        string extra;

        /*!
            \brief Get string representing version number.

            Get dotted version number major.minor.release [extra].
            \return Formatted version string.
        **/
        string GetString() const;

        /*!
            \brief Less than operator overload for comparing VersionInfo.

            Overload of the less than (<) operator for two VersionInfos.
            \param rhs Right hand side of comparison.
            \return true if less than, false if greater than or equal to.
        **/
        bool operator<(const VersionInfo &rhs) const;

        /*!
            \brief Equals to operator overload for comparing VersionInfo.

            Overload of the equals to (==) operator for two VersionInfos.
            \param rhs Right hand side of comparison.
            \return true if equal to, false if not equals to.
        **/
        bool operator==(const VersionInfo &rhs) const;

        /*!
            \brief Greater than operator overload for comparing VersionInfo.

            Overload of the greater than (>) operator for two VersionInfos.
            \param rhs Right hand side of comparison.
            \return true if greater than, false if less than or equal to.
        **/
        bool operator>(const VersionInfo &rhs) const;
};

#endif //__versioninfo_h__
