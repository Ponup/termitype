#include "game.h"

#include <stdio.h>

void init_game_state(game_state_t *game_state)
{
    game_state->text_pos = 0;
    game_state->score = 0;
    game_state->start_time = time(NULL);
}
