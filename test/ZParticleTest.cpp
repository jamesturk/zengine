/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*$Id: ZParticleTest.cpp,v 1.3 2003/08/02 01:18:45 cozman Exp $*/

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

    w = cfg.GetInt("ZParticleTest","width",800);
    h = cfg.GetInt("ZParticleTest","height",600);
    bpp = cfg.GetInt("ZParticleTest","bpp",32);
    fs = cfg.GetBool("ZParticleTest","fullscreen",false);
    title = cfg.GetString("ZParticleTest","title","ZParticle Test");
    rate = cfg.GetInt("ZParticleTest","framerate",60);

    engine->SetupDisplay(w,h,bpp,fs);
    engine->SetDesiredFramerate(rate);
    return engine->CreateDisplay(title);
}


void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    ZFont font("data/axaxax.ttf",20);
    ZImage text[3],bg;
    ZSimpleParticleSystem<ZSimpleParticle> effect[3];
    int effectNum=0,i;
    
    effect[0].SetPosRange(350,300,450,350);
    effect[0].SetColorRange(0,255,0,255,0,255,128,255);
    effect[0].SetVelocityRange(-60,-300,60,-60);
    effect[0].SetEnergyRange(0.1f,2,-0.3f,0.05f);
    effect[0].SetSizeRange(20,30,1,5);
    effect[0].SetDrawStyle(DS_IMAGE);
    effect[0].SetMaxParticles(2000);
    effect[0].SetRate(120);
    effect[0].SetImage("data/particle1.tga");

    effect[1].SetPosRange(0,0,static_cast<float>(engine->DisplayWidth()),20);
    effect[1].SetColorRange(230,255,230,255,250,255,200,240);
    effect[1].SetVelocityRange(-10,30,10,50);
    effect[1].SetEnergyRange(1,1);
    effect[1].SetSizeRange(1,2);
    effect[1].SetDrawStyle(DS_POINT);
    effect[1].SetMaxParticles(3000);
    effect[1].SetRate(80);

    effect[2].SetPosRange(300,500,420,550);
    effect[2].SetColorRange(40,60,40,60,40,60,200,240);
    effect[2].SetVelocityRange(-5,-1,5,-5);
    effect[2].SetEnergyRange(1,1);
    effect[2].SetSizeRange(24,32,-1,-5);
    effect[2].SetDrawStyle(DS_IMAGE);
    effect[2].SetMaxParticles(250);
    effect[2].SetRate(30);
    effect[2].SetImage("data/particle2.tga");

    bg.Open("data/rainbow.bmp");
    //bg.Resize(engine->DisplayWidth()/2,engine->DisplayHeight());  //gives perspective on alpha on half of screen

    font.DrawText("(P)ause    (U)npause    (C)lear",text[0]);
    font.DrawText("1-3 : Change System Being Controlled",text[1]);
    font.DrawText("Controlling Color Sparkle Effect",text[2]);

    do
    {
        engine->CheckEvents();

        if(engine->IsActive())
        {
            
            if(engine->ImagesNeedReload())
            {
                for(i=0; i < 3; ++i)
                    effect[i].ReloadImage();
            }

            if(engine->KeyIsPressed(SDLK_1))
            {
                effectNum = 0;
                font.DrawText("Controlling Color Sparkle Effect",text[2]);
            }
            if(engine->KeyIsPressed(SDLK_2))
            {
                effectNum = 1;
                font.DrawText("Controlling Snow Effect",text[2]);
            }
            if(engine->KeyIsPressed(SDLK_3))
            {
                effectNum = 2;
                font.DrawText("Controlling Smokeish Effect",text[2]);
            }
            
            if(engine->KeyIsPressed(SDLK_p))
                effect[effectNum].Pause();
            if(engine->KeyIsPressed(SDLK_u))
                effect[effectNum].Unpause();
            if(engine->KeyIsPressed(SDLK_c))
                effect[effectNum].Clear();
            

            //do updating//
            if(engine->KeyIsPressed(SDLK_s))
                engine->ToggleFullscreen();
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();

            for(i=0; i < 3; ++i)
                    effect[i].Update();

            engine->Clear();
            bg.Draw(0,0);

            for(i=0; i < 3; ++i)
            {
                effect[i].Render();
                text[i].Draw(0,i*25);
            }

            engine->Update();
        }
        else
            engine->Delay(10);

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
