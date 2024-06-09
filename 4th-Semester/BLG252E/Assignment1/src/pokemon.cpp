//--- 2023-2024 Spring BLG 252E Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Harun Yahya Demirpençe
//---Student Number: 150210022
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "pokemon.h"

using namespace std;

//-------------You Can Add Your Functions Down Below-------------//

//-----------Pokemon Class-----------//

pokemon::pokemon(): name{}, hpValue{}, atkValue{} {}

pokemon::pokemon(const string name, const int atkValue) {
    this->name = name; 
    this->atkValue = atkValue;
    hpValue = 100;
}

pokemon::pokemon(const pokemon& copiedPokemon) {
    this->name = copiedPokemon.name;
    this->atkValue = copiedPokemon.atkValue;
    this->hpValue = copiedPokemon.hpValue;
}

//-----------Pokedex Class-----------//

pokedex::pokedex() : value{} {}

bool pokedex::inPokedex(const string name) const {
    for (int i = 0; i < value; i++) {
        if (pokedexArray[i].getName() == name) 
            return true;
    }
    return false;
}

void pokedex::updatePokedex(const pokemon &pokemon) {
    if (!inPokedex(pokemon.getName())) {
        pokedexArray[value] = pokemon;
        value++;
    }
}

void pokedex::printPokedex() const{
    for (int i = 0; i < value; i++) {
        cout << pokedexArray[i].getName() << "\n";
    }
}

//-----------Player Class-----------//

player::player() : name{}, pokemonNumber{}, pokeballNumber{}, badgeNumber{}, playerPokemon{} {}

player::player(const string name, const pokemon& pokemon) {
    this->name = name;
    pokemonNumber = 0;
    pokeballNumber = 10;
    badgeNumber = 0;
    playerPokemon = pokemon;
}

void player::battleWon() {
    badgeNumber++;
    pokeballNumber += 3;
}

void player::catchPokemon() {
    pokeballNumber--;
    pokemonNumber++;
}

//-----------Enemy Class-----------// 

enemy::enemy() : name{}, enemyPokemon{} {}

enemy::enemy(const string name, const pokemon& pokemon) {
    this->name = name;
    enemyPokemon = pokemon;
}