/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                  Copyright (C) 2002-2004 James Turk

              ZEngine is Licensed under a BSD-style license.
This example file is in the public domain, it may be used with no restrictions.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

// $Id: ZImageTest.cpp,v 1.31 2004/01/13 23:56:28 cozman Exp $

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

    w = cfg.GetInt("ZImageTest","width",800);
    h = cfg.GetInt("ZImageTest","height",600);
    bpp = cfg.GetInt("ZImageTest","bpp",32);
    fs = cfg.GetBool("ZImageTest","fullscreen",true);
    title = cfg.GetString("ZImageTest","title","ZImage Test");

    engine->SetResourceFile("resources.zrf");
    engine->InitErrorLog();
    return engine->CreateDisplay(w,h,bpp,fs,title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();
    float angle=0.0f,movDelta;
    float alpha=128.0f,alphaDelta=15.0f;

    //Open and Setup all the Images//
    ZImage image1,image2,image3,image4,textImage;
    ZFont font("data/almontew.ttf",30);
    ZRect clipRect(400,300,30,30);

    font.SetColor(0,255,0);
    font.SetBGColor(0,0,255);

    engine->InitErrorLog();
    engine->ReportError(ZERR_CRITICAL,"This is a critical test error!!! Something has gone seriously wrong!");
    engine->ReportError(ZERR_DEPRECIATED,"This is a test of a depreciated feature.");
    engine->ReportError(ZERR_ERROR,"This is a normal error, but only a test.");
    engine->ReportError(ZERR_NOTE,"Relax, this is just a test note.");
    engine->ReportError(ZERR_VERBOSE,"This test wouldn't show up if verbose was off.");
    engine->ReportError(ZERR_WARNING,"This is a test warning, not critical but not verbose either.");
    
    image1.OpenFromZip("data/data.zip","test02.bmp");
    image1.SetColorKey(255,0,255);
    image2.Open("data/test01.bmp");
    image2.SetColorKey(255,0,255);
    image3.OpenFromImage(image2.Surface(),5,5,20,20);
    image4.OpenFromZRF("rainbow");

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
                image4.Reload();
                textImage.Reload();
                engine->SetReloadNeed(false);   //very important for speed, without this you'd be reloading every frame
            }

            //movement//
            movDelta = static_cast<float>(engine->GetFrameSpeed()*30);
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

            engine->ClearDisplay();    //clear screen
            //draw the images//
            alpha += static_cast<float>(alphaDelta*engine->GetFrameSpeed());
            if(alpha >= 255 || alpha <= 0)
                alphaDelta *= -1.0f;
            image1.SetAlpha(static_cast<Uint8>(alpha));
            image1.Draw(0,0);

#if (GFX_BACKEND == ZE_OGL)
            image2.DrawRotated(100,0,angle);
            angle += static_cast<float>(150*engine->GetFrameSpeed());
            if(angle > 360)
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

int main(int argc, char *argv[])
{
    if(Initialize())
        Test();
    return 0;
}
