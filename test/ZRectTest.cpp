/*******************************************************************************
         This file is Part of the ZEngine Library for SDL Game Development.
                      Copyright (C) 2002 ConceptOfZero.net

             Licensed under the BSD License, see licensing.txt.

    The maintainer of this library is James Turk (jturk@conceptofzero.net) 
         and the home of this Library is http://www.conceptofzero.net/
*******************************************************************************/

#include <ZEngine.h>
#include <string> 
using namespace std;
using namespace ZE;

void Initialize()
{
    ZEngine *engine = ZEngine::GetInstance();
    ZConfigFile cfg("tests.zcf");
    int w,h,bpp;
    bool fs;
    string title;

    w = cfg.GetInt("ZRectTest","Width",800);
    h = cfg.GetInt("ZRectTest","height",600);
    bpp = cfg.GetInt("ZRectTest","bpp",32);
    fs = cfg.GetBool("ZRectTest","fullscreen",false);
    title = cfg.GetString("ZRectTest","title","ZRect Test");

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();
    ZRect moveRect(0,0,25,25),stillRect(100,100,100,100);
    double movDelta;

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();
        if(engine->KeyIsPressed(SDLK_s))
        {
            //code to toggle screen//
            engine->SetupDisplay(engine->Width(),engine->Height(),engine->BPP(),!engine->IsFullscreen());
            engine->CreateDisplay("ZRect Test");
        }
        if(engine->KeyIsPressed(SDLK_ESCAPE))
            engine->RequestQuit();
        //movement//
        movDelta = engine->GetFrameTime()*30;
        if(engine->KeyPress(SDLK_LEFT))
            moveRect.MoveRel(-movDelta,0);
        if(engine->KeyPress(SDLK_RIGHT))
            moveRect.MoveRel(movDelta,0);
        if(engine->KeyPress(SDLK_UP))
            moveRect.MoveRel(0,-movDelta);
        if(engine->KeyPress(SDLK_DOWN))
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
        engine->UpdateScreen();

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
