/*This code derived from testgl.c which is part of the SDL source distribution.
    Available at http://libsdl.org/
*/

#include "external/SDLGL_Util.h"

#if (GFX_BACKEND == ZE_OGL)

//finds next largest power of two, needed for GL textures
int power_of_two(int input)
{
    int value = 1;

    while(value < input) //texture coord must be >= input
        value <<= 1;    //value <<= 1 is the same as value *= 2
    return value;
}

GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
{
    GLuint texture;
    int w, h;
    SDL_Surface *temp;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8  saved_alpha;

    //expand width and height to nearest powers of 2
    w = power_of_two(surface->w);
    h = power_of_two(surface->h);
    texcoord[0] = 0.0f; //min X
    texcoord[1] = 0.0f; //min Y
    texcoord[2] = (GLfloat)surface->w / w;  //max X
    texcoord[3] = (GLfloat)surface->h / h;  //max Y

    temp = SDL_CreateRGBSurface(
        SDL_SWSURFACE,
        w, h,
        32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN //endian specific color masks
        0x000000FF, 
        0x0000FF00, 
        0x00FF0000, 
        0xFF000000
#else
        0xFF000000,
        0x00FF0000, 
        0x0000FF00, 
        0x000000FF
#endif
    );
    if(!temp)  //failure in CreateRGBSurface
        return 0;

    //save alpha
    saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
        SDL_SetAlpha(surface, 0, 0);

    //copy surface (do not alter passed surface to allow this function to be used in special situations)
    area.x = 0;
    area.y = 0;
    area.w = static_cast<Sint16>(surface->w);
    area.h = static_cast<Sint16>(surface->h);
    SDL_BlitSurface(surface, &area, temp, &area);

    //restore saved alpha
    if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
        SDL_SetAlpha(surface, saved_flags, saved_alpha);

    //create the OpenGL texture
    glGenTextures(1, &texture); 
    //setup texture parmaters
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
    SDL_FreeSurface(temp); //temp surface no longer needed

    return texture;
}

#endif //GFX_BACKEND == OGL
