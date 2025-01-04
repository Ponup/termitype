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

game_state_t game_state;
terminal_t terminal;

int main()
{
	init_terminal(&terminal);
	terminal.configure();

	bool quit = false;
	do {
		int selection = start_game_intro();
		if(selection == 'p') {
			play_game(&game_state, &terminal);
			make_unblock();
			start_game_end(&game_state);
			clear_screen();
		}
		else if(selection == 'q') {
			quit = true;
		}
	} while(!quit);

	terminal.restore();

	return EXIT_SUCCESS;
}

