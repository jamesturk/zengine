/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

#include "ZE_ZConfigFile.h"

namespace ZE
{

std::string ZConfigFile::CleanString(std::string str)  const
{
    std::string tmpStr;
    bool inQuotes = false;

    //cycle through, only copy spaces and if a character is uppercase, convert it to lowercase
    for(std::string::size_type i = 0; i < str.length(); ++i)
    {
        if(!std::isspace(str[i]) || inQuotes)   //if it's in quotes leave it be
        {
            if(str[i] == '\"')
                inQuotes = !inQuotes;   //each quote toggles the quote state
            if(std::isupper(str[i]) && !inQuotes)
                str[i] = static_cast<char>(std::tolower(str[i]));
            tmpStr += str[i];
        }
    }
    return tmpStr;
}

bool ZConfigFile::Exists(std::string sec) const
{
    std::list<ZCF_Section>::const_iterator secIter;

    sec = CleanString(sec);

    //check list for 'cleaned' version of string
    for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
    {
        if(CleanString((*secIter).section) == sec)
            return true;
    }
    return false;
}

bool ZConfigFile::Exists(std::string sec, std::string var) const
{
    std::list<ZCF_Section>::const_iterator secIter;
    std::list<ZCF_Variable>::const_iterator varIter;

    sec = CleanString(sec);
    var = CleanString(var);

    //first find section, then do same search for variable
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

void ZConfigFile::SetVariable(std::string sec, std::string var, std::string val)
{
    std::list<ZCF_Section>::iterator secIter;
    std::list<ZCF_Variable>::iterator varIter;

    if(Exists(CleanString(sec)))    //if section exists find it
    {
        sec = CleanString(sec);
        for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
        {
            if(CleanString((*secIter).section) == sec)    //if this is the section
            {
                if(Exists(sec,var)) //if variable exists find it
                {
                    var = CleanString(var);
                    for(varIter = (*secIter).varList.begin(); varIter != (*secIter).varList.end(); ++varIter)
                    {
                        if(CleanString((*varIter).var) == var)    //once variable found, set value
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

std::string ZConfigFile::GetVariable(std::string sec, std::string var, std::string defVal) const
{
    //finds variable in same manner as SetVariable, but if not found doesn't create, just returns default value
    std::list<ZCF_Section>::const_iterator secIter;
    std::list<ZCF_Variable>::const_iterator varIter;

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

ZConfigFile::ZConfigFile() 
{
}

ZConfigFile::ZConfigFile(std::string rFilename)
{
    Process(rFilename); //process does all the work
}

ZConfigFile::~ZConfigFile()
{
    Close();
}

void ZConfigFile::Process(std::string filename)
{
    rFilename = filename;
    int commentNum,newlineNum;
    char commentStr[15],newlineStr[15];
    std::string section, str, var, tmp;
    std::ifstream cfile(rFilename.c_str()); 

    commentNum = newlineNum = 0;    //comment/newline support is a bit of a hack

    rFileLayout.clear();    //layout must be cleared, in case variable is being used multiple times

    while(!cfile.eof() && cfile.is_open())  //parses entire file
    {
        std::getline(cfile,str);    //read in a line
        tmp = CleanString(str);    //get a clean version

        //if std::string is bracketed it is a section, if it begins in a letter it is a variable
        if(tmp[0] == '[' && tmp[tmp.length()-1] == ']')
            section = str;
        else if(std::isalpha(tmp[0]))   //variables must start with a letter
        {
            var = str.substr(0,str.find('='));    //split the std::string at the equals sign
            SetVariable(section,var,str.substr(str.find('=')+1,str.length()-var.length()-1));
        }
        else if(tmp[0] == '#' || tmp[0] == ';') //acceptable comment characters
        {
            sprintf(commentStr,"__comment%d",commentNum);
            SetVariable(section,commentStr,str);
            ++commentNum;
        }
        else if(tmp.length() == 0 && !cfile.eof())  //avoid adding a line to end of file each time
        {
            sprintf(newlineStr,"__newline%d",newlineNum);
            SetVariable(section,newlineStr,str);
            ++newlineNum;
        }

    }
    cfile.close();
}

//each get* gets the variable (stored as a string) from using GetVariable, then converts it to the desired format
float ZConfigFile::GetFloat(std::string section, std::string var, float defVal) const
{
    std::string val;
    char tmp[20];

    section = CleanString(section);
    var = CleanString(var);

    section = '[' + section + ']';

    sprintf(tmp,"%f",defVal);
    val = GetVariable(section,var,tmp);

    if(!atof(val.c_str()) && val[0] !='0')    //if it is zero but doesn't start with a zero
        return defVal;
    else
        return static_cast<float>(atof(val.c_str()));   //atof returns a double(?!)
}

int ZConfigFile::GetInt(std::string section, std::string var, int defVal) const
{
    std::string val;
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

bool ZConfigFile::GetBool(std::string section, std::string var, bool defVal) const
{
    std::string val,tmp;

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

std::string ZConfigFile::GetString(std::string section, std::string var, std::string defVal) const
{
    std::string val;

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

//each set* converts it's variable to a string, then places it in using SetVariable
void ZConfigFile::SetFloat(std::string section, std::string var, float val)
{
    char buf[20];
    sprintf(buf,"%f",val);

    section = '[' + section + ']';
    SetVariable(section,var,buf);
}

void ZConfigFile::SetInt(std::string section, std::string var, int val)
{
    char buf[20];
    sprintf(buf,"%d",val);

    section = '[' + section + ']';
    SetVariable(section,var,buf);
}

void ZConfigFile::SetBool(std::string section, std::string var, bool val)
{
    std::string tmp = val ? "true" : "false";

    section = '[' + section + ']';
    SetVariable(section,var,tmp);
}

void ZConfigFile::SetString(std::string section, std::string var, std::string val)
{
    section = '[' + section + ']';
    val = "\"" + val + "\"";
    SetVariable(section,var,val);
}

void ZConfigFile::Flush()
{
    std::list<ZCF_Section>::iterator secIter;
    std::list<ZCF_Variable>::iterator varIter;
    std::string secName;

    //in case the filename is already cleared somehow
    if(rFilename.length())
    {
        //open the file blanked out, to not duplicate entries
        std::ofstream cfile(rFilename.c_str(), std::ios::out|std::ios::trunc);

        if(cfile)
        {
            //iteration through sections
            for(secIter = rFileLayout.begin(); secIter != rFileLayout.end(); ++secIter)
            {
                //ensure that section is valid
                secName = CleanString((*secIter).section);
                if(secName.length() && secName[0] == '[' && secName[secName.length()-1] == ']')
                {
                    cfile << (*secIter).section << std::endl;    //write out raw section title

                    //for each variable in section, write out variable=value
                    for(varIter = (*secIter).varList.begin(); varIter != (*secIter).varList.end(); ++varIter)
                    {
                        if((*varIter).var[0] == '_') 
                        {
                            if( ((*varIter).var).substr(2,7) == "comment")
                                cfile << (*varIter).val << std::endl;
                            else if( ((*varIter).var).substr(2,7) == "newline")
                                cfile << std::endl;
                        }
                        else if(CleanString((*varIter).var).length())    //ensures that variable is valid
                            cfile << (*varIter).var << '=' << (*varIter).val << std::endl;
                    }
                }
            }
            cfile.close();
        }
    }
}

void ZConfigFile::Close()
{
    Flush();    //when the file is closed it should be flushed to disk
    rFilename = "";
}

}
