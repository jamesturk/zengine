/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

// $Id: ZMouseTest.cpp,v 1.23 2004/01/13 23:56:28 cozman Exp $

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

    w = cfg.GetInt("ZMouseTest","width",800);
    h = cfg.GetInt("ZMouseTest","height",600);
    bpp = cfg.GetInt("ZMouseTest","bpp",32);
    fs = cfg.GetBool("ZMouseTest","fullscreen",false);
    title = cfg.GetString("ZMouseTest","title","ZMouse Test");

    engine->SetResourceFile("resources.zrf");
    engine->InitErrorLog();
    return engine->CreateDisplay(w,h,bpp,fs,title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    //Open and Setup all the Images//
    ZImage text[3], cursor("data/cursor.bmp");
    ZFont font;
    SDL_Rect textRect;
    
    font.OpenFromZRF("default");

    engine->HideCursor();
    cursor.SetColorKey(255,0,255);

    font.SetColor(0,255,0);
    font.SetBGColor(0,0,255);
    font.DrawText("Mouse Test",text[0]);
    font.DrawShadedText("Mouse Test",text[1]);
    textRect.x = textRect.y = 100;
    textRect.w = font.CalcStringWidth("Mouse Test");
    textRect.h = font.CalcStringHeight("Mouse Test");

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();

        if(engine->IsActive())
        {
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();

            //show where mouse is (clicked or not)//
            if(engine->RButtonPressed())
                font.DrawText(FormatStr("Right button clicked at %d,%d",engine->MouseX(),engine->MouseY()),text[2]);
            else if(engine->LButtonPressed())
                font.DrawText(FormatStr("Left button clicked at %d,%d",engine->MouseX(),engine->MouseY()),text[2]);
            else if(engine->MButtonPressed())
                font.DrawText(FormatStr("Middle button clicked at %d,%d",engine->MouseX(),engine->MouseY()),text[2]);
            else
                font.DrawText(FormatStr("Mouse at %d,%d",engine->MouseX(),engine->MouseY()),text[2]);
                

            engine->ClearDisplay();    //clear screen
            //draw the images//
            text[engine->MouseInRect(textRect)].Draw(100,100);
            text[2].Draw(0,0);
            cursor.Draw(engine->MouseX()-8,engine->MouseY()-8);

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
