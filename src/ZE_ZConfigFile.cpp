/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZConfigFile.cpp <br>
Description: Implementation source file for ZConfigFile, the ZEngine INI-Style Config File. <br>
Author(s): James Turk <br>
$Id: ZE_ZConfigFile.cpp,v 1.7 2003/04/08 03:30:50 cozman Exp $<br>

    \file ZE_ZConfigFile.cpp
    \brief Source file for ZConfigFile.

    Implementation of ZConfigFile, the ZEngine INI-Style Config File.
**/

#include "ZE_ZConfigFile.h"

namespace ZE
{

string ZConfigFile::CleanString(string str)  const
{
    string tmpStr;
    bool inQuotes = false;

    //cycle through, only copy spaces and if a character is uppercase, convert it to lowercase
    for(string::size_type i = 0; i < str.length(); ++i)
    {
        if(!isspace(str[i]) || inQuotes)
        {
            if(str[i] == '\"')
                inQuotes = !inQuotes;
            if(isupper(str[i]) && !inQuotes)
                str[i] = static_cast<char>(tolower(str[i]));
            tmpStr += str[i];
        }
    }
    return tmpStr;
}

bool ZConfigFile::Exists(string sec) const
{
    list<ZCF_Section>::const_iterator secIter;

    sec = CleanString(sec);

    for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
    {
        if(CleanString((*secIter).section) == sec)
            return true;
    }
    return false;
}

bool ZConfigFile::Exists(string sec, string var) const
{
    list<ZCF_Section>::const_iterator secIter;
    list<ZCF_Variable>::const_iterator varIter;

    sec = CleanString(sec);
    var = CleanString(var);

    for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
    {
        if(CleanString((*secIter).section) == sec)
        {
            for(varIter = (*secIter).varList.begin(); varIter != (*secIter).varList.end(); ++varIter)
            {
                if(CleanString((*varIter).var) == var)
                    return true;
            }
        }
    }
    return false;
}

void ZConfigFile::SetVariable(string sec, string var, string val)
{
    list<ZCF_Section>::iterator secIter;
    list<ZCF_Variable>::iterator varIter;

    if(Exists(CleanString(sec)))
    {
        sec = CleanString(sec);
        for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
        {
            if(CleanString((*secIter).section) == sec)    //if this is the section
            {
                if(Exists(sec,var))
                {
                    var = CleanString(var);
                    for(varIter = (*secIter).varList.begin(); varIter != (*secIter).varList.end(); ++varIter)
                    {
                        if(CleanString((*varIter).var) == var)    //if this is the variable
                        {
                            (*varIter).val = val;
                            break;    //break from this loop
                        }
                    }
                    break;    //done in the for loop, time to go
                }
                else
                {
                    ZCF_Variable tempVar;
                    tempVar.var = var;
                    (*secIter).varList.push_back(tempVar);
                    SetVariable(sec,var,val);
                }
            }
        }
    }
    else
    {
        ZCF_Section tempSec;
        tempSec.section = sec;
        rFileLayout.push_back(tempSec);
        SetVariable(sec,var,val);
    }
}

string ZConfigFile::GetVariable(string sec, string var, string defVal) const
{
    list<ZCF_Section>::const_iterator secIter;
    list<ZCF_Variable>::const_iterator varIter;

    sec = CleanString(sec);
    var = CleanString(var);

    if(Exists(sec))
    {
        for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
        {
            if(CleanString((*secIter).section) == sec)    //if this is the section
            {
                if(Exists(sec,var))
                {
                    for(varIter = (*secIter).varList.begin(); varIter != (*secIter).varList.end(); ++varIter)
                    {
                        if(CleanString((*varIter).var) == var)    //if this is the variable
                            return (*varIter).val;    //return now
                    }
                    break;    //done in the for loop, time to go
                }
                else
                {
                    return defVal;
                    break;
                }
            }
        }
    }

    return defVal;    //if it gets to the end just return the default
}

ZConfigFile::ZConfigFile() {}

ZConfigFile::ZConfigFile(string rFilename)
{
    Process(rFilename);
}

ZConfigFile::~ZConfigFile()
{
    Close();
}

void ZConfigFile::Process(string filename)
{
    rFilename = filename;

    ifstream cfile(rFilename.c_str());
    string section, str, var, tmp;

    rFileLayout.clear();

    while(!cfile.eof() && cfile.is_open())
    {
        getline(cfile,str);    //read in a line
        tmp = CleanString(str);    //get a clean version

        //if string is bracketed it is a section, if it begins in a letter it is a variable
        if(tmp[0] == '[' && tmp[tmp.length()-1] == ']')
            section = str;
        else if(isalpha(tmp[0]))
        {
            var = str.substr(0,str.find('='));    //split the string at the equals sign
            SetVariable(section,var,str.substr(str.find('=')+1,str.length()-var.length()-1));
        }
    }
    cfile.close();
}

float ZConfigFile::GetFloat(string section, string var, float defVal) const
{
    string val;
    char tmp[20];

    section = CleanString(section);
    var = CleanString(var);

    section = '[' + section + ']';

    sprintf(tmp,"%d",defVal);
    val = GetVariable(section,var,tmp);

    if(!atof(val.c_str()) && val[0] !='0')    //if it is zero but doesn't start with a zero
        return defVal;
    else
        return static_cast<float>(atof(val.c_str()));   //atof returns a double(?!)
}

int ZConfigFile::GetInt(string section, string var, int defVal) const
{
    string val;
    char tmp[20];

    section = CleanString(section);
    var = CleanString(var);

    section = '[' + section + ']';

    sprintf(tmp,"%d",defVal);
    val = GetVariable(section,var,tmp);

    if(!atoi(val.c_str()) && val[0] !='0')    //if it is zero but doesn't start with a zero
        return defVal;
    else
        return atoi(val.c_str());
}

bool ZConfigFile::GetBool(string section, string var, bool defVal) const
{
    string val,tmp;

    section = CleanString(section);
    var = CleanString(var);

    section = '[' + section + ']';

    tmp = defVal ? "true" : "false";
    val = CleanString(GetVariable(section,var,tmp));

    if(val == "true" || val == "1")
        return true;
    else if(val == "false" || val == "0")
        return false;
    else
        return defVal;
}

string ZConfigFile::GetString(string section, string var, string defVal) const
{
    string val;

    section = CleanString(section);
    var = CleanString(var);

    section = '[' + section + ']';

    val = CleanString(GetVariable(section,var,defVal));
    if(val == CleanString(defVal))
        val = defVal;


    if(val[0] == '\"' && val[val.length()-1] == '\"')
        return val.substr(1,val.length()-2);    //chop off quotes
    else
        return val;
}

void ZConfigFile::SetFloat(string section, string var, float val)
{
    char buf[20];
    sprintf(buf,"%f",val);

    section = '[' + section + ']';
    SetVariable(section,var,buf);
}

void ZConfigFile::SetInt(string section, string var, int val)
{
    char buf[20];
    sprintf(buf,"%d",val);

    section = '[' + section + ']';
    SetVariable(section,var,buf);
}

void ZConfigFile::SetBool(string section, string var, bool val)
{
    string tmp = val ? "true" : "false";

    section = '[' + section + ']';
    SetVariable(section,var,tmp);
}

void ZConfigFile::SetString(string section, string var, string val)
{
    section = '[' + section + ']';
    val = "\"" + val + "\"";
    SetVariable(section,var,val);
}

void ZConfigFile::Flush()
{
    list<ZCF_Section>::iterator secIter;
    list<ZCF_Variable>::iterator varIter;
    string secName;

    //in case the filename is already cleared somehow
    if(rFilename.length())
    {
        ofstream cfile(rFilename.c_str(), ios::out|ios::trunc);

        if(cfile)
        {
            //iteration through sections
            for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
            {
                //ensure that section is valid
                secName = CleanString((*secIter).section);
                if(secName.length() && secName[0] == '[' && secName[secName.length()-1] == ']')
                {
                    cfile << (*secIter).section << endl;    //write out raw section title

                    //for each variable in section, write out variable=value
                    for(varIter = (*secIter).varList.begin(); varIter != (*secIter).varList.end(); ++varIter)
                    {
                        if(CleanString((*varIter).var).length())    //ensures that variable is valid
                            cfile << (*varIter).var << '=' << (*varIter).val << endl;
                    }
                }
            }
            cfile.close();
        }
    }
}

void ZConfigFile::Close()
{
    Flush();
    rFilename = "";
}

}
