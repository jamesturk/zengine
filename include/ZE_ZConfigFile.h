/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

/*!
\par File Header: 
File: Types/ZE_ZConfigFile.h <br>
Description: Header file for ZEngine INI-Style Config Files.<br>
Author(s): James Turk <br>
$Id: ZE_ZConfigFile.h,v 1.2 2002/12/01 07:56:17 cozman Exp $<br>

    \file ZE_ZConfigFile.h
    \brief Definition file for ZConfigFile.

    Definition file for ZConfigFile, an INI-style Config format.
**/


#ifndef __ze_zconfigfile_h__
#define __ze_zconfigfile_h__

#include "ZE_ZObject.h"        //included even though ZCF isn't derived (to obtain all other needed headers)

namespace ZE
{

/*!
    \brief ZConfigFile Class for use in ZEngine.

    ZConfigFile class for INI-style configuration files for games or applications.  Inherited from ZObject.
**/
class ZConfigFile : public ZObject
{
    private:

        //Private Types//


        /*!
            \brief ZConfigFile Variable class.
            
            ZConfigFile class for mapping a variable name to it's value, stored in string form (later converted to 
            bool or int if needed).
        **/
        class ZCF_Variable
        {
            public:
                //! Variable name.
                string var;
                //! Value associated with variable.
                string val;
        };

        /*!
            \brief ZConfigFile Section class.

            ZConfigFile class for mapping a section name to a list of variables in that section.
        **/
        class ZCF_Section
        {
            public:
                //! Section name.
                string section;
                //! STL list of variables.
                list<ZCF_Variable> varList;
        };

        //! List of sections of internal type.
        list<ZCF_Section> mFileLayout;

        //! Filename of file currently open.
        string mFilename;

        /*!
            \brief Reformat a string in a form more suitable to parsing.

            Removes whitespace from a string and makes all characters lowercase.
            \param str The string to get a clean version of.
            \return Cleaned string.
        **/
        string CleanString(string str);
        
        bool Exists(string sec);
        bool Exists(string sec, string var);
        void SetVariable(string sec, string var, string val);
        string GetVariable(string sec, string var, string defVal);

    public:

        /*!
            \brief Default constructor.

            A no-op default constructor.
        **/
        ZConfigFile();

        /*!
            \brief Constructor which takes filename.

            Constructor takes filename, and calls process on it.
            \param filename File to load as ZConfigFile.
        **/
        ZConfigFile(string filename);

        /*!
            \brief Destructor, flushes file.

            Flushes the file, ensures a flush if the file is left open.
        **/
        ~ZConfigFile();

        /*!
            \brief Parse a file.
            
            Parses the file, reading the contents into the fileLayout map.
            \param filename File to parse and attach this ZDataFile to.
        **/
        void Process(string filename);

        /*!
            \brief Get value in integer format from file.

            Get the current value of a variable in the file, or defVal if not found in file.
            \param section Name of section to seek variable under.
            \param var Name of variable to seek value for.
            \param defVal Value to return if var does not exist within section.
            \return Contents of the variable in integer format.
        **/
        int GetInt(string section, string var, int defVal);

        /*!
            \brief Get value in boolean format from file.

            Get the current value of a variable in the file, or defVal if not found in file. 
            (Valid values are "0","1","true" and "false")
            \param section Name of section to seek variable under.
            \param var Name of variable to seek value for.
            \param defVal Value to return if var does not exist within section.
            \return Contents of the variable in boolean format.
        **/
        bool GetBool(string section, string var, bool defVal);

        /*!
            \brief Get value in string format from file.

            Get the current value of a variable in the file, or defVal if not found in file. 
            \param section Name of section to seek variable under.
            \param var Name of variable to seek value for.
            \param defVal Value to return if var does not exist within section.
            \return Contents of the variable in string format.
        **/
        string GetString(string section, string var, string defVal);

        /*!
            \brief Set value in integer format in file.

            Set the new value of a variable in the file to val, creating the section and variable 
            if not already found in file. 
            \param section Name of section to edit variable under.
            \param var Name of variable to set value for.
            \param val Integer value to set variable to in file.
        **/
        void SetInt(string section, string var, int val);

        /*!
            \brief Set value in boolean format in file.

            Set the new value of a variable in the file to val, creating the section and variable 
            if not already found in file.
            \param section Name of section to edit variable under.
            \param var Name of variable to set value for.
            \param val Boolean value to set variable to in file.
        **/
        void SetBool(string section, string var, bool val);

        /*!
            \brief Set value in string format in file.

            Set the new value of a variable in the file to val, creating the section and variable 
            if not already found in file.
            \param section Name of section to edit variable under.
            \param var Name of variable to set value for.
            \param val String value to set variable to in file.
        **/
        void SetString(string section, string var, string val);
        
        /*!
            \brief Write all values to file

            Writes all values and sections to file.
        **/
        void Flush();

        /*!
            \brief Close the file.

            Flush the file and clear the filename.
        **/
        void Close();
};

}

#endif //__ze_zconfigfile_h__
