#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Frames.hpp"
#include "Images.hpp"
#include "MainProcess.hpp"
#include "MonoBehaviour.hpp"
#include "Moving_Object.hpp"
#include "enums.hpp"
#include "glad.h" // if this isn't first it will cause a segmentation fault during compilation, I don't know why and i am scared of it
#include "init.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION // required because of black magic fuckery
#include "stb_image.hpp"

SDL_Renderer *engine::MainProcess::renderer;
engine::FrameHandle engine::MainProcess::Time;
std::vector<int> engine::MainProcess::data;

using namespace engine;

#endif
