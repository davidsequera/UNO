#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

const int CARDS = 108;



class Card {
public:
    string type;
    string color;
    int value;
};

class Player {
public:
    string nickname;
    int cantCartas;
    int score;
    Card deck[10];
    void play() {
        //pone una carta
    }
};

class Table {
public:
    Card lastCard;
    Card picking[CARDS];
    void createCards() {
        srand(time(NULL));
        create();
        mix();
    };
    void showDeck() {
        for (int i = 0; i < CARDS; i++) {
            cout << picking[i].color << " " << picking[i].value << " " << picking[i].type << endl;
        }
    }
private:
    void deleteCard() {
        ;
    }
    void create() {
        for (int i = 0; i < CARDS; i++) {
            if (i < 25) { picking[i].color = "Blue"; }
            if (i < 50 && i >= 25) { picking[i].color = "Red"; }
            if (i < 75 && i >= 50) { picking[i].color = "Yellow"; }
            if (i < 100 && i >= 75) { picking[i].color = "Green"; }
            if (i < 108 && i >= 100) { picking[i].color = "Black"; }
        }// Para los colores
        int value = 1;
        for (int i = 0; i < CARDS; i++) {

            if (i < (CARDS - 8)) {
            //antes de las cartas negras

                picking[i].value = value <= 12 ? value : (value - 13);
                // para valores mayores a 9 se trata de cartas especiales
                // Toma 2 == 10; Cambio de sentido == 11;Pierde turno == 12; 

                picking[i].type = picking[i].value < 10 ? "Normal" : "Special";

                value = value == 25 ? 0 : value; // Sistema para creae solo un 0
                value++;
            }
            if (i >= (CARDS - 8)) {
                picking[i].type = "Special";
                picking[i].value = i < (CARDS - 4) ? 13 : 14;
                //Cambio de color == 13 ; Toma 4 == 14
            }

        }// Para los valores y tipo
    }
    void mix(){
        for (int i = 0; i < CARDS; i++) {
            int random = rand() % CARDS;
            Card temp = picking[i];
            picking[i] = picking[random];
            picking[random] = temp;
        }
    }
};


void mockingPlayers(Player v[], Table);

int main() {
    Table theTable;
    Player players[4];
    theTable.createCards();
    theTable.showDeck();
    mockingPlayers(players, theTable);
    return 0;
}


void mockingPlayers(Player players[], Table table) {
    players[0].nickname = "Martin";
    players[1].nickname = "Jhoseph";
    players[2].nickname = "Jaider";
    players[3].nickname = "David";
    int ca = 0;
    for (int i = 0; i < 4; i++) {
        for (int j= 0; j < 7; j++) {
            players[i].deck[j] = table.picking[ca];
            ca++;
        }
    }
    for (int i = 0; i < 4; i++) {
        cout << players[i].nickname<< ": " <<  endl;
        for (int j = 0; j < 7; j++) {
            cout << " " << players[i].deck[j].color << " " << players[i].deck[j].value << " " << players[i].deck[j].type << endl;
        }
    }
}

