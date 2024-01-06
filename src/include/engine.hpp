#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "enums.hpp"
#include "init.hpp"
#include "MonoBehaviour.hpp"
#include "MainProcess.hpp"
#include "Frames.hpp"

SDL_Renderer* engine::MainProcess::renderer;
engine::FrameHandle engine::MainProcess::Time;
std::vector<int> engine::MainProcess::data;

#endif