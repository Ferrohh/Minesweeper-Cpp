// libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

// local classes
#include "RenderWindow.hpp"
#include "Game.hpp"

// constants
#define ROWS 16
#define COLS 16

#define SCALE 3

#define N_BOMBS 40

#define W_W 16*ROWS*SCALE
#define W_H 16*COLS*SCALE


// window & renderer
RenderWindow window = RenderWindow("Minesweeper with C++", W_W, W_H);
bool running = true;
uint8_t playing = 1;

SDL_Texture* tiles_tex = window.load_texture("res/gfx/textures_tiles.png");
Game minesweeper = Game(tiles_tex, ROWS, COLS, N_BOMBS);

SDL_Event events;

// functions
bool SDL_init_all();

int main()
{
    srand(time(NULL));
    if(!SDL_init_all()) return 1; // error initializing SDL

    minesweeper.generate_bombs();

    while(running)
    {
        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(playing)
                    {
                        switch(events.button.button)
                        {
                            case SDL_BUTTON_LEFT:
                                playing = minesweeper.press_tile(W_W, W_H);
                                break;
                            case SDL_BUTTON_RIGHT:
                                minesweeper.place_flag(W_W, W_H);
                                break;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
				    switch(events.key.keysym.sym)
                    {
                        case SDLK_r:
                            playing = true;
                            minesweeper.restart();
                            break;
                    }
                
                
            }
        }
        if(playing == 2)
        {
            std::cout << "You won!" << std::endl;
            playing = 0;
        }

        window.clear();
        
        window.render(minesweeper.get_board(), ROWS, COLS, SCALE);

        window.display();
    }

    return 0; 
}



bool SDL_init_all()
{
    // check if SDL can be initialized
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) > 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << '\n';
        return false;
    }

    // check if SDL IMG can be initialized
    if(!IMG_Init(IMG_INIT_PNG)) {
        std::cerr << "Could not  initialize IMG_Load: " << IMG_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    // check if SDL TTF can be initialized
    if(TTF_Init( )) {
        std::cerr << "Could not init TTF: " << TTF_GetError() << '\n';
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}