/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*$Id: ZRectTest.cpp,v 1.21 2003/11/24 22:59:18 cozman Exp $*/

#include <ZEngine.h>
#include <string> 
using namespace std;
using namespace ZE;

bool Initialize()
{
    ZEngine *engine = ZEngine::GetInstance();
    ZConfigFile cfg("tests.zcf");
    int w,h,bpp,rate;
    bool fs;
    std::string title;

    w = cfg.GetInt("ZRectTest","Width",800);
    h = cfg.GetInt("ZRectTest","height",600);
    bpp = cfg.GetInt("ZRectTest","bpp",32);
    fs = cfg.GetBool("ZRectTest","fullscreen",false);
    title = cfg.GetString("ZRectTest","title","ZRect Test");
    rate = cfg.GetInt("ZRectTest","framerate",60);

    return engine->CreateDisplay(w,h,bpp,fs,title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();
    ZRect moveRect(0,0,25,25),stillRect(100,100,100,100);
    float movDelta;

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();

        if(engine->IsActive())
        {
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();
            //movement//
            movDelta = static_cast<float>(engine->GetFrameTime()*30);
            if(engine->KeyIsPressed(SDLK_LEFT))
                moveRect.MoveRel(-movDelta,0);
            if(engine->KeyIsPressed(SDLK_RIGHT))
                moveRect.MoveRel(movDelta,0);
            if(engine->KeyIsPressed(SDLK_UP))
                moveRect.MoveRel(0,-movDelta);
            if(engine->KeyIsPressed(SDLK_DOWN))
                moveRect.MoveRel(0,movDelta);
            if(engine->KeyIsPressed(SDLK_EQUALS))
            {
                moveRect.MoveRel(-1,-1);
                moveRect.ResizeRel(2,2);
            }
            if(engine->KeyIsPressed(SDLK_MINUS))
            {
                moveRect.MoveRel(1,1);
                moveRect.ResizeRel(-2,-2);
            }

            engine->Clear();
            moveRect.Draw(255,0,0,128);
            stillRect.Draw(0,0,255,128);
            moveRect.Intersection(stillRect).Draw(0,255,0);
            engine->Update();
        }

    } while(!engine->QuitRequested());
}

int main(int argc, char *argv[])
{
    if(Initialize())
        Test();
    ZEngine::ReleaseInstance();
    return 0;
}
