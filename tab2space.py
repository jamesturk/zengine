#!/usr/bin/python


#Python script used to convert tabs to spaces.
import os,re

def ProcessFile(filename):
    linenum = 0
    print filename,
    lines = open(filename,'r').readlines()
    f = open(filename,'w')
    for line in lines:
	linenum+=1
        f.write(line.expandtabs(4))
        if len(line) > 80:
            print linenum,'[',len(line),']',
    f.close()
    print 'Done!'

def FileType(filename):
    try:
        return filename.split('.')[1]
    except: 
        return ''
    
def ProcessDir(dir):
    entries = os.listdir(dir)
    for entry in entries:
        if os.path.isdir(os.path.join(dir,entry)):
            ProcessDir(os.path.join(dir,entry))
        else:
            type = FileType(entry)
            if(type == 'cpp' or type == 'h' or type == 'txt'):
                ProcessFile(os.path.join(dir,entry))


def main():
    dir = os.getcwd()
    ProcessDir(dir)

main()

    
