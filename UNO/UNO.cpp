#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;
const int CARDS = 108; //tamaño fisico de las cartas


struct Card
{
    string type;
    string color;
    int value;
};

struct Player
{
    string nickname;
    int NCards;
    int score;
    Card deck[10];
};

struct Table
{
    int Npick; //tamaño logico de las cartas a poner
    int Ndeck; //tamaño logico de la baraja
    Card deck[CARDS];
    Card pick[CARDS];
};


void game(Player [], int, Table&);
void createCards(Table& );
void showDeck(Table, string);
void deleteCardPlayer(Player &, int);
void mockingPlayers(Player [], Table&);
void deleteCard(Table&);
void insertCard(Table&, Card);


int main()
{
    const int PP = 4;//number of players
    Table theTable;
    Player players[PP];
    createCards(theTable);
    //showDeck(theTable, "pick");
    mockingPlayers(players, theTable);
    game(players, PP, theTable);
    showDeck(theTable, "deck");
    return 0;
}
void game(Player players[], int PP, Table &theTable)
{
    int S;//seleccionada
    int jugandocon = 7;
    bool winner = false;
    while (!winner)
    {
        for (int i = 0; i < 4; i++)
        {
            cout << players[i].nickname << ": " << endl;
            for (int j = 0; j < players[i].NCards; j++)
            {
                cout << '\t' << j + 1 << '\t' << players[i].deck[j].color << '\t' << players[i].deck[j].value << '\t' << players[i].deck[j].type;
                if(players[i].deck[j].value==10){
                cout<<"\t- Toma dos"<<endl;
                }
                if(players[i].deck[j].value==11){
                cout<<"\t- Cambio de sentido"<<endl;
                }
                if(players[i].deck[j].value==12){
                cout<<"\t- Pierde turno"<<endl;
                }
                if(players[i].deck[j].value==13){
                cout<<"\t- Cambio de color"<<endl;
                }
                if(players[i].deck[j].value==14){
                cout<<"\t- Toma cuatro"<<endl;
                }
                if(players[i].deck[j].value<10){
                cout<<endl;
                }
            }
            cout << "\nSelecciona una carta:" << endl;
            do
            {
                cin >> S;
            }
            while (S > players[i].NCards);
            S--;
            insertCard(theTable, players[i].deck[S]);
            deleteCardPlayer(players[i], S);
            cout <<"\nCartas actuales de "<<players[i].nickname<< ": "<<endl;
            for (int j = 0; j < players[i].NCards; j++)
            {
                cout << '\t' << j + 1 << '\t' << players[i].deck[j].color << '\t' << players[i].deck[j].value << '\t' << players[i].deck[j].type << endl;
            }
            cout<<endl;
        }
        winner = true;
    }
}
void createCards(Table& a)
{
    srand(time(NULL));
    for (int i = 0; i < CARDS; i++)
    {
        if (i < 25)
        {
            a.pick[i].color = "Blue";
        }
        if (i < 50 && i >= 25)
        {
            a.pick[i].color = "Red";
        }
        if (i < 75 && i >= 50)
        {
            a.pick[i].color = "Yellow";
        }
        if (i < 100 && i >= 75)
        {
            a.pick[i].color = "Green";
        }
        if (i < 108 && i >= 100)
        {
            a.pick[i].color = "Black";
        }
    }// Para los colores
    int value = 1;
    for (int i = 0; i < CARDS; i++)
    {

        if (i < (CARDS - 8))
        {
            //antes de las cartas negras

            a.pick[i].value = value <= 12 ? value : (value - 13);
            // para valores mayores a 9 se trata de cartas especiales
            // Toma 2 == 10; Cambio de sentido == 11;Pierde turno == 12;

            a.pick[i].type = a.pick[i].value < 10 ? "Normal" : "Special";

            value = value == 25 ? 0 : value; // Sistema para crear solo un 0
            value++;
        }
        if (i >= (CARDS - 8))
        {
            a.pick[i].type = "Special";
            a.pick[i].value = i < (CARDS - 4) ? 13 : 14;
            //Cambio de color == 13 ; Toma 4 == 14
        }

    }// Para los valores y tipo
    for (int i = 0; i < CARDS; i++)
    {
        int random = rand() % CARDS;
        Card temp = a.pick[i];
        a.pick[i] = a.pick[random];
        a.pick[random] = temp;
    }// mixer
    a.Npick = CARDS;
    a.Ndeck = 0;
};
void showDeck(Table a, string x)
{
    if (x == "pick")
    {
        for (int i = 0; i < a.Npick; i++)
        {
            cout << a.pick[i].color << '\t' << a.pick[i].value << '\t' << a.pick[i].type << endl;
        }
    }
    if (x == "deck")
    {
        for (int i = 0; i < a.Ndeck; i++)
        {
            cout << a.deck[i].color << '\t' << a.deck[i].value << '\t' << a.deck[i].type << endl;
        }
    }
}
void deleteCard(Table &theTable)
{
    for (int i = 1; i < theTable.Npick; i++)
    {
        theTable.pick[i-1] = theTable.pick[i];
    }
    theTable.Npick--;
}
void insertCard(Table& theTable, Card card)
{
    theTable.deck[theTable.Ndeck] = card;
    theTable.Ndeck++;
}//en proceso

void deleteCardPlayer(Player &thePlayer, int deleted)
{
    Player copy = thePlayer;
    Card temp = copy.deck[deleted];
    copy.deck[deleted] = copy.deck[copy.NCards - 1];
    copy.deck[copy.NCards-1] = temp;
    copy.NCards -= 1;
    for (int i = 0; i < copy.NCards; i++)
    {
        thePlayer.deck[i] = copy.deck[i];
    }
    thePlayer.NCards = copy.NCards;
}

void mockingPlayers(Player players[], Table &table)
{
    players[0].nickname = "Martin";
    players[1].nickname = "Jhoseph";
    players[2].nickname = "Jaider";
    players[3].nickname = "David";
    int ca = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j= 0; j < 7; j++)
        {
            players[i].deck[j] = table.pick[ca];
            deleteCard(table);
        }
        players[i].NCards = 7;
    }
}


