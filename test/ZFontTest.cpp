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

    w = cfg.GetInt("ZFontTest","width",800);
    h = cfg.GetInt("ZFontTest","height",600);
    bpp = cfg.GetInt("ZFontTest","bpp",32);
    fs = cfg.GetBool("ZFontTest","fullscreen",false);
    title = cfg.GetString("ZFontTest","title","ZFont Test");

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    //Open and Setup all the Fonts and Create Images//
    ZImage text[5];
    ZFont almonte("data/almontew.ttf",48), axaxax("data/axaxax.ttf",32), betsy("data/betsy.ttf",64);
    almonte.SetColor(255,0,0);
    almonte.DrawText("This is the font test.",text[0]);
    axaxax.SetColor(0,255,255);
    axaxax.SetStyle(true,false,false);
    axaxax.DrawText("Fonts free from: ",text[1]);
    axaxax.SetStyle(false,true,true);
    axaxax.DrawText("http://larabiefonts.com/",text[2]);
    almonte.SetBGColor(0,0,128);
    almonte.SetColor(0,0,255);
    almonte.SetStyle(false,true,false);
    almonte.DrawShadedText("Shaded, italic, bold and underlined tested. ",text[3]);
    betsy.SetColor(255,255,255);
    betsy.DrawText("Font test successful.",text[4]);

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();
        if(engine->KeyIsPressed(SDLK_ESCAPE))
            engine->RequestQuit();

        engine->Clear();    //clear screen
        //draw the images//
        for(int i=0; i <= 4; i++)
            text[i].Draw(10.0f*i,50.0f*i);
        engine->Update();    //update the screen

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
