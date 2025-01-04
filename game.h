#pragma once

#include <time.h>
#include <stdint.h>

#include "terminal.h"

typedef enum
{
    START,
    PLAYING,
    END
} scene_t;

typedef struct
{
    uint8_t text_pos;
    uint16_t score;
    time_t start_time;
} game_state_t;

void init_game_state(game_state_t *game_state);
void play_game(game_state_t* game_state, const terminal_t *terminal);