/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*$Id: ZImageTest.cpp,v 1.24 2003/09/09 02:45:58 cozman Exp $*/

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
    float angle=0.0f,movDelta;
    Uint8 alpha=128,alphaDelta=1;

    //Open and Setup all the Images//
    SDL_Surface *temp;
    ZImage image1,image2,image3,image4,textImage;
    ZFont font("data/almontew.ttf",30);
    ZRect clipRect(400,300,30,30);

    font.SetColor(0,255,0);
    font.SetBGColor(0,0,255);

    temp = SDL_LoadBMP("data/test02.bmp");    //this is a separate surface
    image1.Attach(temp);    //this attaches the surface into itself
    image2.Open("data/test01.bmp");
    image3.OpenFromImage(image2.Surface(),5,5,20,20);
    image4.Open("data/test02.bmp");
    temp = NULL;    //and temp will now be controlled and freed by image1
    image1.SetColorKey(255,0,255);
    image2.SetColorKey(255,0,255);
#if (GFX_BACKEND == ZE_OGL)
    image4.Resize(400,300);
    image4.Flip(true,false);
#endif
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

            //movement//
            movDelta = static_cast<float>(engine->GetFrameTime()*30);
            if(engine->KeyIsPressed(SDLK_LEFT))
                clipRect.MoveRel(-movDelta,0);
            if(engine->KeyIsPressed(SDLK_RIGHT))
                clipRect.MoveRel(movDelta,0);
            if(engine->KeyIsPressed(SDLK_UP))
                clipRect.MoveRel(0,-movDelta);
            if(engine->KeyIsPressed(SDLK_DOWN))
                clipRect.MoveRel(0,movDelta);
            if(engine->KeyIsPressed(SDLK_EQUALS))
            {
                clipRect.MoveRel(-1,-1);
                clipRect.ResizeRel(2,2);
            }
            if(engine->KeyIsPressed(SDLK_MINUS))
            {
                clipRect.MoveRel(1,1);
                clipRect.ResizeRel(-2,-2);
            }

            if(engine->KeyIsPressed(SDLK_s))
                engine->ToggleFullscreen();
            if(engine->KeyIsPressed(SDLK_ESCAPE))
                engine->RequestQuit();

            engine->Clear();    //clear screen
            //draw the images//
            alpha += alphaDelta;
            if(alpha ==255 || alpha == 0)
                alphaDelta *= -1;
            image1.SetAlpha(alpha);
            image1.Draw(0,0);

#if (GFX_BACKEND == ZE_OGL)
            image2.DrawRotated(100,0,angle);
            if(++angle > 360)
                angle = 0.0f;
#elif (GFX_BACKEND == ZE_SDL)
            image2.Draw(100,0);
#endif

            image3.Draw(200,0);
            image4.DrawClipped(400,300,clipRect);
            textImage.Draw(0,100);
            engine->Update();    //update the screen
        }
        else
            engine->Delay(10);

    } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
}

int ZE_main(int argc, char *argv[])
{
    if(Initialize())
        Test();
    return 0;
}
