#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

#include "Tile.hpp"

class RenderWindow 
{
    public:
        // Constructor / Destructor
        RenderWindow(std::string p_title, int p_w, int p_h);
        ~RenderWindow();

        SDL_Texture* load_texture(const std::string file_path);

        void render(std::vector<std::vector<tile>> tiles, const int rows, const int cols, const float scale);

        void clear();
        void display();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};