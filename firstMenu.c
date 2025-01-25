#include <ncurses.h>
#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "firstMenu.h"
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_EMAIL_LEN 100
#define USER_FILE "users.txt"

int check_password(char pass[]);
int check_email(char email[]);
int username_exist(const char username[]);
int add_user_to_file(char username[], char password[], char email[]);
int search_for_user(char username[], char password[]);
void generate_random_password(char *password, int length);
int sign_up();
int check_email_for_username(char username[], char email[]);
int login();
int first_menu();
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

    // initscr();
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

    // initscr();
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

// int first_menu() {
//     int choice;

//     initscr();
//     cbreak();
//     noecho();
//     curs_set(1);

//     mvprintw(1, 1, "Welcome to rogue!");
//     mvprintw(2, 1, "1.LogIn");
//     mvprintw(3, 1, "2.SignUp");
//     mvprintw(4, 1, "3.Play as a guest");
//     mvprintw(5, 1, "4.Exit");
//     mvprintw(6, 1, "choose one: ");
//     echo();
//     scanw("%d", &choice);
//     clear();
//     noecho();
//     switch (choice) {
//         case 1:while (!login());
//         break;
//         case 2:while(!sign_up());
//         break;
//         case 3:/*do later*/
//         break;
//         case 4:
//         mvprintw(7, 1, "GOODBYE...");
//         refresh();
//         getch();
//         endwin();
//         return 0;
//         break;
//         default:
//         mvprintw(7, 1, "Wrong input please try again.");
//         refresh();
//         getch();
//         clear();
//         first_menu();
//         break;
    
//     }
//     endwin();
//     return 1;
// }
int first_menu() {
    int choice;
    int highlight = 0;
    char *choices[] = {
        "LogIn",
        "SignUp",
        "guest",
        "Exit",
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    mvprintw(1, 1, "WELCOME!");
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
                if (strcmp(choices[highlight], "LogIn") == 0) {
                    clear();
                    if(login()){return 1;}
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "SignUp") == 0) {
                    clear();
                    if(sign_up()){return 1;}
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "guest") == 0) {
                    /*do later*/
                    refresh();
                    getch();
                    clear();
                } else if (strcmp(choices[highlight], "Exit") == 0) {
                    clear();
                    endwin();
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
