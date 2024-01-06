#ifndef ENUMS_HPP
#define ENUMS_HPP


// contains the order for which data read from a file is stored in an array
// for eample the first data read contains the Target FPS at which the game should run

typedef enum{
    TARGET_FPS,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    WINDOW_FLAGS,
    RENDERER_FLAGS,
}Data_Order;

#endif
