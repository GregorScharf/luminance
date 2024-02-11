#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "glad.h" // if this isn't first it will cause a segmentation fault during compilation, I don't know why and i am scared of it
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "enums.hpp"
#include "init.hpp"
#include "MonoBehaviour.hpp"
#include "MainProcess.hpp"
#include "Frames.hpp"
#include "Moving_Object.hpp"
#include "Images.hpp"

#define STB_IMAGE_IMPLEMENTATION // required because of black magic fuckery
#include "stb_image.hpp"


SDL_Renderer* engine::MainProcess::renderer;
engine::FrameHandle engine::MainProcess::Time;
std::vector<int> engine::MainProcess::data;

using namespace engine;

#endif