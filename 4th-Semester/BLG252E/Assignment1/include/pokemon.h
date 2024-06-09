//--- 2023-2024 Spring BLG 252E Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Harun Yahya Demirpençe
//---Student Number: 150210022
//--------------------------//

#ifndef _H
#define _H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//-------------Do Not Add Any New Class(es)-------------//

class pokemon{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        int hpValue;
        int atkValue;
    public:
        pokemon();
        pokemon(const string, const int);
        pokemon(const pokemon&);
        string getName() const { return name; }
        int getHpValue() const { return hpValue; }
        int getAtkValue() const { return atkValue; }
        void printPokemon() const { cout << this->name << " Health: " << this->hpValue << " Attack: " << this->atkValue; }
        void attacked(int atk) { hpValue -= atk; }
        void hpReset() { hpValue=100; }
};

class pokedex{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        pokemon pokedexArray[100];
        int value;
        bool inPokedex(const string) const;
    public:
        pokedex();
        void updatePokedex(const pokemon&);
        void printPokedex() const;   
       
};

class player{
    private:
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
        string name;
        int pokemonNumber;
        int pokeballNumber;
        int badgeNumber;
        pokemon playerPokemon;
    public:
        pokedex playerPokedex;
        player();
        player(const string, const pokemon&);
        int showPokemonNumber() const { return pokemonNumber; }
        int showPokeballNumber() const { return pokeballNumber; }
        int showBadgeNumber() const { return badgeNumber; }
        pokemon* getPokemon() { return &playerPokemon; }
        void battleWon();
        void catchPokemon();
        
};

class enemy{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        pokemon enemyPokemon;
    public:
        enemy();
        enemy(const string, const pokemon&);
        pokemon* getPokemon() { return &enemyPokemon; }
        string getName() const { return name; }
        void printEnemy() const { cout << "You encounter with " << name << " and his/hers pokemon " << enemyPokemon.getName() << "\n"; }
        
};

#endif