#include "Game.hpp"

Game::Game(SDL_Texture* p_tex, const int p_rows, const int p_cols, const int n_bombs)
:tile_texture(p_tex), rows(p_rows), cols(p_cols), n_bombs(n_bombs)
{
    restart();
}


uint8_t Game::press_tile(const int w_w, const int w_h)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int x = mouseX*cols/w_w;
    int y = mouseY*rows/w_h;

    if(board[y][x].state == not_clicked)
    {
        if(board_map[y][x] == 1)
        {
            board[y][x].switch_state(bomb_clicked);
            game_over();
            return 0;
        }
        else
        {
            board[y][x].switch_state((tile_rect)count_bombs(x, y));
            free_cells_count++;
            if(count_bombs(x, y) == 0)
                free_cells(x, y);
        }
    }
    
    if(free_cells_count == free_cells_total) return 2;

    return 1;
}

void Game::place_flag(const int w_w, const int w_h)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int x = mouseX*cols/w_w;
    int y = mouseY*rows/w_h;

    switch(board[y][x].state)
    {
        case not_clicked:
            board[y][x].switch_state(flag);
            break;
        case flag:
            board[y][x].switch_state(not_clicked);
            break;
    }
}

void Game::restart()
{
    board = std::vector<std::vector<tile>>(rows, std::vector<tile>(cols, tile(not_clicked)));
    board_map = std::vector<std::vector<uint8_t>>(rows, std::vector<uint8_t>(cols, 0));
    free_cells_count = 0;
    free_cells_total = 0;
    generate_bombs();
}