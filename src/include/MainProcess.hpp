#include <SDL2/SDL.h>
#include <iostream>
#include "enums.hpp"
#include "init.hpp"
#include <vector>
#include "Frames.hpp"
#include "MonoBehaviour.hpp"

// i am so sorry for this
#ifndef MAINPROCESS_HPP
#define MAINPROCESS_HPP

std::vector<engine::MonoBehaviour *> engine::MonoBehaviour::process_updates;

namespace engine
{
    class MainProcess
    {
    private:
        SDL_Window *window;
        std::vector<MonoBehaviour *> _updates;
        static SDL_Renderer *renderer;
        bool running;
        void loop()
        {
            while (running)
            {
                Time.handle_start();
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        running = false;
                        break;
                    }
                }
                for (MonoBehaviour *processes : _updates)
                {
                    processes->event(&event);
                }
                const Uint8 *key_state = SDL_GetKeyboardState(NULL);
                for (MonoBehaviour *processes : _updates)
                {
                    processes->input(key_state);
                }
                for (MonoBehaviour *processes : _updates)
                {
                    processes->update();
                }
                SDL_RenderClear(renderer);
                for (MonoBehaviour *processes : _updates)
                {
                    processes->render(renderer);
                }
                SDL_RenderPresent(renderer);
                Time.handle_end();
            }
            quit();
        }
        void quit()
        {
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();

            std::ofstream file;
            std::string text_data;
            for (int i = 0; i < data.size(); i++)
            {
                text_data += std::to_string(data[i]);
                text_data += "\n";
            }
            file << text_data.c_str();
        }

    public:
        static engine::FrameHandle Time;
        static std::vector<int> data;
        MainProcess(const char *title)
        {
            _updates = MonoBehaviour::process_updates;
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_RESIZABLE);
            running = true;
            data = engine::init();
            Time.init(data[TARGET_FPS]);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            for (MonoBehaviour *processes : _updates)
            {
                processes->start();
            }
            loop();
        }
        static SDL_Renderer *get_renderer()
        {
            return renderer;
        }
        static long double get_delta_time()
        {
            return Time.deltaTime;
        }
        static SDL_Point get_mouse_position()
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            return {x, y};
        }
        static int get_Fps()
        {
            return data[0];
        }
    };
}

#endif