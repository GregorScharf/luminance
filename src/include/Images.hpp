#ifndef IMAGES_HPP
#define IMAGES_HPP

#include "glad.h"
#include <SDL2/SDL.h>
#include "stb_image.hpp" 

namespace engine
{   

    const unsigned int rectangleIndecies[6] = {
        0, 1, 3,
        1, 2, 3
    };


    typedef struct Image{
        GLuint texture;
        float vertices[20];
    } Image;

    Image* loadBmp_toTexture(const char* path, float* vertices, size_t size_of_vertices){
        SDL_Surface* surface = SDL_LoadBMP(path);
        GLuint texture;
        Image* image = new Image;
        if(vertices == NULL){
            image->vertices[0] = -1.0f;
            image->vertices[1] = 1.0f;
            image->vertices[2] = 0.0f;
            image->vertices[3] = 0.0f;
            image->vertices[4] = 0.0f;
            image->vertices[5] = -1.0f;
            image->vertices[6] = -1.0f;
            image->vertices[7] = 0.0f;
            image->vertices[8] = 0.0f;
            image->vertices[9] = 1.0f;
            image->vertices[10] = 1.0f;
            image->vertices[11] = 0.0f;
            image->vertices[12] = 1.0f;
            image->vertices[13] = 0.0f;
            image->vertices[14] = 0.0f;
            image->vertices[15] = 1.0f;
            image->vertices[16] = 1.0f;
            image->vertices[17] = 0.0f;
            image->vertices[18] = 1.0f;
            image->vertices[19] = 1.0f;
        }

        else
        {
            for (size_t i = 0; i < size_of_vertices; i++)
            {
                image->vertices[i] = vertices[i];
            }
        }
        

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        SDL_FreeSurface(surface);

        return ;
    }

    void renderImageTexture(GLuint texture, float* vertices, size_t size){

    }

    void freeTexture(Image* Image){
        glDeleteTextures(1, &Image->texture);
        delete Image;
    }
}

#endif