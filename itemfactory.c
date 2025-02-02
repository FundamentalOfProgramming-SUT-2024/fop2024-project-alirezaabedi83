#include "game.h"

Item* create_sword(int attack, int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=WEAPON_TYPE;

    strcpy(item->string, "sword");

    Weapon* weapon=malloc(sizeof(Weapon));

    weapon->attack=attack;
    weapon->health=health;

    item->item.weapon=weapon;
    return item;
}

Item* create_mace(int attack, int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=WEAPON_TYPE;

    strcpy(item->string, "mace");

    Weapon* weapon=malloc(sizeof(Weapon));

    weapon->attack=attack;
    weapon->health=health;

    item->item.weapon=weapon;
    return item;
}

Item* create_dagger(int attack, int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=WEAPON_TYPE;

    strcpy(item->string, "dagger");

    Weapon* weapon=malloc(sizeof(Weapon));

    weapon->attack=attack;
    weapon->health=health;

    item->item.weapon=weapon;
    return item;
}

Item* create_wand(int attack, int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=WEAPON_TYPE;

    strcpy(item->string, "wand");

    Weapon* weapon=malloc(sizeof(Weapon));

    weapon->attack=attack;
    weapon->health=health;

    item->item.weapon=weapon;
    return item;
}

Item* create_arrow(int attack, int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=WEAPON_TYPE;

    strcpy(item->string, "arrow");

    Weapon* weapon=malloc(sizeof(Weapon));

    weapon->attack=attack;
    weapon->health=health;

    item->item.weapon=weapon;
    return item;
}

void* reset_attack(void* arg) {
    Player* user = (Player*) arg;

    sleep(10);

    user->attack = 5;

    return NULL;
}

void* reset_health(void* arg) {
    Player* user = (Player*) arg;

    sleep(10);

    health-=2;

    return NULL;
}

void delete_weopon(Player *player, char *item_name) {
    for (int i = 0; i < player->weapon_count; i++) {
        if (strcmp(player->weapon_items[i]->string, item_name) == 0) {
            free(player->weapon_items[i]);

            for (int j = i; j < player->weapon_count - 1; j++) {
                player->weapon_items[j] = player->weapon_items[j + 1];
            }

            player->weapon_count--;

        }
    }

}

void delete_potion(Player *player, char *item_name) {
    for (int i = 0; i < player->potion_count; i++) {
        if (strcmp(player->potion_items[i]->string, item_name) == 0) {
            free(player->potion_items[i]);

            for (int j = i; j < player->potion_count - 1; j++) {
                player->potion_items[j] = player->potion_items[j + 1];
            }

            player->potion_count--;

        }
    }

}

Item* create_health_potion(int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=POTION_TYPE;

    strcpy(item->string, "health");

    Potion* potion=malloc(sizeof(Potion));

    potion->health=health;

    item->item.potion=potion;
    return item;
}

Item* create_attack_potion(int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=POTION_TYPE;

    strcpy(item->string, "attack");

    Potion* potion=malloc(sizeof(Potion));

    potion->health=health;

    item->item.potion=potion;
    return item;
}

Item* create_speed_potion( int health){
    Item* item=(Item*)malloc(sizeof(Item));
    item->type=POTION_TYPE;

    strcpy(item->string, "speed");

    Potion* potion=malloc(sizeof(Potion));

    potion->health=health;

    item->item.potion=potion;
    return item;
}
/*
A -> arrow

W -> wand

R -> sword

E -> dagger




*/


/*POTION
X -> health
Z-> attack
P -> speed

*/