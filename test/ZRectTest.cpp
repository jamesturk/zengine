/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*$Id: ZRectTest.cpp,v 1.14 2003/01/08 06:07:07 cozman Exp $*/

#include <ZEngine.h>
#include <string> 
using namespace std;
using namespace ZE;

void Initialize()
{
    ZEngine *engine = ZEngine::GetInstance();
    ZConfigFile cfg("tests.zcf");
    int w,h,bpp,rate;
    bool fs;
    string title;

    w = cfg.GetInt("ZRectTest","Width",800);
    h = cfg.GetInt("ZRectTest","height",600);
    bpp = cfg.GetInt("ZRectTest","bpp",32);
    fs = cfg.GetBool("ZRectTest","fullscreen",false);
    title = cfg.GetString("ZRectTest","title","ZRect Test");
    rate = cfg.GetInt("ZRectTest","framerate",60);

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
    engine->SetDesiredFramerate(rate);
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

    } while(!engine->QuitRequested());
}

int main(int argc, char *argv[])
{
    ZEngine *engine = ZEngine::GetInstance();

    Initialize();
    //engine->InitPhysFS(argv[0]);    //remove this line if PhysFS is not available
    Test();

    ZEngine::ReleaseInstance();    //release engine instance
    return 0;
}
