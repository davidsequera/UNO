#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;
const int CARDS = 108;


struct Card {
    string type;
    string color;
    int value;
};

struct Player {
    string nickname;
    int cantCartas;
    int score;
    Card deck[10];
};

struct Table {
    Card lastCard;
    Card picking[CARDS];
};


void mockingPlayers(Player [], Table);

void createCards(Table &a) {
    srand(time(NULL));
    for (int i = 0; i < CARDS; i++) {
        if (i < 25) { a.picking[i].color = "Blue"; }
        if (i < 50 && i >= 25) { a.picking[i].color = "Red"; }
        if (i < 75 && i >= 50) { a.picking[i].color = "Yellow"; }
        if (i < 100 && i >= 75) { a.picking[i].color = "Green"; }
        if (i < 108 && i >= 100) { a.picking[i].color = "Black"; }
    }// Para los colores
    int value = 1;
    for (int i = 0; i < CARDS; i++) {

        if (i < (CARDS - 8)) {
            //antes de las cartas negras

            a.picking[i].value = value <= 12 ? value : (value - 13);
            // para valores mayores a 9 se trata de cartas especiales
            // Toma 2 == 10; Cambio de sentido == 11;Pierde turno == 12; 

            a.picking[i].type = a.picking[i].value < 10 ? "Normal" : "Special";

            value = value == 25 ? 0 : value; // Sistema para creae solo un 0
            value++;
        }
        if (i >= (CARDS - 8)) {
            a.picking[i].type = "Special";
            a.picking[i].value = i < (CARDS - 4) ? 13 : 14;
            //Cambio de color == 13 ; Toma 4 == 14
        }

    }// Para los valores y tipo
    for (int i = 0; i < CARDS; i++) {
        int random = rand() % CARDS;
        Card temp = a.picking[i];
        a.picking[i] = a.picking[random];
        a.picking[random] = temp;
    }
};
void showDeck(Table &a) {
    for (int i = 0; i < CARDS; i++) {
        cout << a.picking[i].color << " " << a.picking[i].value << " " << a.picking[i].type << endl;
    }
}

int main() {
    Table theTable;
    Player players[4];
    createCards(theTable);
    showDeck(theTable);
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

