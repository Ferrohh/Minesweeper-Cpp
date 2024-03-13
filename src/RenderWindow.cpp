#include "RenderWindow.hpp"

RenderWindow::RenderWindow(std::string p_title, int p_w, int p_h)
:window(NULL)
{
    window = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, SDL_WINDOW_ALLOW_HIGHDPI);
	
    if(window == NULL) {
        std::cerr  << "Window failed to init! Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

RenderWindow::~RenderWindow() 
{
    // clean up the  window and close it
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}


void RenderWindow::render(std::vector<std::vector<tile>> tiles, const int rows, const int cols, const float scale)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    for (int i=0; i < rows; i++) 
    {
        for (int j=0; j < cols; j++) 
        {
            SDL_Rect dst;
            dst.h = 16*scale;
            dst.w = 16*scale;
            dst.x = 16*j*scale;
            dst.y = 16*i*scale;

            SDL_RenderCopy(renderer, tiles[i][j].tex, &tiles[i][j].rect, &dst);
        }
    }
}


SDL_Texture* RenderWindow::load_texture(const std::string file_path)
{
	// load image from file path
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, file_path.c_str());

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::clear() 
{
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}