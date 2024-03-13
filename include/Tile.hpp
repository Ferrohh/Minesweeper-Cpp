#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum tile_rect
{
    zero = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    not_clicked = 9,
    flag = 10,
    bomb_x = 11,
    question = 12,
    bomb = 13,
    bomb_clicked = 14
};

struct tile
{
    SDL_Rect rect;
    tile_rect state;

    tile(tile_rect p_rect)
    :state(p_rect)
    {
        rect.h = 16;
        rect.w = 16;
        switch(p_rect)
        {
            case 1:
                rect.x = 0;
                rect.y = 0;
                break;
            case 2:
                rect.x = 16;
                rect.y = 0;
                break;
            case 3:
                rect.x = 32;
                rect.y = 0;
                break;
            case 4:
                rect.x = 48;
                rect.y = 0;
                break;
            case 5:
                rect.x = 0;
                rect.y = 16;
                break;
            case 6:
                rect.x = 16;
                rect.y = 16;
                break;
            case 7:
                rect.x = 32;
                rect.y = 16;
                break;
            case 8:
                rect.x = 48;
                rect.y = 16;
                break;
            case 0:
                rect.x = 0;
                rect.y = 32;
                break;
            case 9:
                rect.x = 16;
                rect.y = 32;
                break;
            case 10:
                rect.x = 32;
                rect.y = 32;
                break;
            case 11:
                rect.x = 48;
                rect.y = 32;
                break;
            case 12:
                rect.x = 16;
                rect.y = 48;
                break;
            case 13:
                rect.x = 32;
                rect.y = 48;
                break;
            case 14:
                rect.x = 48;
                rect.y = 48;
                break;
        }
    }

    void switch_state(tile_rect p_state)
    {
        state = p_state;
        switch(state)
        {
            case 1:
                rect.x = 0;
                rect.y = 0;
                break;
            case 2:
                rect.x = 16;
                rect.y = 0;
                break;
            case 3:
                rect.x = 32;
                rect.y = 0;
                break;
            case 4:
                rect.x = 48;
                rect.y = 0;
                break;
            case 5:
                rect.x = 0;
                rect.y = 16;
                break;
            case 6:
                rect.x = 16;
                rect.y = 16;
                break;
            case 7:
                rect.x = 32;
                rect.y = 16;
                break;
            case 8:
                rect.x = 48;
                rect.y = 16;
                break;
            case 0:
                rect.x = 0;
                rect.y = 32;
                break;
            case 9:
                rect.x = 16;
                rect.y = 32;
                break;
            case 10:
                rect.x = 32;
                rect.y = 32;
                break;
            case 11:
                rect.x = 48;
                rect.y = 32;
                break;
            case 12:
                rect.x = 16;
                rect.y = 48;
                break;
            case 13:
                rect.x = 32;
                rect.y = 48;
                break;
            case 14:
                rect.x = 48;
                rect.y = 48;
                break;
        }
    }
};