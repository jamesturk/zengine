/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZConfigFile.h
    \brief Definition file for ZConfigFile.
    
    Definition file for ZConfigFile, an INI-style config file format.<br>
    $ id: ZE_ZConfigFile.h,v 1.9 2003/02/10 04:40:16 cozman Exp $
    \author James Turk
**/


#ifndef __ze_zconfigfile_h__
#define __ze_zconfigfile_h__

#include "ZE_ZEngine.h"

namespace ZE
{

/*!
    \brief ZConfigFile Class for use in ZEngine.

    ZConfigFile class for INI-style configuration files for games or applications.  Inherited from ZObject.
**/
class ZConfigFile
{
    private:

        //Private Types//

        /*!
            \brief ZConfigFile Variable class.
            
            ZConfigFile class for mapping a variable name to it's value, stored in std::string form (later converted to 
            bool or int if needed).
        **/
        class ZCF_Variable
        {
            public:
                //! Variable name.
                std::string var;
                //! Value associated with variable.
                std::string val;
        };

        /*!
            \brief ZConfigFile Section class.

            ZConfigFile class for mapping a section name to a list of variables in that section.
        **/
        class ZCF_Section
        {
            public:
                //! Section name.
                std::string section;
                //! STL list of variables.
                std::list<ZCF_Variable> varList;
        };

    protected:
        //! List of sections of internal type.
        std::list<ZCF_Section> rFileLayout;
        //! Filename of file currently open.
        std::string rFilename;

        /*!
            \brief Reformat a std::string in a form more suitable to parsing.

            Removes whitespace from a std::string and makes all characters lowercase.
            \param str The std::string to get a clean version of.
            \return Cleaned std::string.
        **/
        std::string CleanString(std::string str)  const;
        
        /*!
            \brief Check if a section exists.

            Find out if a section currently exists.
            \param sec Section to check for.
            \return bool, true if section exists in file.
        **/
        bool Exists(std::string sec) const;

        /*!
            \brief Check if a variable exists.

            Find out if a variable currently exists.
            \param sec Section to check in.
            \param var Variable to check for.
            \return bool, true if section exists in file.
        **/
        bool Exists(std::string sec, std::string var) const;

        /*!
            \brief Internal function to set variables.

            Set variable to value, called internally only.
            \param sec Section for variable.
            \param var Variable to set.
            \param val Value to set variable to.
        **/
        void SetVariable(std::string sec, std::string var, std::string val);

        /*!
            \brief Internal function to get value of a variable.

            Get value of variable, called internally only.
            \param sec Section for variable.
            \param var Variable to get.
            \param defVal Value to return if variable doesnt exist.
            \return Value of variable.
        **/
        std::string GetVariable(std::string sec, std::string var, std::string defVal) const;

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
        ZConfigFile(std::string filename);

        /*!
            \brief Destructor, flushes file.

            Flushes the file, ensures a flush if the file is left open.
        **/
        virtual ~ZConfigFile();

        /*!
            \brief Parse a file.
            
            Parses the file, reading the contents into the fileLayout map.
            \param filename File to parse and attach this ZDataFile to.
        **/
        void Process(std::string filename);

        /*!
            \brief Get value in floating point format from file.

            Get the current value of a variable in the file, or defVal if not found in file.
            \since 0.8.3
            \param section Name of section to seek variable under.
            \param var Name of variable to seek value for.
            \param defVal Value to return if var does not exist within section.
            \return Contents of the variable in floating point format.
        **/
        float GetFloat(std::string section, std::string var, float defVal) const;

        /*!
            \brief Get value in integer format from file.

            Get the current value of a variable in the file, or defVal if not found in file.
            \param section Name of section to seek variable under.
            \param var Name of variable to seek value for.
            \param defVal Value to return if var does not exist within section.
            \return Contents of the variable in integer format.
        **/
        int GetInt(std::string section, std::string var, int defVal) const;

        /*!
            \brief Get value in boolean format from file.

            Get the current value of a variable in the file, or defVal if not found in file. 
            (Valid values are "0","1","true" and "false")
            \param section Name of section to seek variable under.
            \param var Name of variable to seek value for.
            \param defVal Value to return if var does not exist within section.
            \return Contents of the variable in boolean format.
        **/
        bool GetBool(std::string section, std::string var, bool defVal) const;

        /*!
            \brief Get value in std::string format from file.

            Get the current value of a variable in the file, or defVal if not found in file. 
            \param section Name of section to seek variable under.
            \param var Name of variable to seek value for.
            \param defVal Value to return if var does not exist within section.
            \return Contents of the variable in std::string format.
        **/
        std::string GetString(std::string section, std::string var, std::string defVal) const;

        /*!
            \brief Set value in floating point format in file.

            Set the new value of a variable in the file to val, creating the section and variable 
            if not already found in file. 
            \since 0.8.3
            \param section Name of section to edit variable under.
            \param var Name of variable to set value for.
            \param val Floating point value to set variable to in file.
        **/
        void SetFloat(std::string section, std::string var, float val);

        /*!
            \brief Set value in integer format in file.

            Set the new value of a variable in the file to val, creating the section and variable 
            if not already found in file. 
            \param section Name of section to edit variable under.
            \param var Name of variable to set value for.
            \param val Integer value to set variable to in file.
        **/
        void SetInt(std::string section, std::string var, int val);

        /*!
            \brief Set value in boolean format in file.

            Set the new value of a variable in the file to val, creating the section and variable 
            if not already found in file.
            \param section Name of section to edit variable under.
            \param var Name of variable to set value for.
            \param val Boolean value to set variable to in file.
        **/
        void SetBool(std::string section, std::string var, bool val);

        /*!
            \brief Set value in std::string format in file.

            Set the new value of a variable in the file to val, creating the section and variable 
            if not already found in file.
            \param section Name of section to edit variable under.
            \param var Name of variable to set value for.
            \param val String value to set variable to in file.
        **/
        void SetString(std::string section, std::string var, std::string val);
        
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
