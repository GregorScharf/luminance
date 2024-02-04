#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "glad.h"
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

SDL_Renderer* engine::MainProcess::renderer;
engine::FrameHandle engine::MainProcess::Time;
std::vector<int> engine::MainProcess::data;

using namespace engine;

#endif