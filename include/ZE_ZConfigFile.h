/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#ifndef __ze_zconfigfile_h__
#define __ze_zconfigfile_h__

#include "ZE_ZEngine.h"

namespace ZE
{

class ZConfigFile
{
    private:

        class ZCF_Variable
        {
            public:
                std::string var;
                std::string val;
        };
        
        class ZCF_Section
        {
            public:
                std::string section;
                std::list<ZCF_Variable> varList;
        };

    protected:
        std::list<ZCF_Section> rFileLayout;
        std::string rFilename;
     
        std::string CleanString(std::string str)  const;      
        bool Exists(std::string sec) const;
        bool Exists(std::string sec, std::string var) const;
        void SetVariable(std::string sec, std::string var, std::string val);
        std::string GetVariable(std::string sec, std::string var, std::string defVal) const;

    public:     
        ZConfigFile();
        ZConfigFile(std::string filename);
        virtual ~ZConfigFile();

        void Process(std::string filename);

        float GetFloat(std::string section, std::string var, float defVal) const;
        int GetInt(std::string section, std::string var, int defVal) const;
        bool GetBool(std::string section, std::string var, bool defVal) const;
        std::string GetString(std::string section, std::string var, std::string defVal) const;
        
        void SetFloat(std::string section, std::string var, float val);
        void SetInt(std::string section, std::string var, int val);
        void SetBool(std::string section, std::string var, bool val);
        void SetString(std::string section, std::string var, std::string val);
        
        void Flush();
        void Close();
};

}

#endif //__ze_zconfigfile_h__
