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