/*This code comes from testgl.c which is part of the SDL source distribution.
    Available at http://libsdl.org/
*/
#ifndef __sdlgl_h__
#define __sdlgl_h__

#include "ZE_Includes.h"

#if (GFX_BACKEND == ZE_OGL)
int power_of_two(int input);
GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord);
#endif

#endif //__sdlgl_h__
