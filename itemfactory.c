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

void delete_item(Player *player, char *item_name) {
    for (int i = 0; i < player->item_count; i++) {
        if (strcmp(player->items[i]->string, item_name) == 0) {
            free(player->items[i]);

            for (int j = i; j < player->item_count - 1; j++) {
                player->items[j] = player->items[j + 1];
            }

            player->item_count--;

        }
    }

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