#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "colors.h"
#include "printer.h"
#include "terminal.h"
#include "game.h"
#include "game_intro.h"
#include "game_end.h"

scene_t scene;
game_state_t game_state;
terminal_t terminal;

int main()
{
	scene = START;
	configure_terminal();

	if (scene == START)
	{
		start_game_intro();
		scene = PLAYING;
	}
	if (scene == PLAYING)
	{
		play_game(&game_state, &terminal);
		make_unblock();
		scene = END;
	}
	if (scene == END)
	{
		start_game_end(&game_state);
		clear_screen();
	}
	restore_terminal();
	return 0;
}
