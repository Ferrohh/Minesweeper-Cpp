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
        /*      constructor         */
        // initialize the game board and logic
        // p_tex --> texture for the tiles
        // p_rows --> number of rows of the field
        // p_cols --> number of cols of the field
        // n_bombs --> number of bombs to place
        Game(SDL_Texture* p_tex, const int p_rows, const int p_cols, const int n_bombs);


        /*      FUNCTIONS       */
        uint8_t press_tile(const int w_w, const int w_h); // events for when you press one tile (left click)
        void place_flag(const int w_w, const int w_h);  // events for when you place one flag (right click)
        void restart(); // events for when you restart


        /*      GETTERS     */
        std::vector<std::vector<tile>> get_board() { return board; }
        SDL_Texture* get_tex() { return tile_texture; }


    private:
        /*      VARIABLES       */
        SDL_Texture* tile_texture; // texture of the tiles for the board
        std::vector<std::vector<tile>> board; // board, saving rects and states
        std::vector<std::vector<uint8_t>> board_map; // saving where the bombs are placed
        int rows, cols; // dimensions of the field
        int n_bombs; // number of bombs
        int free_cells_count, free_cells_total; // counter for counting how many cells the player've free'd

        /*      PRIVATE FUNCTIONS       */

        // generate random number
        int rand_num(int min, int max) { return (rand() % (max - min)) + min; }

        // generate bombs in the field
        void generate_bombs()
        {
            // make a space where bombs can't spawn in the center
            std::vector<vector2f> busy_places = {
                vector2f(cols/2-1-1, rows/2-1-1),
                vector2f(cols/2-1-1, rows/2-1),
                vector2f(cols/2-1-1, rows/2+1-1),
                vector2f(cols/2-1, rows/2-1-1),
                vector2f(cols/2-1, rows/2-1),
                vector2f(cols/2-1, rows/2+1-1),
                vector2f(cols/2+1-1, rows/2-1-1),
                vector2f(cols/2+1-1, rows/2-1),
                vector2f(cols/2+1-1, rows/2+1-1),
                };

            // go through all the bombs to place them
            for(int i = 0; i < n_bombs; i++)
            {
                // generate random position
                vector2f new_bomb(rand_num(0, cols), rand_num(0, rows));
                bool is_place_av = true; // bool to check if the place is available

                // go through all busy places
                for(vector2f pos : busy_places)
                {   
                    // if the place is taken, change the bool
                    if(new_bomb.x == pos.x && new_bomb.y == pos.y)
                    {
                        is_place_av = false;
                        break;
                    }
                }
                // if the place is available, place the bomb and put it on the board map
                if(is_place_av)
                {
                    busy_places.push_back(new_bomb);
                    board_map[new_bomb.y][new_bomb.x] = 1;
                }
                else
                    i--;
            }

            // count the total of free cells
            for(std::vector<uint8_t> i : board_map)
            {
                for(uint8_t j : i)
                {
                    if(j == 0)
                        free_cells_total++;
                }
            }
        }

        // count the bombs around a cell with x & y coords and returns the number
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

        // open the cells in case they're 0 bombs
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
                        
                        // recursive function un case there are other cells with 0 bombs
                        if(count_bombs(x+j, y+i) == 0)
                            free_cells(x+j, y+i);
                    }
                }
            }
        }

        // function to show all the bombs in case of game over
        void game_over()
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    if(board[i][j].state == not_clicked && board_map[i][j] == 1)
                        board[i][j].switch_state(bomb);
                    if(board[i][j].state == flag && board_map[i][j] == 0)
                        board[i][j].switch_state(bomb_x);
                }
            }
        }
};