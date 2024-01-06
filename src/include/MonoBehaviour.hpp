#include <SDL2/SDL.h>

#ifndef MONOBEHAVIOUR_HPP
#define MONOBEHAVIOUR_HPP

// this class is a base for gluing classes to the main process
// classes that inherit from this should not be deconstructed until the end of the program, else a segault will occur
// 

namespace engine
{
    // DO NOT TYPE MONOBEHAVIOUR IN A COMMENT AFTER CLASS DECLARATION
    class MonoBehaviour
    {

    public:
        static std::vector<MonoBehaviour *> process_updates;
        virtual void start(){

        };
        virtual void update(){

        };
        virtual void render(SDL_Renderer *renderer)
        {
            
        };
        virtual void input(const Uint8 *key_state)
        {

        };
        virtual void event(SDL_Event* event)
        {

        };
        static void add_process(MonoBehaviour *process)
        {
            process_updates.push_back(process);
        }
        MonoBehaviour()
        {
            process_updates.push_back(this);
        }
    };
}

#endif