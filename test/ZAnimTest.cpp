/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

// $Id: ZAnimTest.cpp,v 1.3 2004/01/13 23:56:28 cozman Exp $

#include <ZEngine.h>
#include <string> 
using namespace std;
using namespace ZE;

bool Initialize()
{
    ZEngine *engine = ZEngine::GetInstance();
    ZConfigFile cfg("tests.zcf");
    int w,h,bpp;
    bool fs;
    string title;

    w = cfg.GetInt("ZAnimTest","width",800);
    h = cfg.GetInt("ZAnimTest","height",600);
    bpp = cfg.GetInt("ZAnimTest","bpp",32);
    fs = cfg.GetBool("ZAnimTest","fullscreen",false);
    title = cfg.GetString("ZAnimTest","title","ZAnimation Test");

    engine->InitErrorLog();
    return engine->CreateDisplay(w,h,bpp,fs,title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();
    ZFont font;
    ZImage srcImg,tankImg[8],text[2];
    ZAnimation tank[8];
    int i;

    font.OpenFromZRF("default");

    srcImg.OpenFromZip("data/data.zip","tank.bmp");
    for(i=0; i < 8; ++i)
        tankImg[i].OpenFromImage(srcImg,0,140*i,200,140);
    srcImg.Release();   //don't need this, but no need to keep image around
    font.DrawText("From left to right: ZANIM_NONE, ZANIM_ONCE, ZANIM_LOOP, ZANIM_REVERSE",text[0]);
    font.DrawText("top row - forward  |  bottom row - reverse",text[1]);

    tank[0].Create(tankImg,8,250,ZANIM_NONE,true);
    tank[1].Create(tankImg,8,250,ZANIM_NONE,false);
    tank[2].Create(tankImg,8,250,ZANIM_ONCE,true);
    tank[3].Create(tankImg,8,250,ZANIM_ONCE,false);
    tank[4].Create(tankImg,8,250,ZANIM_LOOP,true);
    tank[5].Create(tankImg,8,250,ZANIM_LOOP,false);
    tank[6].Create(tankImg,8,250,ZANIM_REVERSE,true);
    tank[7].Create(tankImg,8,250,ZANIM_REVERSE,false);

    for(i=0; i < 8; ++i)
        tank[i].Start();

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();
        if(engine->IsActive())
        {
            
            for(i=0; i < 8; ++i)
                tank[i].Update();
            
            engine->ClearDisplay();

            for(i=0; i < 8; ++i)
                tank[i].Draw(200*(i/2),200*(i%2));
            for(i=0; i < 2; ++i)
                text[i].Draw((engine->DisplayWidth()-text[i].Width())/2,500.0f+i*20);

            engine->Update();
        }

    } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
}

int main(int argc, char *argv[])
{
    if(Initialize())
        Test();
    return 0;
}
