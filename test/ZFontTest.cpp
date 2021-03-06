/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

// $Id: ZFontTest.cpp,v 1.21 2004/01/13 23:56:28 cozman Exp $

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
    string title;

    w = cfg.GetInt("ZFontTest","width",800);
    h = cfg.GetInt("ZFontTest","height",600);
    bpp = cfg.GetInt("ZFontTest","bpp",32);
    fs = cfg.GetBool("ZFontTest","fullscreen",false);
    title = cfg.GetString("ZFontTest","title","ZFont Test");

    engine->SetResourceFile("resources.zrf");
    engine->InitErrorLog();
    return engine->CreateDisplay(w,h,bpp,fs,title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    //Open and Setup all the Fonts and Create Images//
    ZImage text[6];
    ZFont almonte, axaxax("data/axaxax.ttf",32), betsy;
    almonte.OpenFromZRF("default");
    almonte.Resize(48);
    betsy.OpenFromZip("data/data.zip","betsy.ttf",20);
    almonte.SetColor(255,0,0,128);
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
        if(engine->IsActive())
        {
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();
            betsy.DrawText(FormatStr("FPS: %.2f",engine->GetFramerate()),text[5]);

            engine->ClearDisplay();    //clear screen
            //draw the images//
            for(int i=0; i <= 5; i++)
                text[i].Draw(10*i,50*i);
            engine->Update();    //update the screen
        }

    } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
}

int main(int argc, char *argv[])
{
    if(Initialize())
        Test();
    return 0;
}
