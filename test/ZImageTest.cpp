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

    w = cfg.GetInt("ZImageTest","width",800);
    h = cfg.GetInt("ZImageTest","height",600);
    bpp = cfg.GetInt("ZImageTest","bpp",32);
    fs = cfg.GetBool("ZImageTest","fullscreen",true);
    title = cfg.GetString("ZImageTest","title","ZImage Test");

    engine->SetupDisplay(w,h,bpp,fs);
    engine->CreateDisplay(title);
}

void Test()
{
    ZEngine *engine = ZEngine::GetInstance();
    float angle=0.0f;

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
            engine->SetupDisplay(engine->Width(),engine->Height(),engine->BPP(),!engine->IsFullscreen());
            engine->CreateDisplay("ZImage Test");
            engine->SetReloadNeed(true);
        }
        if(engine->KeyIsPressed(SDLK_ESCAPE))
            engine->RequestQuit();

        engine->Clear();    //clear screen
        //draw the images//
        image1.Draw(0,0);
        
        image2.DrawRotated(100,0,angle);
        if(++angle > 360)
            angle = 0.0f;

        image3.Draw(200,0);
        textImage.Draw(0,100);
        engine->Update();    //update the screen

    } while(!engine->QuitRequested());    //quit only when engine has encountered a quit request
}

int main(int argc, char **argv)
{
    ZEngine *engine = ZEngine::GetInstance();

    Initialize();
    //engine->InitPhysFS(argv[0]);    //remove this line if PhysFS is not available
    Test();

    ZEngine::ReleaseInstance();    //release engine instance
    return 0;
}
