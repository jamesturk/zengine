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

    w = cfg.GetInt("ZTimerTest","width",800);
    h = cfg.GetInt("ZTimerTest","height",600);
    bpp = cfg.GetInt("ZTimerTest","bpp",32);
    fs = cfg.GetBool("ZTimerTest","fullscreen",false);
    title = cfg.GetString("ZTimerTest","title","ZTimer Test");

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    string TimerName[3] = {"ZEngine Timer", "ZEngine Hooked Timer", "SDL Hooked Timer"};
    int curTimer = 0;

    //Open and Setup Font and Create Images and Timers//
    ZImage text[5];
    ZFont font("data/almontew.ttf",48);
    ZTimer TimerOne, TimerTwo(false);    //Timer Two is on the SDL Timer.

    //do this only once//
    font.DrawText("(T)oggle | (P)ause | (U)npause",text[4]);

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();
        if(engine->KeyIsPressed(SDLK_s))
        {
            //code to toggle screen//
            engine->SetupDisplay(engine->Width(),engine->Height(),engine->BPP(),!engine->IsFullscreen());
            engine->CreateDisplay("ZImage Test");
        }
        if(engine->KeyIsPressed(SDLK_ESCAPE))
            engine->RequestQuit();
        //pause current timer//
        if(engine->KeyIsPressed(SDLK_p))
        {
            switch(curTimer)
            {
                case 0:
                    engine->PauseTimer();
                    break;
                case 1:
                    TimerOne.Pause();
                    break;
                case 2:
                    TimerTwo.Pause();
                    break;
            }
        }
        //unpause current timer//
        if(engine->KeyIsPressed(SDLK_u))
        {
            switch(curTimer)
            {
                case 0:
                    engine->UnpauseTimer();
                    break;
                case 1:
                    TimerOne.Unpause();
                    break;
                case 2:
                    TimerTwo.Unpause();
                    break;
            }
        }
        //switch//
        if(engine->KeyIsPressed(SDLK_t))
        {
            if(++curTimer > 2)
                curTimer = 0;
            engine->Delay(200);
        }

        //Render all the fonts//
        font.DrawText(FormatStr("Current Timer: %s",TimerName[curTimer].c_str()),text[0]);
        font.DrawText(FormatStr("%s Time: %d",TimerName[0].c_str(),engine->GetTime()),text[1]);
        font.DrawText(FormatStr("%s Time: %d",TimerName[1].c_str(),TimerOne.GetTime()),text[2]);
        font.DrawText(FormatStr("%s Time: %d",TimerName[2].c_str(),TimerTwo.GetTime()),text[3]);

        engine->Clear();    //clear screen

        for(int i=0; i <= 4; i++)
            text[i].Draw(0,i*50.0f);
        
        engine->UpdateScreen();    //update the screen

    } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
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
