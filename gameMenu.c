#include <ncurses.h>
#include <string.h>
#include "gameMenu.h"
#include "firstMenu.h"

int game_menu() {
    int choice;
    int highlight = 0;
    char *choices[] = {
        "New Game",
        "Continue Previous Game",
        "Scoreboard",
        "Settings",
        "Profile",
        "Back to Main Menu"
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    // initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    mvprintw(1, 1, "Game Menu:");
    while (1) {
        for (int i = 0; i < n_choices; ++i) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(3 + i, 1, "%s", choices[i]);
            attroff(A_REVERSE);
        }

        choice = getch();

        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + n_choices) % n_choices;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % n_choices;
                break;
            case 10:
                if (strcmp(choices[highlight], "New Game") == 0) {
                    mvprintw(10, 1, "Starting a new game...");
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "Continue Previous Game") == 0) {
                    mvprintw(10, 1, "Continuing previous game...");
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "Scoreboard") == 0) {
                    mvprintw(10, 1, "Showing scoreboard...");
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "Settings") == 0) {
                    mvprintw(10, 1, "Opening settings...");
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "Profile") == 0) {
                    mvprintw(10, 1, "Opening profile...");
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "Back to Main Menu") == 0) {
                    first_menu();
                    return 0;
                }
                break;
            default:
                break;
        }

        refresh();
    }

    // endwin();
    clear();
    return 1;
}
