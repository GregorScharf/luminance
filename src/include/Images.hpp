#ifndef IMAGES_HPP
#define IMAGES_HPP

#include "glad.h"
#include <SDL2/SDL.h>

namespace engine
{

    typedef SDL_Surface Image;

    Image *loadImage(const char *path)
    {
        Image *image;
        image = SDL_LoadBMP(path);
        return image;
    }

    int destroyImage(Image *image)
    {
        if (image == NULL)
        {
            SDL_Log("Image is NULL");
            return -1;
        }
        SDL_FreeSurface(image);
        return 0;
    }

    typedef SDL_Texture Texture;

    Texture *createTextureFromImage(SDL_Renderer *renderer, Image *image)
    {
        Texture *texture;
        texture = SDL_CreateTextureFromSurface(renderer, image);
        return texture;
    }

    int destroyTexture(Texture *texture)
    {
        if (texture == NULL)
        {
            SDL_Log("Texture is NULL");
            return -1;
        }
        SDL_DestroyTexture(texture);
        return 0;
    }
}

#endif