#include "game.h"
#include <ncurses.h>
#include <string.h>

int check_password(char pass[]) {
    if (strlen(pass) < 7 || pass == NULL) {
        return 0;
    }

    int digit_counter = 0, upper_counter = 0, lower_counter = 0;
    for (int i = 0; i < strlen(pass); i++) {
        if (pass[i] >= 'A' && pass[i] <= 'Z') {
            upper_counter++;
        }
        if (pass[i] >= 'a' && pass[i] <= 'z') {
            lower_counter++;
        }
        if (pass[i] >= '0' && pass[i] <= '9') {
            digit_counter++;
        }
    }
    return (upper_counter && lower_counter && digit_counter);
}

int check_email(char email[]) {
    regex_t regex;
    int result;

    const char *pattern = "^[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z]{3}$";

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        return 0;
    }
    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int username_exist(const char username[]) {
    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        return 0;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[MAX_USERNAME_LEN];
        sscanf(line, "%[^:]", stored_username);
        if (strcmp(stored_username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int add_user_to_file(char username[], char password[], char email[]) {
    FILE *file = fopen(USER_FILE, "a");
    if (file == NULL) {
        return 0;
    }
    fprintf(file, "%s:%s:%s\n", username, password, email);
    fclose(file);
    return 1;
}

int search_for_user(char username[], char password[]) {
    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        return 0; 
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[MAX_USERNAME_LEN], stored_password[MAX_PASSWORD_LEN], stored_email[MAX_EMAIL_LEN];
        sscanf(line, "%[^:]:%[^:]:%s", stored_username, stored_password, stored_email);

        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void generate_random_password(char *password, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[length] = '\0';
}

int sign_up() {
    char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN], email[MAX_EMAIL_LEN];
    char choice;

    clear();
    cbreak();
    noecho();
    curs_set(1);

    mvprintw(1, 1, "Welcome, Enter your Username: ");
    echo();
    getstr(username);
    noecho();

    if (strlen(username) == 0) {
        mvprintw(3, 1, "Username cannot be empty.");
        refresh();
        getch();
        clear();
        return 0;
    }

    if (username_exist(username)) {
        mvprintw(3, 1, "Username already exists! Press any key to return.");
        refresh();
        getch();
        clear();
        return 0;
    }

    mvprintw(2, 1, "Do you want to generate a random password? (y/n): ");
    echo();
    choice = getch();
    noecho();

    if (choice == 'y' || choice == 'Y') {
        generate_random_password(password, 10);
        mvprintw(3, 1, "Your generated password is: %s", password);
        refresh();
        getch();
    } else {
        mvprintw(3, 1, "Enter Password: ");
        echo();
        getstr(password);
        noecho();

        if (strlen(password) == 0) {
            mvprintw(4, 1, "Password cannot be empty.");
            refresh();
            getch();
            clear();
            return 0;
        }

        if (!check_password(password)) {
            mvprintw(4, 1, "Password must be at least 7 characters, containing one digit, one uppercase, and one lowercase letter.");
            refresh();
            getch();
            clear();
            return 0;
        }
    }

    mvprintw(4, 1, "Enter Email: ");
    echo();
    getstr(email);
    noecho();

    if (strlen(email) == 0) {
        mvprintw(5, 1, "Email cannot be empty.");
        refresh();
        getch();
        clear();
        return 0;
    }

    if (!check_email(email)) {
        mvprintw(5, 1, "Invalid email format.");
        refresh();
        getch();
        clear();
        return 0;
    }

    if (!add_user_to_file(username, password, email)) {
        mvprintw(6, 1, "Error saving user data.");
        refresh();
        getch();
        clear();
        return 0;
    }

    mvprintw(7, 1, "User successfully created. Press any key to continue.");
    strcpy(user_name, username);
    refresh();
    getch();
    clear();
    return 1;
}

int check_email_for_username(char username[], char email[]) {
    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        return 0;
    }

    char line[200];
    char stored_username[MAX_USERNAME_LEN], stored_password[MAX_PASSWORD_LEN], stored_email[MAX_EMAIL_LEN];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^:]:%[^:]:%s", stored_username, stored_password, stored_email);

        if (strcmp(stored_username, username) == 0 && strcmp(stored_email, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int login() {
    char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN], email[MAX_EMAIL_LEN];
    int choice;

    clear();
    cbreak();
    noecho();
    curs_set(1);

    mvprintw(1, 1, "Welcome, Enter your Username: ");
    echo();
    getstr(username);
    noecho();

    if (strlen(username) == 0) {
        mvprintw(3, 1, "Username cannot be empty.");
        refresh();
        getch();
        clear();
        return 0;
    }

    mvprintw(2, 1, "1. Enter Password");
    mvprintw(3, 1, "2. I forgot my password (log in with email)");
    mvprintw(4, 1, "Choose an option: ");
    echo();
    scanw("%d", &choice);
    noecho();

    clear();

    if (choice == 1) {
        mvprintw(2, 1, "Enter Password: ");
        echo();
        getstr(password);
        noecho();

        if (strlen(password) == 0) {
            mvprintw(4, 1, "Password cannot be empty.");
            refresh();
            getch();
            clear();
            return 0;
        }

        if (search_for_user(username, password)) {
            mvprintw(5, 1, "Login successful! Press any key to continue.");
            refresh();
            getch();
            clear();
            strcpy(user_name, username);
            return 1;
        } else {
            mvprintw(5, 1, "Invalid username or password. Press any key to try again.");
            refresh();
            getch();
            clear();
            return 0;
        }

    } else if (choice == 2) {
        mvprintw(2, 1, "Enter your registered email: ");
        echo();
        getstr(email);
        noecho();

        if (strlen(email) == 0) {
            mvprintw(4, 1, "Email cannot be empty.");
            refresh();
            getch();
            clear();
            return 0;
        }

        if (check_email_for_username(username, email)) {
            mvprintw(5, 1, "Login successful with email! Press any key to continue.");
            refresh();
            getch();
            clear();
            strcpy(user_name, username);
            return 1;
        } else {
            mvprintw(5, 1, "Invalid email for this username. Press any key to try again.");
            refresh();
            getch();
            clear();
            return 0;
        }
    } else {
        mvprintw(6, 1, "Invalid choice. Press any key to return.");
        refresh();
        getch();
        clear();
        return 0;
    }
}


void close_menu(int number_items , MENU* menu , ITEM** items){
    int x;
    unpost_menu(menu);
    free_menu(menu);

    for (x=0; x<number_items; x++) {
        free_item(items[x]);
    }

}

int main_menu(int number_items , char* choices[]){
    int i,c , value;
    MENU* menu;

    ITEM** items=(ITEM**)malloc(sizeof(ITEM**)*number_items);
    ITEM* current;
    for (i=0; i<number_items; i++) {
        items[i]=new_item(choices[i], "");
   
    }
    items[i]=(ITEM*)NULL;
    menu=new_menu((ITEM **)items);
    post_menu(menu);
    refresh();

    while (1) {
        c=getch();
        switch (c) {
            case KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;

            case KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
            case 10:
            current=current_item(menu);
            value=item_index(current);
            close_menu(number_items,menu,items);
            return value;

        
        }
    
    }
}


void settings_menu() {
    int choice;
    int difficulty = 1;  // 1: Easy, 2: Medium, 3: Hard
    char *character_color = "Red";  // Default color
    char *selected_song = "None";

    char *difficulty_levels[] = {
        "Easy",
        "Medium",
        "Hard"
    };

    char *colors[] = {
        "Red",
        "Blue",
        "Green",
        "Yellow"
    };

    char *songs[] = {
        "Song 1",
        "Song 2",
        "Song 3"
    };

    char *settings_options[] = {
        "Change Difficulty",
        "Change Character Color",
        "Select Background Music",
        "Back to Main Menu"
    };

    while (1) {
        clear();
        mvprintw(1, 1, "Settings Menu:");
        mvprintw(2, 1, "1. Change Difficulty (Current: %s)", difficulty_levels[difficulty - 1]);
        mvprintw(3, 1, "2. Change Character Color (Current: %s)", character_color);
        mvprintw(4, 1, "3. Select Background Music (Current: %s)", selected_song);
        mvprintw(5, 1, "4. Back to Main Menu");

        choice = getch() - '0';  // Get user input as integer

        switch (choice) {
            case 1: {  // Change Difficulty
                int diff_choice;
                clear();
                mvprintw(1, 1, "Select Difficulty:");
                mvprintw(2, 1, "1. Easy");
                mvprintw(3, 1, "2. Medium");
                mvprintw(4, 1, "3. Hard");
                diff_choice = getch() - '0';  
                if (diff_choice >= 1 && diff_choice <= 3) {
                    difficulty = diff_choice;
                    if (difficulty==1) {
                        health=100;
                    }else if (difficulty==2) {
                        health=70;
                    }else {
                        health=50;
                    }
                    mvprintw(6, 1, "Difficulty set to: %s", difficulty_levels[difficulty - 1]);
                } else {
                    mvprintw(6, 1, "Invalid choice!");
                }
                getch();
                break;
            }
            case 2: {  // Change Character Color
                int color_choice;
                clear();
                mvprintw(1, 1, "Select Character Color:");
                for (int i = 0; i < 4; i++) {
                    mvprintw(i + 2, 1, "%d. %s", i + 1, colors[i]);
                }
                color_choice = getch() - '0';  
                if (color_choice >= 1 && color_choice <= 4) {
                    color=color_choice;

                    character_color = colors[color_choice - 1];
                    mvprintw(7, 1, "Character color set to: %s", character_color);
                } else {
                    mvprintw(7, 1, "Invalid choice!");
                }
                getch();
                break;
            }
            case 3: {  // Select Background Music
                int song_choice;
                clear();
                mvprintw(1, 1, "Select Background Music:");
                mvprintw(2, 1, "1. Song 1");
                mvprintw(3, 1, "2. Song 2");
                mvprintw(4, 1, "3. Song 3");
                mvprintw(5, 1, "4. Stop Music");
                song_choice = getch() - '0';  
                switch (song_choice) {
                    case 1:
                        selected_song = "Song 1";
                        play_music("music1.mp3");
                        mvprintw(6, 1, "Music selected: %s", selected_song);
                        break;
                    case 2:
                        selected_song = "Song 2";
                        play_music("music2.mp3");
                        mvprintw(6, 1, "Music selected: %s", selected_song);
                        break;
                    case 3:
                        selected_song = "Song 3";
                        play_music("music3.mp3");
                        mvprintw(6, 1, "Music selected: %s", selected_song);
                        break;
                    case 4:
                        selected_song = "None";
                        stop_music();
                        mvprintw(6, 1, "Music stopped.");
                        break;
                    default:
                        mvprintw(7, 1, "Invalid choice!");
                        break;
                }
                getch();
                break;
            }
            case 4:  // Back to Main Menu
            clear();
                return;
            default:
                mvprintw(7, 1, "Invalid option!");
                getch();
                clear();
                break;
        }
    }
}

void play_music(const char *file) {
    if (Mix_PlayingMusic() == 1) {
        Mix_HaltMusic();
    }

    current_music = Mix_LoadMUS(file);
    if (current_music == NULL) {
        mvprintw(10, 1, "Error loading music: %s", Mix_GetError());
        getch();
        return;
    }

    Mix_PlayMusic(current_music, -1);
}

void stop_music() {
    if (Mix_PlayingMusic() == 1) {
        Mix_HaltMusic();
    }}

