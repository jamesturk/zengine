/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*$Id: ZImageTest.cpp,v 1.16 2003/01/25 20:36:13 cozman Exp $*/

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
    string title;

    w = cfg.GetInt("ZImageTest","width",800);
    h = cfg.GetInt("ZImageTest","height",600);
    bpp = cfg.GetInt("ZImageTest","bpp",32);
    fs = cfg.GetBool("ZImageTest","fullscreen",true);
    title = cfg.GetString("ZImageTest","title","ZImage Test");
    rate = cfg.GetInt("ZImageTest","framerate",60);

    engine->SetupDisplay(w,h,bpp,fs);
    engine->SetDesiredFramerate(rate);
    return engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();
    float angle=0.0f;
    Uint8 alpha=128,alphaDelta=1;

    //Open and Setup all the Images//
    SDL_Surface *temp;
    ZImage image1, image2, image3, textImage;
    ZFont font("data/almontew.ttf",30);

    font.SetColor(0,255,0);
    font.SetBGColor(0,0,255);

    temp = SDL_LoadBMP("data/test02.bmp");    //this is a separate surface
    image1.Attach(temp);    //this attaches the surface into itself
    image2.Open("data/test01.bmp");
    image3.OpenFromImage(image2.Surface(),5,5,20,20);
    temp = NULL;    //and temp will now be controlled and freed by image1
    image1.SetColorKey(255,0,255);
    image2.SetColorKey(255,0,255);
    font.DrawShadedText("ZImage Test.",textImage);

    do
    {
        //In the active loop, check events first//
        engine->CheckEvents();

        if(engine->IsActive())
        {
            if(engine->ImagesNeedReload())
            {
                image1.Reload();
                image2.Reload();
                image3.Reload();
                textImage.Reload();
                engine->SetReloadNeed(false);   //very important for speed, without this you'd be reloading every frame
            }

            if(engine->KeyIsPressed(SDLK_s))
            {
                //code to toggle screen//
                engine->ToggleFullscreen();
            }
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();

            engine->Clear();    //clear screen
            //draw the images//
            alpha += alphaDelta;
            if(alpha ==255 || alpha == 0)
                alphaDelta *= -1;
            image1.SetAlpha(alpha);
            image1.Draw(0,0);

            
            image2.DrawRotated(100,0,angle);
            if(++angle > 360)
                angle = 0.0f;

            image3.Draw(200,0);
            textImage.Draw(0,100);
            engine->Update();    //update the screen
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
