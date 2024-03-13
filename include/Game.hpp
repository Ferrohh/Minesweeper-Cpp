#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Tile.hpp"
#include "Math.hpp"

class Game
{
    public:
        Game(SDL_Texture* p_tex, const int p_rows, const int p_cols, const int n_bombs);

        void generate_bombs();
        uint8_t press_tile(const int w_w, const int w_h);
        void place_flag(const int w_w, const int w_h);
        void restart();

        // getters
        std::vector<std::vector<tile>> get_board() {return board;}

    private:
    SDL_Texture* tile_texture;
        std::vector<std::vector<tile>> board;
        std::vector<std::vector<uint8_t>> board_map;
        int rows, cols;
        int n_bombs;
        int free_cells_count, free_cells_total;

        int rand_num(int min, int max) { return (rand() % (max - min)) + min; }

        int count_bombs(const int x, const int y)
        {
            int num_bombs = 0;

            for(int i = -1; i <= 1; i++)
            {
                if(y+i < 0) continue;
                if(y+i > cols-1) continue;
                for(int j = -1; j <= 1; j++)
                {
                    if(i == 0 && j == 0) continue;
                    if(x+j < 0) continue;
                    if(x+j > rows-1) continue;
                    if(board_map[y+i][x+j] == 1) num_bombs++;
                }
            }

            return num_bombs;
        }

        void free_cells(const int x, const int y)
        {
            for(int i = -1; i <= 1; i++)
            {
                if(y+i < 0) continue;
                if(y+i > cols-1) continue;
                for(int j = -1; j <= 1; j++)
                {
                    if(i == 0 && j == 0) continue;
                    if(x+j < 0) continue;
                    if(x+j > rows-1) continue;
                    if(board[y+i][x+j].state == not_clicked && board_map[y+i][x+j] == 0)
                    {
                        board[y+i][x+j].switch_state((tile_rect)count_bombs(x+j, y+i));
                        
                        free_cells_count++;

                        if(count_bombs(x+j, y+i) == 0)
                            free_cells(x+j, y+i);
                    }
                }
            }
        }
};