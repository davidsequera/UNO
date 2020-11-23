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
    int NCards;
    int score;
    Card deck[CARDS];
};

struct Table {
    int Npick;
    int Ndeck;
    string color;
    Card deck[CARDS];
    Card pick[CARDS];
};


void game(Player [], int, Table&);



//funciones para manejo de arreglos
void createCards(Table& );
void showDeck(Table, string);
void deleteCardPlayer(Player &, int);
void mockingPlayers(Player [], Table&);
void deleteCard(Table&);
void insertCard(Table&, Card);
void insertCardPlayer(Player&, Table&);

//funciones para funcionalidad del juego
void turns(Player players[], Table& theTable);
bool conditions(Card, Table);
void askforColor(Table&);
void reverse(Player[], int, int&);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main() {

    const int NP = 4;//number of players
    Table theTable;
    Player players[NP];
    createCards(theTable);
    showDeck(theTable, "pick");
    mockingPlayers(players, theTable);
    game(players, NP, theTable);
    showDeck(theTable, "deck");
    return 0;
}

void game(Player players[], int NP, Table& theTable) {
    int winner = 0;
    while (winner < 2) {
        turns(players, theTable);
        winner++;
    }
}



void aame(Player players[], int NP, Table &theTable) {
    int S;//seleccionada
    int jugandocon = 7;
    bool winner = false;
    while (!winner) {
        for (int i = 0; i < NP; i++) {
            cout << players[i].nickname << ": " << endl;
            for (int j = 0; j < players[i].NCards; j++) {
                cout << '\t' << j + 1 << '\t' << players[i].deck[j].color << '\t' << players[i].deck[j].value << '\t' << players[i].deck[j].type << endl;
            }
            cout << "Selecciona una carta:" << endl;
            do { cin >> S; } while (S > players[i].NCards); S--;
            insertCard(theTable, players[i].deck[S]);
            deleteCardPlayer(players[i], S);
            for (int j = 0; j < players[i].NCards; j++) {
                cout << '\t' << j + 1 << '\t' << players[i].deck[j].color << '\t' << players[i].deck[j].value << '\t' << players[i].deck[j].type << endl;
            }
        }
        winner = true;
    }
}


//funciones para funcionalidad del juego

void turns(Player players[], Table& theTable) {
    int NP = 4;//parametro
    for (int i = 0; i < NP; i++) {
        cout << "Carta Actual:" << '\t' << theTable.deck[theTable.Ndeck].color << '\t' << theTable.deck[theTable.Ndeck].value << '\t' << theTable.deck[theTable.Ndeck].type << endl;
        cout << "Color Actual:"<< '\t'  << theTable.color << endl;
        cout << players[i].nickname << ": " << endl;
        for (int j = 0; j < players[i].NCards; j++) {
            cout << '\t' << j + 1 << '\t' << players[i].deck[j].color << '\t' << players[i].deck[j].value << '\t' << players[i].deck[j].type << endl;
        }
        int S;//seleccion del jugador
        bool achieve = false;// comprobante
        do {
            cout << players[i].nickname << " Selecciona una carta:" << endl;
            do { cin >> S; } while (S > players[i].NCards || S < 0); S--;
            if (S >= 0) {
                achieve = conditions(players[i].deck[S], theTable);
                if (achieve) {
                    insertCard(theTable, players[i].deck[S]);
                    //cambia tambien el color de la tabla
                    deleteCardPlayer(players[i], S);
                    // Toma 2 == 10; Cambio de sentido == 11;Pierde turno == 12;Cambio de color == 13 ; Toma 4 == 14; 
                    //if (players[i].deck[S].value == 10) {
                    //    insertCardPlayer(players[i + 1], theTable);
                    //    insertCardPlayer(players[i + 1], theTable);
                    //}
                    //if (players[i].deck[S].value == 11) {
                    //    reverse(players, NP, i);
                    //}
                    //if (players[i].deck[S].value == 12) { i++; }
                    //if (players[i].deck[S].value == 13) { askforColor(theTable); }
                    //if (players[i].deck[S].value == 14) {
                    //    insertCardPlayer(players[i + 1], theTable);
                    //    insertCardPlayer(players[i + 1], theTable);
                    //    insertCardPlayer(players[i + 1], theTable);
                    //    insertCardPlayer(players[i + 1], theTable);
                    //    askforColor(theTable);
                    //}
                }
            }
            else
            {
                insertCardPlayer(players[i], theTable);
                achieve = true;
            }

        } while (!achieve);
        //system("cls");
        //system("pause");
    }
}

bool conditions(Card Cplayer, Table table) {
    cout << "[conditions]" << endl;
    cout << Cplayer.color << '\t' << Cplayer.value << '\t' << Cplayer.type << endl;
    if (Cplayer.type == "Normal") {
        if (Cplayer.color != table.color && Cplayer.value != table.deck[table.Ndeck].value) {
            if (Cplayer.value != table.deck[table.Ndeck].value) {
                cout << "Valor Carta jugador "<< Cplayer.value << " VS " << "Valor Carta tabla " <<  table.deck[table.Ndeck].value <<endl;
            }
            return false;
        }
    }
    else if(Cplayer.color != "Black" && Cplayer.color != table.color) {
        return false;
    }
    return true;
}

void askforColor(Table& theTable){
    string color;
    cout << "Seleccione un color" << endl;
    cout << "Red, Green, Blue, Yellow" << endl;
    do { cin >> color; } while (color != "Red" || color != "Green" || color != "Blue" || color != "Yellow");
    theTable.color = color;
}
void reverse(Player players[], int size, int &i) {
    Player copy[100];
    for (int u = 0; u < size; u++) {
        copy[u] = players[u];
    }//Hacer una copia
    int u = size - 1;
    int v = 0;
    do {
        players[u] = copy[v];
        u--;
        v++;
    } while (u > -1);
    i = abs(i - size + 1);//Arregla la posicion
}



//funciones para manejo de arreglos


void createCards(Table& a) {
    srand(time(NULL));
    for (int i = 0; i < CARDS; i++) {
        if (i < 25) { a.pick[i].color = "Blue"; }
        if (i < 50 && i >= 25) { a.pick[i].color = "Red"; }
        if (i < 75 && i >= 50) { a.pick[i].color = "Yellow"; }
        if (i < 100 && i >= 75) { a.pick[i].color = "Green"; }
        if (i < 108 && i >= 100) { a.pick[i].color = "Black"; }
    }// Para los colores
    int value = 1;
    for (int i = 0; i < CARDS; i++) {

        if (i < (CARDS - 8)) {
            //antes de las cartas negras

            a.pick[i].value = value <= 12 ? value : (value - 13);
            // para valores mayores a 9 se trata de cartas especiales
            // Toma 2 == 10; Cambio de sentido == 11;Pierde turno == 12; 

            a.pick[i].type = a.pick[i].value < 10 ? "Normal" : "Special";

            value = value == 25 ? 0 : value; // Sistema para creae solo un 0
            value++;
        }
        if (i >= (CARDS - 8)) {
            a.pick[i].type = "Special";
            a.pick[i].value = i < (CARDS - 4) ? 13 : 14;
            //Cambio de color == 13 ; Toma 4 == 14
        }

    }// Para los valores y tipo
    for (int i = 0; i < CARDS; i++) {
        int random = rand() % CARDS;
        Card temp = a.pick[i];
        a.pick[i] = a.pick[random];
        a.pick[random] = temp;
    }// mixer
    a.Npick = CARDS;
    a.Ndeck = 0;


    //Añadir carta a deck
    int PickP = 0;//posicion
    while (a.pick[PickP].type == "Special") { PickP++; }//garantizar que primera carta no es especial
    Card PickCard = a.pick[0];
    a.pick[0] = a.pick[PickP];
    a.pick[PickP] = PickCard;
    a.deck[a.Ndeck] = a.pick[0];
    a.color = a.deck[a.Ndeck].color;
    deleteCard(a);
}; //crea maso de 108 en pick y carta inicial
void showDeck(Table a, string x) {
    if (x == "pick") {
        for (int i = 0; i < a.Npick; i++) {
            cout << a.pick[i].color << '\t' << a.pick[i].value << '\t' << a.pick[i].type << endl;
        }
    }
    if (x == "deck") {
        for (int i = 0; i < a.Ndeck; i++) {
            cout << a.deck[i].color << '\t' << a.deck[i].value << '\t' << a.deck[i].type << endl;
        }
    }
}
void deleteCard(Table &theTable) {
    for (int i = 1; i < theTable.Npick; i++) {
        theTable.pick[i-1] = theTable.pick[i];
    }
    theTable.Npick--;
}//elimina una carta del inicio de pick
void insertCard(Table& theTable, Card card) {
    if (theTable.color != card.color) { theTable.color = card.color; }
    theTable.Ndeck++;
    theTable.deck[theTable.Ndeck] = card;
}//inserta una carta en deck
void insertCardPlayer(Player& thePlayer, Table& table) {
    thePlayer.deck[thePlayer.NCards] = table.pick[0];
    thePlayer.NCards++;
    deleteCard(table);
}//inserta una carta en jugador
void deleteCardPlayer(Player &thePlayer, int deleted) {
    Player copy = thePlayer;
    Card temp = copy.deck[deleted];
    copy.deck[deleted] = copy.deck[copy.NCards - 1];
    copy.deck[copy.NCards-1] = temp;
    copy.NCards -= 1;
    for (int i = 0; i < copy.NCards; i++) {
        thePlayer.deck[i] = copy.deck[i];
    }
    thePlayer.NCards = copy.NCards;
}//elimina una carta de jugador, por indice
void mockingPlayers(Player players[], Table &table) {
    players[0].nickname = "Martin";
    players[1].nickname = "Jhoseph";
    players[2].nickname = "Jaider";
    players[3].nickname = "David";
    for (int i = 0; i < 4; i++) {
        players[i].NCards = 0;
        players[i].score = 0;
        for (int j= 0; j < 7; j++) {
            insertCardPlayer(players[i], table);
        }
    }
}//crea los jugadores


//UNO PREGUNTAR DESPUES AL JUGADOR

