/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

// $Id: ZMusicTest.cpp,v 1.23 2004/01/13 23:56:28 cozman Exp $

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
    std::string title;

    w = cfg.GetInt("ZMusicTest","width",800);
    h = cfg.GetInt("ZMusicTest","height",600);
    bpp = cfg.GetInt("ZMusicTest","bpp",32);
    fs = cfg.GetBool("ZMusicTest","fullscreen",false);
    title = cfg.GetString("ZMusicTest","title","ZMusic Test");

    engine->InitAudio();
    return engine->CreateDisplay(w,h,bpp,fs,title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    ZMusic song("data/sample.ogg");
    ZFont font("data/almontew.ttf",48);
    ZImage text[4];

    if(!song.IsLoaded())    //this executes if there is no music.ogg file
    {
        engine->CreateDisplay(800,70,32,false,"ZMusic Test");
        engine->ClearDisplay();
        font.DrawText("sample.ogg does not exist, please read music.txt.",text[0]);
        text[0].Draw(0,0);
        engine->Update();
        do
        {
            engine->CheckEvents();
            engine->Update();
        } while(!engine->QuitRequested());
    }
    else    //this is the actual example
    {
        font.DrawText("(P)ause\t(U)npause\t(R)ewind",text[0]);
        font.DrawText("(F)ade Out\t(H)alt\t",text[1]);
        font.DrawText("Space - Play\t Up/Down - Control Volume",text[2]);

        song.Play();
        do
        {
            //In the active loop, check events first//
            engine->CheckEvents();

            if(engine->IsActive())
            {
                if(engine->KeyIsPressed(SDLK_ESCAPE))
                    engine->RequestQuit();
                if(engine->KeyIsPressed(SDLK_r))
                    song.Rewind();
                if(engine->KeyIsPressed(SDLK_p))
                    song.Pause();
                if(engine->KeyIsPressed(SDLK_u))
                    song.Unpause();
#if SND_BACKEND == ZE_MIXER
                if(engine->KeyIsPressed(SDLK_f))
                    song.Stop(200);
#endif
                if(engine->KeyIsPressed(SDLK_h))
                    song.Stop();
                if(engine->KeyIsPressed(SDLK_SPACE))
                    song.Play();
                if(engine->KeyIsPressed(SDLK_UP))
                    song.SetVolume(song.GetVolume()+1);
                if(engine->KeyIsPressed(SDLK_DOWN) && song.GetVolume() > 0)
                    song.SetVolume(song.GetVolume()-1);
                if(engine->KeyIsPressed(SDLK_v))
                    song.SetVolume(100);
                
                font.DrawText(FormatStr("Volume: %d%%",song.GetVolume()),text[3]);

                engine->ClearDisplay();    //clear screen
                for(int i=0; i < 4; i++)
                    text[i].Draw(0,i*50);
                engine->Update();    //update the screen
            }
        } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
    }
}

int main(int argc, char *argv[])
{
    if(Initialize())
        Test();
    return 0;
}
