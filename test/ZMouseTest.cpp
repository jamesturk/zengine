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

    w = cfg.GetInt("ZMouseTest","width",800);
    h = cfg.GetInt("ZMouseTest","height",600);
    bpp = cfg.GetInt("ZMouseTest","bpp",32);
    fs = cfg.GetBool("ZMouseTest","fullscreen",false);
    title = cfg.GetString("ZMouseTest","title","ZMouse Test");

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();

    //Open and Setup all the Images//
    ZImage text[3], cursor("data/cursor.bmp");
    ZFont font("data/almontew.ttf",30);
    SDL_Rect textRect;
    
    engine->HideCursor();
    cursor.SetColorKey(255,0,255);

    font.SetColor(0,255,0);
    font.SetBGColor(0,0,255);
    font.DrawText("Mouse Test",text[0]);
    font.DrawShadedText("Mouse Test",text[1]);
    textRect.x = textRect.y = 100;
    textRect.w = font.StringWidth("Mouse Test");
    textRect.h = font.StringHeight("Mouse Test");

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();
        if(engine->KeyIsPressed(SDLK_s))
        {
            //code to toggle screen//
            engine->SetupDisplay(engine->Width(),engine->Height(),engine->BPP(),!engine->IsFullscreen());
            engine->CreateDisplay("ZEngine Mouse Test");
        }
        if(engine->KeyIsPressed(SDLK_ESCAPE))
            engine->RequestQuit();

        //show where mouse is (clicked or not)//
        if(engine->RButtonPressed())
            font.DrawText(FormatStr("Right button clicked at %d,%d",engine->MouseX(),engine->MouseY()),text[2]);
        else if(engine->LButtonPressed())
            font.DrawText(FormatStr("Left button clicked at %d,%d",engine->MouseX(),engine->MouseY()),text[2]);
        else
            font.DrawText(FormatStr("Mouse at %d,%d",engine->MouseX(),engine->MouseY()),text[2]);
            

        engine->Clear();    //clear screen
        //draw the images//
        text[engine->MouseInRect(&textRect)].Draw(100,100);
        text[2].Draw(0,0);
        cursor.Draw(engine->MouseX()-8,engine->MouseY()-8);

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
