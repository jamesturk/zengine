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

    w = cfg.GetInt("ZMusicTest","width",800);
    h = cfg.GetInt("ZMusicTest","height",600);
    bpp = cfg.GetInt("ZMusicTest","bpp",32);
    fs = cfg.GetBool("ZMusicTest","fullscreen",false);
    title = cfg.GetString("ZMusicTest","title","ZMusic Test");

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    ZMusic song("data/music.ogg");
    ZFont font("data/almontew.ttf",48);
    ZImage text[4];

    if(!song.IsLoaded())    //this executes if there is no music.ogg file
    {
        engine->SetupDisplay(800,70,32,false);
        engine->CreateDisplay("ZMusic Test");
        font.DrawText("Music.ogg does not exist, please read music.txt.",text[0]);
        text[0].Draw(0,0);
        engine->UpdateScreen();
        do
        {
            engine->CheckEvents();
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
            if(engine->KeyIsPressed(SDLK_s))
            {
                //code to toggle screen//
                engine->SetupDisplay(engine->Width(),engine->Height(),engine->BPP(),!engine->IsFullscreen());
                engine->CreateDisplay("ZMusic Test");
            }
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();
            if(engine->KeyIsPressed(SDLK_r))
                song.Rewind();
            if(engine->KeyIsPressed(SDLK_p))
                song.Pause();
            if(engine->KeyIsPressed(SDLK_u))
                song.Unpause();
            if(engine->KeyIsPressed(SDLK_f))
                song.Stop(5000);
            if(engine->KeyIsPressed(SDLK_h))
                song.Stop();
            if(engine->KeyIsPressed(SDLK_SPACE))
                song.Play();
            if(engine->KeyIsPressed(SDLK_UP))
                song.SetVolume(song.GetVolume()+1);
            if(engine->KeyIsPressed(SDLK_DOWN))
                song.SetVolume(song.GetVolume()-1);


            font.DrawText(FormatStr("Volume: %d",song.GetVolume()),text[3]);

            engine->Clear();    //clear screen
            for(int i=0; i < 4; i++)
                text[i].Draw(0,i*50);
            engine->UpdateScreen();    //update the screen
        } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
    }
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
