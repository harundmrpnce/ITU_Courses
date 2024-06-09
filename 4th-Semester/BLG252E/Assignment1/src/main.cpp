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
#include <fstream>

#include "pokemon.h"

using namespace std;

//-------------Do Not Change These Global Variables-------------//
int NAME_COUNTER = 0;   //Use this to keep track of the enemy names
int POK_COUNTER = 0;    //Use this to keep track of the pokemon names
int PLAYER_POKEMON_ATTACK = 20; //You don't have to use this variable but its here if you need it
int ENEMY_POKEMON_ATTACK = 10;  //You don't have to use this variable but its here if you need it
//--------------------------------------------------------------//

//---If Necessary Add Your Global Variables Here---// 
// 
//
//
//-------------------------------------------------//

//-------------Do Not Change These Function Definitions-------------//
string* readEnemyNames(const char*);
string* readPokemonNames(const char*);
player characterCreate(string, int);
void mainMenu();
void fightEnemy(player*, string*, string*);
void catchPokemon(player*, string*);
//------------------------------------------------------------------//

//---If Necessary Add Your Function Definitions Here---// 
//
//
//
//-----------------------------------------------------//

//-------------Do Not Change This Function-------------//
int main(int argc, char* argv[]){
	system("clear");

    //---Creating Enemy and Pokemon Name Arrays---//
    string* enemyNames = readEnemyNames(argv[1]);         
    string* pokemonNames = readPokemonNames(argv[2]);
    

    string playerName;
    int pokemonChoice;

    cout << "Welcome to the Pokemon Game! \n" << endl;
    cout << "Please enter your name: "; 
    cin >> playerName;
    cout << "Please choose one of these pokemons as your pokemon: \n1- Bulbasaur \n2- Charmender \n3- Squirtle \nChoice: ";
    cin >> pokemonChoice;

    //---Character Creation--//
    player newPlayer = characterCreate(playerName, pokemonChoice);
    
    int menuChoice;

    while(true){
        mainMenu(); 
        cin>>menuChoice;

        switch (menuChoice){
        case 1:
            fightEnemy(&newPlayer, enemyNames, pokemonNames);
            break;
        case 2:
            catchPokemon(&newPlayer, pokemonNames);
            break;
        case 3:
            cout<<newPlayer.showPokemonNumber()<<endl;
            break;
        case 4:
            cout<<newPlayer.showPokeballNumber()<<endl;
            break;
        case 5:
            cout<<newPlayer.showBadgeNumber()<<endl;
            break;
        case 6:
            cout << endl;
            cout << "------- Pokedex -------" <<endl;
            newPlayer.playerPokedex.printPokedex();
            break;
        case 7:
            //---Deletes Dynamic Arrays From Memory and Exits---//
            delete[] enemyNames;
            delete[] pokemonNames;
            return EXIT_SUCCESS;
            break;
  
        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};

string* readEnemyNames(const char* argv){
    ifstream file(argv);

    int enemyNum;
    file >> enemyNum;

    string* enemies = new string[enemyNum];

    for (int i = 0; i < enemyNum; i++) {
        file >> enemies[i];
    }
    
    file.close();
    return enemies;
};

string* readPokemonNames(const char* argv){
    ifstream file(argv);

    int pokeNum;
    file >> pokeNum;

    string* pokemons = new string[pokeNum];

    for (int i = 0; i < pokeNum; i++) {
        file >> pokemons[i];
    }
    
    file.close();
    return pokemons;
};

player characterCreate(string playerName, int pokemonChoice){
    string pokemonName;
    switch (pokemonChoice) {
        case 1:
            pokemonName = "Bulbasaur";
            break;
        case 2:
            pokemonName = "Charmender";
            break;
        case 3:
            pokemonName = "Squirtle";
            break;
        default: 
            cout << "Invalid!";
    }

    pokemon playerPokemon(pokemonName, PLAYER_POKEMON_ATTACK);
    player newPlayer(playerName, playerPokemon);
    return newPlayer;
};

//-------------Do Not Change This Function-------------//
void mainMenu(){
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Fight for a badge" << endl;
    cout << "2. Catch a Pokemon" << endl;
    cout << "3. Number of Pokemons" << endl;
    cout << "4. Number of Pokeballs " << endl;
    cout << "5. Number of Badges" << endl;
    cout << "6. Pokedex" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
void fightEnemy(player* newPlayer, string* enemyNames, string* pokemonNames){
    pokemon enemyPokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK);
    enemy newEnemy(enemyNames[NAME_COUNTER], enemyPokemon);
    NAME_COUNTER++;
    POK_COUNTER++;

    newPlayer->playerPokedex.updatePokedex(enemyPokemon);

    int choice;
    newEnemy.printEnemy();
    enemyPokemon.printPokemon();
    cout << "\n1- Fight\n2- Runaway\nChoice: ";
    cin >> choice;

    while (true) {
        if (choice == 1) {
            newPlayer->getPokemon()->attacked(enemyPokemon.getAtkValue());
            enemyPokemon.attacked(newPlayer->getPokemon()->getAtkValue());
            cout << "Your Pokemons Health: " << newPlayer->getPokemon()->getHpValue() << "\n" << newEnemy.getName() << " Pokemons Health: " << enemyPokemon.getHpValue();
            if (newPlayer->getPokemon()->getHpValue() <= 0) {
                cout << "You lost!";
                break;
            }
            else if (enemyPokemon.getHpValue() <= 0) {
                cout << "\nYou won!\n";
                newPlayer->battleWon(); 
                break;
            } else {
                cout << "\n1- Fight\n2- Runaway\nChoice: ";
                cin >> choice;
            }
        } 
        else if (choice == 2) {
            break;
        } 
        else 
            cout << "Enter a valid number!\n";
    }
    newPlayer->getPokemon()->hpReset();
};

void catchPokemon(player* newPlayer, string* pokemonNames){
    pokemon newPokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK);
    POK_COUNTER++;

    newPlayer->playerPokedex.updatePokedex(newPokemon);

    int choice;
    cout << "You encounter with ";
    newPokemon.printPokemon();
    cout << "\n1- Catch\n2- Runaway\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        newPlayer->catchPokemon();
        cout << "You catch " << newPokemon.getName() << "\n\n";
    }
    else 
        return;
};
