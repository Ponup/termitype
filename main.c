#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>

#include "colors.h"
#include "printer.h"
#include "terminal.h"
#include "game.h"
#include "game_intro.h"
#include "game_end.h"

#define TEXT "this is a test"

scene_t scene;
game_state_t game_state;
struct winsize term_size;

void print_time()
{
	time_t now = time(NULL);
	int seconds = now - game_state.start_time;

	printer_t *printer = new_printer();
	printer->pos(printer, 1, 1)
		->color(printer, COLOR_BLACK, COLOR_RED)
		->text(printer, "Time:")
		->color(printer, COLOR_BLACK, COLOR_GREEN);
	if (seconds > 5)
	{
		printer->bold_on(printer);
	}
	printer->text(printer, " %d", seconds);
	if (seconds > 5)
	{
		printer->bold_off(printer);
	}
	printer->flush(printer);
	delete_printer(printer);
}

void print_score(bool error)
{
	printer_t *printer = new_printer();
	printer->pos(printer, term_size.ws_col - 15, 1)
		->text(printer, "Score: %d", game_state.score)
		->flush(printer);
	delete_printer(printer);
}

void print_line()
{
	printer_t *printer = new_printer();
	printer->pos(printer, 1, 20);
	printer->color(printer, COLOR_BLACK, COLOR_GREEN);
	for (int i = 0; i < game_state.text_pos; i++)
	{
		printer->text(printer, "%c", TEXT[i]);
	}
	for (int i = game_state.text_pos; i < sizeof(TEXT); i++)
	{
		printer->color(printer, COLOR_BLACK, COLOR_RED)
			->text(printer, "%c", TEXT[i]);
	}
	printer->flush(printer);
	delete_printer(printer);
}

void play_game()
{
	make_block();
	init_game_state(&game_state);
	while (true)
	{
		bool error = true;
		clear_screen();
		print_time();
		print_score(error);
		print_line();
		char c = getchar();
		if (c != EOF)
		{
			if (TEXT[game_state.text_pos] == c)
			{
				game_state.text_pos++;
				game_state.score++;
			}
			else
			{
				play_bell();
				error = true;
				if (game_state.score > 0)
					game_state.score--;
			}
			if (game_state.text_pos == strlen(TEXT))
			{
				scene = END;
				break;
			}
		}
		refresh_screen();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_size);
		sleep(0.3);
	}
}

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
		play_game();
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
