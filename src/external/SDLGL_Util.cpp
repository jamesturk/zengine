/*This code comes from testgl.c which is part of the SDL source distribution.
    Available at http://libsdl.org/
*/

#include "external/SDLGL_Util.h"

int power_of_two(int input)
{
    int value = 1;

    while(value < input) 
    {
        value <<= 1;
    }
    return value;
}

GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
{
    GLuint texture;
    int w, h;
    SDL_Surface *image;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8  saved_alpha;

    /* Use the surface width and height expanded to powers of 2 */
    w = power_of_two(surface->w);
    h = power_of_two(surface->h);
    texcoord[0] = 0.0f; //min X
    texcoord[1] = 0.0f; //min Y
    texcoord[2] = (GLfloat)surface->w / w;  //max X
    texcoord[3] = (GLfloat)surface->h / h;  //max Y

    image = SDL_CreateRGBSurface(
        SDL_SWSURFACE,
        w, h,
        32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
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
    if ( image == NULL ) {
            return 0;
    }

    /* Save the alpha blending attributes */
    saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
            SDL_SetAlpha(surface, 0, 0);
    }

    /* Copy the surface into the GL texture image */
    area.x = 0;
    area.y = 0;
    area.w = static_cast<Sint16>(surface->w);
    area.h = static_cast<Sint16>(surface->h);
    SDL_BlitSurface(surface, &area, image, &area);

    /* Restore the alpha blending attributes */
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
            SDL_SetAlpha(surface, saved_flags, saved_alpha);
    }

    /* Create an OpenGL texture for the image */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,
                    0,
                    GL_RGBA16,
                    w, h,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    image->pixels);
    SDL_FreeSurface(image); /* No longer needed */

    return texture;
}
