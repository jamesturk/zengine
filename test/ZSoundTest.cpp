/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*$Id: ZSoundTest.cpp,v 1.13 2003/06/11 05:51:47 cozman Exp $*/

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

    w = cfg.GetInt("ZSoundTest","width",800);
    h = cfg.GetInt("ZSoundTest","height",600);
    bpp = cfg.GetInt("ZSoundTest","bpp",32);
    fs = cfg.GetBool("ZSoundTest","fullscreen",false);
    title = cfg.GetString("ZSoundTest","title","ZSound Test");
    rate = cfg.GetInt("ZSoundTest","framerate",60);

    engine->SetupDisplay(w,h,bpp,fs);
    engine->SetDesiredFramerate(rate);
    return engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    std::string name[5] = { "monkey", "rooster", "kick", "carcrash", "whip" };
    ZSound sample[5];
    ZFont font("data/almontew.ttf",48);
    ZImage text[6];
    int sampleNum = 0;

    for(int i=0; i < 5; i++)
        sample[i].Open(FormatStr("data/%s.wav",name[i].c_str()));

    font.DrawText("(P)ause\t(U)npause",text[0]);
    font.DrawText("(F)ade Out\t(H)alt\t",text[1]);
    font.DrawText("Space - Play\t Up/Down - Control Volume",text[2]);
    font.DrawText("1-5 Change Sample Being Controled",text[3]);
    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();

        if(engine->IsActive())
        {
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();
            if(engine->KeyIsPressed(SDLK_1))
                sampleNum = 0;
            if(engine->KeyIsPressed(SDLK_2))
                sampleNum = 1;
            if(engine->KeyIsPressed(SDLK_3))
                sampleNum = 2;
            if(engine->KeyIsPressed(SDLK_4))
                sampleNum = 3;
            if(engine->KeyIsPressed(SDLK_5))
                sampleNum = 4;
            if(engine->KeyIsPressed(SDLK_p))
                sample[sampleNum].Pause();
            if(engine->KeyIsPressed(SDLK_u))
                sample[sampleNum].Unpause();
            if(engine->KeyIsPressed(SDLK_f))
                sample[sampleNum].Stop(5000);
            if(engine->KeyIsPressed(SDLK_h))
                sample[sampleNum].Stop();
            if(engine->KeyIsPressed(SDLK_SPACE))
                sample[sampleNum].Play();
            if(engine->KeyIsPressed(SDLK_UP))
                sample[sampleNum].SetVolume(sample[sampleNum].Volume()+1);
            if(engine->KeyIsPressed(SDLK_DOWN))
                sample[sampleNum].SetVolume(sample[sampleNum].Volume()-1);

            font.DrawText(FormatStr("Volume: %d",sample[sampleNum].Volume()),text[4]);
            font.DrawText(FormatStr("Sample: %s",name[sampleNum].c_str()),text[5]);

            engine->Clear();    //clear screen
            for(int i=0; i < 6; i++)
                text[i].Draw(0,i*50);
            engine->Update();    //update the screen
        }

    } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
}

int main(int argc, char *argv[])
{
    ZEngine *engine = ZEngine::GetInstance();

    if(Initialize())
    {
        //engine->InitPhysFS(argv[0]);    //remove this line if PhysFS is not available
        Test();
    }

    ZEngine::ReleaseInstance();    //release engine instance
    return 0;
}
