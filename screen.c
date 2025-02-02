#include "game.h"
void screen_setup(){
    // int MAX_WIDTH=188;
    // int MAX_HEIGHT=56;
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    srand(time(NULL));
}

int print_game_info(Level* level){
    mvprintw(55, 0, "    Level: %d",level->level);
    printw("    GOLD : %d",gold);
    printw("    SCORE : %d",score);

    printw("    HEALTH: %d(%d)",health,level->user->max_health);
    printw("    ATTACK: %d",level->user->attack);
    printw("    EXPRIENCE: %d\t",level->user->exprience);
    return 1;

}

void print_weopon(Player*player){
        mvprintw(54, 0, "    Weopons: ");
        for (int i=0; i<player->weapon_count; i++) {
            printw("%s ", player->weapon_items[i]->string);
        
        }

}

void print_potion(Player*player){
        mvprintw(54, 0, "    Potions: ");
        for (int i=0; i<player->potion_count; i++) {
            printw("%s ", player->potion_items[i]->string);
        
        }

}

void save_scoreboard(char username[], int score , int gold) {
    FILE *file = fopen("scoreboard.txt", "a");
    if (file == NULL) {
        return;
    }
    fprintf(file, "%s %d %d\n", username, score, gold);
    fclose(file);
}

int compare_scores(const void *a, const void *b) {
    ScoreBoard *entryA = (ScoreBoard *)a;
    ScoreBoard *entryB = (ScoreBoard *)b;
    return entryB->score - entryA->score; 
}
void display_scoreboard(const char* logged_in_user) {
    ScoreBoard scores[100];
    int count = 0;
    int current_page = 0;
    const int entries_per_page = 10;

    FILE *file = fopen("scoreboard.txt", "r");
    if (file == NULL) {
        mvprintw(1, 1, "Error: No scores found.");
        getch();
        return;
    }

    while (fscanf(file, "%s %d %d", scores[count].username, &scores[count].score , &scores[count].gold) != EOF) {
        count++;
    }
    fclose(file);

    qsort(scores, count, sizeof(ScoreBoard), compare_scores);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);  
    init_pair(2, COLOR_CYAN, COLOR_BLACK);    
    init_pair(3, COLOR_GREEN, COLOR_BLACK);  
    init_pair(4, COLOR_WHITE, COLOR_BLACK);  

    int ch;

    do {
        clear();
        mvprintw(1, 1, "Scoreboard (Page %d/%d):", current_page + 1, (count + entries_per_page - 1) / entries_per_page);
        mvprintw(2, 1, "--------------------------");

        for (int i = 0; i < entries_per_page; i++) {
            int idx = current_page * entries_per_page + i;
            if (idx >= count) {
                break;
            }

            if (idx == 0) {
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvprintw(i + 3, 1, "%d. 🏆 %s (Goat) -> %d the gold %d", idx + 1, scores[idx].username, scores[idx].score , scores[idx].gold);
                attroff(A_BOLD);
                attroff(COLOR_PAIR(1));
            } else if (idx == 1) {
                attron(COLOR_PAIR(2));
                attron(A_BOLD);
                mvprintw(i + 3, 1, "%d. 🥈 %s (Legend) -> %d the gold %d", idx + 1, scores[idx].username, scores[idx].score ,scores[idx].gold);
                attroff(A_BOLD);
                attroff(COLOR_PAIR(2));
            } else if (idx == 2) {
                attron(COLOR_PAIR(3));
                attron(A_BOLD);
                mvprintw(i + 3, 1, "%d. 🥉 %s (Master) -> %d the gold %d", idx + 1, scores[idx].username, scores[idx].score,scores[idx].gold);
                attroff(A_BOLD);
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvprintw(i + 3, 1, "%d. %s - %d the gold %d", idx + 1, scores[idx].username, scores[idx].score ,scores[idx].gold);
                attroff(COLOR_PAIR(4));
            }

            if (strcmp(scores[idx].username, logged_in_user) == 0) {
                attron(A_BOLD);
                mvprintw(i + 3, 1, "%d. %s -> %d the gold %d", idx + 1, scores[idx].username, scores[idx].score,scores[idx].gold);
                attroff(A_BOLD);
            }
        }

        mvprintw(LINES - 2, 1, "Use UP/DOWN to scroll, q to quit.");
        refresh();

        ch = getch();
        if (ch == KEY_DOWN && current_page < (count - 1) / entries_per_page) {
            current_page++;
        } else if (ch == KEY_UP && current_page > 0) {
            current_page--;
        }

    } while (ch != 'q');

    clear();
    refresh();
}