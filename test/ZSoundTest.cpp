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

    w = cfg.GetInt("ZSoundTest","width",800);
    h = cfg.GetInt("ZSoundTest","height",600);
    bpp = cfg.GetInt("ZSoundTest","bpp",32);
    fs = cfg.GetBool("ZSoundTest","fullscreen",false);
    title = cfg.GetString("ZSoundTest","title","ZSound Test");

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    string name[5] = { "monkey", "rooster", "kick", "carcrash", "whip" };
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
        if(engine->KeyIsPressed(SDLK_s))
        {
            //code to toggle screen//
            engine->SetupDisplay(engine->Width(),engine->Height(),engine->BPP(),!engine->IsFullscreen());
            engine->CreateDisplay("ZSound Test");
        }
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
            sample[sampleNum].SetVolume(sample[sampleNum].GetVolume()+1);
        if(engine->KeyIsPressed(SDLK_DOWN))
            sample[sampleNum].SetVolume(sample[sampleNum].GetVolume()-1);


        font.DrawText(FormatStr("Volume: %d",sample[sampleNum].GetVolume()),text[4]);
        font.DrawText(FormatStr("Sample: %s",name[sampleNum].c_str()),text[5]);

        engine->Clear();    //clear screen
        for(int i=0; i < 6; i++)
            text[i].Draw(0,i*50);
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
