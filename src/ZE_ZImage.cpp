/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZImage.cpp
    \brief Source file for ZImage.

    Implementation of ZImage, the Image class for ZEngine.
    <br>$Id: ZE_ZImage.cpp,v 1.48 2003/10/11 16:21:50 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZImage.h"

namespace ZE
{

ZImage::ZImage() : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    Release();
}

ZImage::ZImage(const ZImage &rhs) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(rhs.Alpha())
{
    OpenFromImage(rhs.Surface(),0,0,(Sint16)rhs.Width(),(Sint16)rhs.Height());
}

ZImage::ZImage(std::string filename) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    Open(filename);
}

ZImage::ZImage(SDL_Surface *surface) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    Attach(surface);
}

ZImage::ZImage(SDL_Surface *img, Sint16 x, Sint16 y, Sint16 w, Sint16 h) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    OpenFromImage(img,x,y,w,h);
}

ZImage::ZImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h) : 
    rEngine(ZEngine::GetInstance()),
    rImage(NULL),
    rAlpha(255)
{
    OpenFromImage(img.Surface(),x,y,w,h);   //call SDL_Surface* version instead of taking the long way
}

ZImage::~ZImage()
{
    Release();
}

void ZImage::Open(std::string filename)
{
    SDL_Surface *image;

#ifdef USE_SDL_IMAGE
    image = IMG_Load(filename.c_str());
#else
    image = SDL_LoadBMP(filename.c_str());
#endif    //USE_SDL_IMAGE

    if(!image)
        rEngine->ReportError(ZERR_LOAD_IMAGE,filename);
    else
        Attach(image);
}

void ZImage::OpenFromZip(std::string zipname, std::string filename)
{
    SDL_Surface *image=NULL;
    SDL_RWops *rw;

    rw = RWFromZip(zipname,filename);

    if(rw)
    {
#ifdef USE_SDL_IMAGE
        image = IMG_Load_RW(rw,0);
#else
        image = SDL_LoadBMP_RW(rw,0);
#endif    //USE_SDL_IMAGE
        delete []rw->hidden.mem.base;   //must free buffer
        SDL_FreeRW(rw);
    }

    if(!image)
        rEngine->ReportError(ZERR_LOAD_IMAGE,FormatStr("%s in %s archive",filename.c_str(),zipname.c_str()));
    else
        Attach(image);
}

void ZImage::OpenFromImage(SDL_Surface *image, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
    SDL_Surface *screen = rEngine->Display();
    SDL_Surface *cutImg = NULL;
    SDL_Rect rect;
    SDL_VideoInfo *videoInfo;

    //either set hardware or software surface//
    videoInfo = const_cast<SDL_VideoInfo*>(SDL_GetVideoInfo());

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(!image)
        rEngine->ReportError(ZERR_NOIMAGE,"OpenFromImage");

    cutImg = SDL_CreateRGBSurface(0, rect.w, rect.h, rEngine->DisplayDepth(),
        screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if(!cutImg)
        rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_CreateRGBSurface failed in ZImage::OpenFromImage: %s.",SDL_GetError()));

    SDL_BlitSurface(image,&rect,cutImg,NULL);
    Attach(cutImg);
}

void ZImage::OpenFromImage(const ZImage &img, Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
    OpenFromImage(img.Surface(),x,y,w,h);
}

#if (GFX_BACKEND == ZE_OGL)

//attach is really the core of ZImage, everything calls it, it converts SDL_Surface->OpenGL Texture->ZImage
void ZImage::Attach(SDL_Surface *surface)
{
    GLfloat coord[4];

	Release();		//avoid most user inflicted memory leaks associated with ZImage

    if(surface)
    {
        SDL_Surface *temp = SDL_DisplayFormatAlpha(surface); //TTF_RenderTextBlended relys on this
        if(temp) //if conversion succeeds, free old surface
        {
            FreeImage(surface);
            surface = temp;
        }
        else    //can't convert, leave surface as is
        {
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_DisplayFormatAlpha failed in ZImage::Attach: %s",SDL_GetError()));
        }
    
        rWidth = static_cast<float>(surface->w);
        rHeight = static_cast<float>(surface->h);
        rTexID = SDL_GL_LoadTexture(surface,coord); //major helper, not written by me, from libsdl.org
        rTexMinX = coord[0];
        rTexMinY = coord[1];
        rTexMaxX = coord[2];
        rTexMaxY = coord[3];
        rImage = surface;
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"Attach");
}

void ZImage::Reload()
{
    //this little hack helps to reload images to OpenGL surfaces after loss
    SDL_Surface *temp = rImage;
    rImage = NULL;  
    Attach(temp);
}

void ZImage::Release()
{
    //set everything back the way it came
    if(glIsTexture(rTexID))
        glDeleteTextures(1,&rTexID);
    rTexMinX = rTexMinY = rTexMaxX = rTexMaxY = 0.0f;
    rTexID = 0;
    rWidth = rHeight = 0;
    FreeImage(rImage);
}

void ZImage::SetAlpha(Uint8 alpha)
{
    rAlpha = alpha;
}

void ZImage::SetColorKey(Uint8 red, Uint8 green, Uint8 blue)
{
    Uint32 color;

    if(rImage)
    {
        color = SDL_MapRGB(rImage->format,red,green,blue);
        if(SDL_SetColorKey(rImage, SDL_SRCCOLORKEY, color) < 0)
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_SetColorKey failed in ZImage::SetColorKey: %s",SDL_GetError()));
        else
            Reload(); //do the reattach hack, this gets a new OpenGL surface for the same image
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"SetColorKey");
}

void ZImage::Draw(int x, int y) const
{
    Draw(static_cast<float>(x),static_cast<float>(y));
}

void ZImage::DrawClipped(int x, int y, ZRect clipRect) const
{
    DrawClipped(static_cast<float>(x),static_cast<float>(y),clipRect);
}

void ZImage::Draw(float x, float y) const
{
    glColor4ub(255,255,255,rAlpha); //sets the color correctly
    Bind();
    glBegin(GL_TRIANGLE_STRIP); //triangle strips, speedier?
        glTexCoord2f(rTexMinX,rTexMinY);    glVertex2f(x,y);
        glTexCoord2f(rTexMaxX,rTexMinY);    glVertex2f(x+rWidth,y);
        glTexCoord2f(rTexMinX,rTexMaxY);    glVertex2f(x,y+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY);    glVertex2f(x+rWidth,y+rHeight);
    glEnd();
    glColor4ub(255,255,255,255);    //be responsible, return to standard color state
}

void ZImage::Draw(float x, float y, Uint8 vc[]) const
{
    Bind();
    glBegin(GL_TRIANGLE_STRIP); //triangle strips, speedier?
        glTexCoord2f(rTexMinX,rTexMinY); glColor4ub(vc[0],vc[1],vc[2],vc[3]); glVertex2f(x,y);
        glTexCoord2f(rTexMaxX,rTexMinY); glColor4ub(vc[4],vc[5],vc[6],vc[7]); glVertex2f(x+rWidth,y);
        glTexCoord2f(rTexMinX,rTexMaxY); glColor4ub(vc[12],vc[13],vc[14],vc[15]); glVertex2f(x,y+rHeight);  //12-15 here to keep counterclockwise
        glTexCoord2f(rTexMaxX,rTexMaxY); glColor4ub(vc[8],vc[9],vc[10],vc[11]); glVertex2f(x+rWidth,y+rHeight);
    glEnd();
    glColor4ub(255,255,255,255);    //be responsible, return to standard color state
}

void ZImage::DrawRotated(int x, int y, float angle) const
{
    DrawRotated(static_cast<float>(x),static_cast<float>(y),angle);
}

void ZImage::DrawRotated(float x, float y, float angle) const
{
    //center point
    float cX,cY; 
    cX = rWidth/2.0f;
    cY = rHeight/2.0f;

    glPushMatrix();
    glTranslatef(x+cX,y+cY,0);  //translate to center
    glRotatef(angle,0,0,1.0f);  //rotate on z axis, to keep x&y parallel to 2D plane
    glColor4ub(255,255,255,rAlpha); 
    Bind(); 
    //draw is modified to be based around center//
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(rTexMinX,rTexMinY);    glVertex2f(-cX,-cY);
        glTexCoord2f(rTexMaxX,rTexMinY);    glVertex2f(-cX+rWidth,-cY);
        glTexCoord2f(rTexMinX,rTexMaxY);    glVertex2f(-cX,-cY+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY);    glVertex2f(-cX+rWidth,-cY+rHeight);
    glEnd();
    glPopMatrix();
}

void ZImage::DrawRotated(float x, float y, float angle, Uint8 vc[]) const
{
    //center point
    float cX,cY; 
    cX = rWidth/2.0f;
    cY = rHeight/2.0f;

    glPushMatrix();
    glTranslatef(x+cX,y+cY,0);  //translate to center
    glRotatef(angle,0,0,1.0f);  //rotate on z axis, to keep x&y parallel to 2D plane
    Bind(); 
    //draw is modified to be based around center//
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(rTexMinX,rTexMinY); glColor4ub(vc[0],vc[1],vc[2],vc[3]); glVertex2f(-cX,-cY);
        glTexCoord2f(rTexMaxX,rTexMinY); glColor4ub(vc[4],vc[6],vc[6],vc[7]); glVertex2f(-cX+rWidth,-cY);
        glTexCoord2f(rTexMinX,rTexMaxY); glColor4ub(vc[12],vc[13],vc[14],vc[15]); glVertex2f(-cX,-cY+rHeight);
        glTexCoord2f(rTexMaxX,rTexMaxY); glColor4ub(vc[8],vc[9],vc[10],vc[11]); glVertex2f(-cX+rWidth,-cY+rHeight);
    glEnd();
    glPopMatrix();
}

void ZImage::DrawClipped(float x, float y, ZRect clipRect) const
{
    ZRect imgRect(x,y,rWidth,rHeight);

    if(clipRect.Contains(imgRect))
    {
        Draw(x,y);
    }
    else if(clipRect.Intersects(imgRect))
    {
        //This is some pretty complex code, it is broken down in 4 steps. 

        //Step 1: The intersection rectangle (inRect) is compared to the image rectangle and the overlapping area is found. 
        ZRect inRect = clipRect.Intersection(imgRect); 

        //Step 2: The portion of the image that needs to be drawn is being mapped to triangle strips the same size as the intersection
        //        of the clipping and image rectangles and then transformed to texture coordinates via xScale and yScale.
        //        (double is used for needed precision when dealing with the scaling)
        double xScale = (rTexMaxX - rTexMinX)*rWidth;   //texCoordWidth/imgWidth
        double yScale = (rTexMaxY - rTexMinY)*rHeight;  //texCoordHeight/imgHeight
        double nx = rTexMinX + (inRect.X()-x)/xScale;    //cut off left side
        double ny = rTexMinY + (inRect.Y()-y)/yScale;    //cut off top
        double nw = nx + inRect.Width()/xScale;      //cut off right side
        double nh = ny + inRect.Height()/yScale;     //cut off bottom

        glColor4ub(255,255,255,rAlpha);
        Bind();
        glBegin(GL_TRIANGLE_STRIP);
            //Step 3: The texture coords are modified to only specify the portion of the texture which falls within the clipping rect.
            //Step 4: The vertices are changed to the sides of the clipping rectangle in glVertex2f.
            glTexCoord2d(nx,ny);  glVertex2f(inRect.Left(),inRect.Top());
            glTexCoord2d(nw,ny);  glVertex2f(inRect.Right(),inRect.Top());
            glTexCoord2d(nx,nh);  glVertex2f(inRect.Left(),inRect.Bottom());
            glTexCoord2d(nw,nh);  glVertex2f(inRect.Right(),inRect.Bottom());
        glEnd();
        glColor4ub(255,255,255,255);    //be responsible, return to standard color state
    }
    //otherwise it doesn't contain nor intersect, so nothing should be drawn
}

void ZImage::DrawClipped(float x, float y, ZRect clipRect, Uint8 vc[]) const
{
    ZRect imgRect(x,y,rWidth,rHeight);

    if(clipRect.Contains(imgRect))
    {
        Draw(x,y);
    }
    else if(clipRect.Intersects(imgRect))
    {
        //This is some pretty complex code, it is broken down in 4 steps. 

        //Step 1: The intersection rectangle (inRect) is compared to the image rectangle and the overlapping area is found. 
        ZRect inRect = clipRect.Intersection(imgRect); 

        //Step 2: The portion of the image that needs to be drawn is being mapped to triangle strips the same size as the intersection
        //        of the clipping and image rectangles and then transformed to texture coordinates via xScale and yScale.
        //        (double is used for needed precision when dealing with the scaling)
        double xScale = (rTexMaxX - rTexMinX)*rWidth;   //texCoordWidth/imgWidth
        double yScale = (rTexMaxY - rTexMinY)*rHeight;  //texCoordHeight/imgHeight
        double nx = rTexMinX + (inRect.X()-x)/xScale;    //cut off left side
        double ny = rTexMinY + (inRect.Y()-y)/yScale;    //cut off top
        double nw = nx + inRect.Width()/xScale;      //cut off right side
        double nh = ny + inRect.Height()/yScale;     //cut off bottom

        Bind();
        glBegin(GL_TRIANGLE_STRIP);
            //Step 3: The texture coords are modified to only specify the portion of the texture which falls within the clipping rect.
            //Step 4: The vertices are changed to the sides of the clipping rectangle in glVertex2f.
            glTexCoord2d(nx,ny); glColor4ub(vc[0],vc[1],vc[2],vc[3]); glVertex2f(inRect.Left(),inRect.Top());
            glTexCoord2d(nw,ny); glColor4ub(vc[4],vc[5],vc[6],vc[7]); glVertex2f(inRect.Right(),inRect.Top());
            glTexCoord2d(nx,nh); glColor4ub(vc[12],vc[13],vc[14],vc[15]); glVertex2f(inRect.Left(),inRect.Bottom());
            glTexCoord2d(nw,nh); glColor4ub(vc[8],vc[9],vc[10],vc[11]); glVertex2f(inRect.Right(),inRect.Bottom());
        glEnd();
        glColor4ub(255,255,255,255);    //be responsible, return to standard color state
    }
    else    //doesn't contain nor intersect
    {
        //draw nothing
    }
}

void ZImage::Flip(bool horizontal, bool vertical)
{
    //all that a flip does is invert the Min/Max coordinates
    if(horizontal)
        std::swap(rTexMinX,rTexMaxX);
    if(vertical)
        std::swap(rTexMinY,rTexMaxY);
}

//stretching and resizing is very inexpensive, done via variables
void ZImage::Stretch(float xFactor, float yFactor)
{
    rWidth = xFactor*rWidth;
    rHeight = yFactor*rHeight;
}

void ZImage::Resize(float width, float height)
{
    rWidth = width;
    rHeight = height;
}

//this is available for other uses of ZEngine
void ZImage::Bind() const
{
    if(rTexID)
        glBindTexture(GL_TEXTURE_2D, rTexID);
    else
        rEngine->ReportError(ZERR_NOIMAGE,"Bind");
        
}

bool ZImage::IsLoaded() const
{
    return glIsTexture(rTexID) == GL_TRUE;
}

#elif (GFX_BACKEND == ZE_SDL)

void ZImage::Attach(SDL_Surface *surface)
{
    Release();
    
    if(surface)
    {
        SDL_Surface *temp = SDL_DisplayFormatAlpha(surface); //TTF_RenderTextBlended relys on this
        if(temp) //if conversion succeeds, free old surface
        {
            FreeImage(surface);
            surface = temp;
        }
        else    //can't convert, leave surface as is
        {
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_DisplayFormatAlpha failed in ZImage::Attach: %s",SDL_GetError()));
        }

        rImage = surface;
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"Attach");
}

void ZImage::Reload()
{
    //currently a no-op
}

void ZImage::Release()
{
    FreeImage(rImage);
}

void ZImage::SetAlpha(Uint8 alpha)
{
    rAlpha = alpha;
    if(rImage)
    {
        if(SDL_SetAlpha(rImage, SDL_SRCALPHA, alpha) < 0)
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_SetAlpha failed in ZImage::SetAlpha: %s",SDL_GetError()));
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"SetAlpha");
}

void ZImage::SetColorKey(Uint8 red, Uint8 green, Uint8 blue)
{
    Uint32 color;

    if(rImage)
    {
        color = SDL_MapRGBA(rImage->format,red,green,blue,255);
        if(SDL_SetColorKey(rImage, SDL_RLEACCEL|SDL_SRCCOLORKEY, color) < 0)
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_SetColorKey failed in ZImage::SetColorKey: %s",SDL_GetError()));
        //surface conversion//
        SDL_Surface *temp = rImage;
        rImage = SDL_DisplayFormatAlpha(temp); //TTF_RenderTextBlended relys on this
        if(rImage)
        {
            FreeImage(temp);
        }
        else    //can't convert
        {
            rEngine->ReportError(ZERR_SDL_INTERNAL,FormatStr("SDL_DisplayFormatAlpha failed in ZImage::SetColorKey: %s",SDL_GetError()));
            rImage = temp;
        }
    }
    else
        rEngine->ReportError(ZERR_NOIMAGE,"SetColorKey");
}

void ZImage::Draw(int x, int y) const
{
    SDL_Rect rect;
    rect.x = static_cast<Sint16>(x);
    rect.y = static_cast<Sint16>(y);
    SDL_BlitSurface(rImage, NULL, rEngine->Display(), &rect);
}

void ZImage::DrawClipped(int x, int y, ZRect clipRect) const
{
    ZRect img(static_cast<Sint16>(x),static_cast<Sint16>(y),static_cast<Sint16>(rImage->w),static_cast<Sint16>(rImage->h));
    SDL_Rect inRect,imgRect;
    
    imgRect = inRect = clipRect.Intersection(img).SDLrect();
    inRect.x -= x;
    inRect.y -= y;
    
    SDL_BlitSurface(rImage, &inRect, rEngine->Display(), &imgRect);
}

bool ZImage::IsLoaded() const
{
    return rImage ? true : false;
}

#endif //GFX_BACKEND

SDL_Surface* ZImage::Surface() const
{
    return rImage;
}

#if (GFX_BACKEND == ZE_OGL)

float ZImage::Width() const
{
    return rWidth;
}

float ZImage::Height() const
{
    return rHeight;
}

#elif (GFX_BACKEND == ZE_SDL)

int ZImage::Width() const
{
    return rImage->w;
}

int ZImage::Height() const
{
    return rImage->h;
}

#endif //GFX_BACKEND

Uint8 ZImage::Alpha() const
{
    return rAlpha;
}

}
