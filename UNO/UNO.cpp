#include <iostream>
#include <math.h>
#include <time.h>
#include <string>


using namespace std;
const int CARDS = 108; //tamaño fisico de las cartas
const int PLAYERS = 10; //tamaño fisico de los jugadores


struct Card
{
    string type;
    string color;
    int value;
    int score;
};

struct Player
{
    string nickname;
    int NCards;
    int score;
    Card deck[CARDS];
};

struct Table
{
    int Npick;
    int Ndeck;
    string color;
    Card deck[CARDS];
    Card pick[CARDS];
};


void game(Player [PLAYERS], Table&);
void header();
void instructions(int);


//funciones para manejo de arreglos
void createCards(Table&, string);
int createPlayers(Player [], Table&);
void showDeck(Table, string);
void deleteCardPlayer(Player &, int);
int mockingPlayers(Player[], Table&);
void deleteCard(Table&);
void insertCard(Table&, Card);
void insertCardPlayer(Player&, Table&);
void createCards4Players(Player[], Table&, int);

//funciones para funcionalidad del juego
void turns(Player players[PLAYERS], Table& theTable, int);
bool conditions(Card, Table);
void askforColor(Table&);
void reverse(Player[PLAYERS], int, int&);
void UNO(Player&, Table&);
bool winnerCheck(Player player);

int main()
{
    int option=0, idiom=0;
    bool start=false;
    do
    {
        if(option==0){
          header();
        }
        cout <<"  1. Play"<<endl;
        cout <<"  2. Instructions"<<endl;
        cout <<"  3. Exit"<<endl;
        cout <<"\n  Choose an option: ";
        cin>>option;

        switch(option)
        {
        case 2:
            cout<<"\n  1. Spanish"<<endl;
            cout<<"  2. English"<<endl;
            do
            {
                cout<<"\n  Choose an idiom: ";
                cin>>idiom;
            }
            while(idiom>2 || idiom<1);
            instructions(idiom);
            option==0;
            break;
        case 3:
            cout <<"  Have a good day :)"<<endl;
            break;
        default:
            cout <<"  Invalid option !!\n"<<endl;
            break;
        case 1:
            system("cls");
            start=true;
            Player players[PLAYERS];
            Table theTable;
            //showDeck(theTable, "pick");
            game(players, theTable);
            //showDeck(theTable, "deck");
            break;
        }
    }
    while(option!=3 || start==true);
    return 0;
}

void game(Player players[], Table& theTable)
{
    int NP = 0;//number of players
    createCards(theTable, "initial");
    NP = createPlayers(players, theTable);
    bool winner = false;
    while (!winner)
    {
        createCards4Players(players, theTable, NP);
        turns(players, theTable, NP);
        for (int i = 0; i < NP; i++) {
            if (players[i].score >= 500) {
                system("cls");
                cout << "El ganador es: " << players[i].nickname << endl << "Score: " << players[i].score << endl;
                winner = true;
            }
        }

    }
}

void header(){
    cout<<"  -------------------------------"<<"  -------------------------------"<<endl;
    cout<<"  |                              "<<" |                               |"<<endl;
    cout<<"  |      U   U  N   N   OOO      "<<" |           CREATED BY          |"<<endl;
    cout<<"  |      U   U  NN  N  O   O     "<<" |    David Alejandro Sequera    |"<<endl;
    cout<<"  |      U   U  N N N  O   O     "<<" |    Jaider David Daza Pardo    |"<<endl;
    cout<<"  |       UUU   N  NN   OOO      "<<" |    Jhoseph Samirt Lizarazo    |"<<endl;
    cout<<"  |                              "<<" |    Martin Zhaohong Chen He    |"<<endl;
    cout<<"  |                              "<<" |                               |"<<endl;
    cout<<"  -------------------------------"<<"  -------------------------------"<<"\n"<<endl;
}

void instructions(int idi)
{
    system("cls");
    if(idi==1)
    {
        cout<<"\n----- OBJETIVO DEL JUEGO  -----"<<endl;
        cout<<"\nEl objetivo de UNO es deshacerse de todas las cartas que se (roban) inicialmente, diciendo la palabra (UNO) cuando queda la ultima carta en la mano. El primero que llega a 500 puntos gana."<<endl;
        cout<<"\n\n-----PREPARACION DEL JUEGO-----"<<endl;
        cout<<"\n1. Se baraja las cartas y cada jugador recibe siete cartas. Las cartas restantes se ponen encubiertas en el centro y forman el mazo. La primera carta se desvela y se pone al lado. Este mazo es el mazo de descartes."<<endl;
        cout<<"\n2. El primero jugador pone una carta de su mano al mazo de descartes. Aqui vale: Una carta solo se puede superponer en una carta del mismo color o del mismo numero. Las cartas negras son cartas de accion especiales con reglas particulares."<<endl;
        cout<<"\n3. Si un jugador no puede poner la carta oportuna, tiene que tomar una carta de pena del mazo (Digitar 0)"<<endl;
        cout<<"\n4. Quien pone la penultima carta, debe decir (UNO), que indica que tiene la ultima carta en la mano. Si un jugador lo olvida y pasa al siguiente turno, tiene que tomar dos cartas de pena"<<endl;
        cout<<"\n5. El ganador de la ronda es el que depone la ultima carta. Los puntos se suman y se comienza una nueva ronda."<<endl;
        cout<<"\n\n-----  CARTAS DE ACCION   -----"<<endl;
        cout<<"\nCARTA TOMA DOS: El siguiente jugador debe tomar dos cartas y no puede deponer ninguna carta en esta ronda."<<endl;
        cout<<"\nCARTA DE RETORNO: Con esta carta se cambia la direccion. Si se ha jugado por la izquierda, ahora se juega por la derecha y por la inversa. La carta solo se puede superponer en una carta con color correspondiente o en una otra carta de retorno."<<endl;
        cout<<"\nCARTA DE INTERMISION (QUITAR TURNO): El siguiente jugador será (saltado). La carta solo se puede superponer en una carta con color correspondiente o en una otra carta de intermision. "<<endl;
        cout<<"\nCARTA DE ELECCION DE COLORES: El jugador decide que color sigue en el juego. Tambien el color presente puede ser seleccionado. "<<endl;
        cout<<"\nCARTA TOMA CUATRO: El jugador decide que color sigue en el juego. Ademas, el siguiente jugador debe tomar cuatro cartas. No se puede deponer cualquier carta en esta ronda.\n\n"<<endl;
    }
    else
    {
        cout<<"\n-----  OBJECT OF THE GAME   -----"<<endl;
        cout<<"\nThe first player to play all of the cards in their hand in each round scores points for the cards their opponents are left holding. The first player to score 500 points wins the game."<<endl;
        cout<<"\n\n-----  SETUP OF THE GAME  -----"<<endl;
        cout<<"\n1. The first player to play all of the cards in their hand in each round scores points for the cards their opponents are left holding. The first player to score 500 points wins the game."<<endl;
        cout<<"\n2. You must match the top card on the DISCARD pile either by number, color or word."<<endl;
        cout<<"\n3. If you don't have anything that matches, you must pick a card from the DRAW pile (type 0)"<<endl;
        cout<<"\n4. Before playing your next to last card, you must say (UNO). If you don't say UNO and the next player begins their turn you must pick TWO more cards from the DRAW pile."<<endl;
        cout<<"\n5. Once a player plays their last card, the hand is over. Points are tallied and you start over again."<<endl;
        cout<<"\n\n------   SPECIAL CARDS   ------"<<endl;
        cout<<"\nDRAW TWO CARD: When you play this card, the next person to play must draw 2 cards and forfeit his/her turn."<<endl;
        cout<<"\nREVERSE CARD: This card reverses direction of play. Play to the left now passes to the right, and vice versa."<<endl;
        cout<<"\nSKIP CARD: The next person in line to play after this card is played loses his/her turn and is (skipped). "<<endl;
        cout<<"\nWILD CARD: When you play this card, you may change the color being played to any color (including the current color) to continue play. "<<endl;
        cout<<"\nWILD DRAW FOUR CARD: This card allows you to call the next color played and requires the next player to pick 4 cards from the DRAW pile and forfeit his/her turn.\n\n" <<endl;
    }
    system("pause");
    system("cls");
}

//funciones para funcionalidad del juego

void turns(Player players[PLAYERS], Table& theTable, int NP)
{
    int i = 0;
    bool winner = false;
    while (!winner)
    {
        cout << "\nCarta Actual en el mazo:" << '\t' << theTable.deck[theTable.Ndeck].color << '\t' << theTable.deck[theTable.Ndeck].value << '\t' << theTable.deck[theTable.Ndeck].type << endl;
        cout << "Color Actual en el mazo:"<< '\t'  << theTable.color << endl;
        cout <<"\n"<<players[i].nickname << ": " << "\t\t\t" "Score:" << players[i].score << endl;
        cout <<"\tCartas actuales"<<endl;
        for (int j = 0; j < players[i].NCards; j++)
        {
            cout << '\t' << j + 1 << '\t' << players[i].deck[j].color << '\t' << players[i].deck[j].value << '\t' << players[i].deck[j].type;
            if(players[i].deck[j].value==10)
            {
                cout<<"\t- Toma dos"<<endl;
            }
            if(players[i].deck[j].value==11)
            {
                cout<<"\t- Cambio de sentido"<<endl;
            }
            if(players[i].deck[j].value==12)
            {
                cout<<"\t- Pierde turno"<<endl;
            }
            if(players[i].deck[j].value==13)
            {
                cout<<"\t- Cambio de color"<<endl;
            }
            if(players[i].deck[j].value==14)
            {
                cout<<"\t- Toma cuatro"<<endl;
            }
            if(players[i].deck[j].value<10)
            {
                cout<<endl;
            }
        }
        int S;//seleccion del jugador
        bool achieve = false;// comprobante
        do
        {
            cout <<"\n"<< players[i].nickname << " Selecciona una carta:" << endl;
            do
            {
                cin >> S;
            }
            while (S > players[i].NCards || S < 0);
            S--;
            if (S >= 0)
            {
                achieve = conditions(players[i].deck[S], theTable);
                if (achieve)
                {
                    Card tem = players[i].deck[S];
                    insertCard(theTable, players[i].deck[S]);
                    deleteCardPlayer(players[i], S);
                    //cambia tambien el color de la tabla
                    // Toma 2 == 10; Cambio de sentido == 11;Pierde turno == 12;Cambio de color == 13 ; Toma 4 == 14;
                    if (tem.value == 10) {
                        if (i == (NP-1)) {
                            insertCardPlayer(players[0], theTable);
                            insertCardPlayer(players[0], theTable);
                        }
                        else {
                            insertCardPlayer(players[i + 1], theTable);
                            insertCardPlayer(players[i + 1], theTable);
                        }
                    }
                    if (tem.value == 13) { askforColor(theTable); }
                    if (tem.value == 14) {
                        askforColor(theTable);
                        if (i == (NP - 1)) {
                            insertCardPlayer(players[0], theTable);
                            insertCardPlayer(players[0], theTable);
                            insertCardPlayer(players[0], theTable);
                            insertCardPlayer(players[0], theTable);
                        }
                        else {
                            insertCardPlayer(players[i + 1], theTable);
                            insertCardPlayer(players[i + 1], theTable);
                            insertCardPlayer(players[i + 1], theTable);
                            insertCardPlayer(players[i + 1], theTable);
                        }
                    }
                    if (tem.value == 12) {
                        i++;
                        if (i >= NP) { i = 0; }
                    }
                    if (tem.value == 11) {
                        reverse(players, NP, i);
                    }
                }
            }
            else
            {
                insertCardPlayer(players[i], theTable);
                achieve = true;
            }

        }
        while (!achieve);
        UNO(players[i], theTable);
        winner = winnerCheck(players[i]);
        i = winner?  i:i+1;
        if (i >= NP) {i = 0;}
        system("pause");
        system("cls");
        system("pause");
    }//fin de la ronda

    int score = 0;
    for (int u = 0; u < NP; u++) {
        for (int v = 0; v < players[u].NCards; v++) {
            score += players[u].deck[v].score;
        }
    }
    players[i].score += score;
}

void UNO(Player &player,Table &theTable) {
    if (player.NCards == 1) {
        string uno;
        cout << "Dijiste UNO" << endl;
        cout << "Si, escribe UNO" << endl;
        cout << "No, escribe No" << endl;
        do
        {
            getline(cin, uno);
        } while (uno != "UNO" && uno != "No");
        if (uno == "No") {
            insertCardPlayer(player, theTable);
            insertCardPlayer(player, theTable);
        }
    }
}

bool winnerCheck(Player player) {
    if (player.NCards == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool conditions(Card Cplayer, Table table)
{
    cout << "\nCarta seleccionada: "  << Cplayer.color << '\t' << Cplayer.value << '\t' << Cplayer.type << endl;
    if (Cplayer.color != "Black")
    {
        if (Cplayer.color != table.color && Cplayer.value != table.deck[table.Ndeck].value)
        {
            cout << "\n[You can't pick this card!]" << endl;
            return false;
        }
    }
    return true;
}

void askforColor(Table& theTable)
{
    string color;
    cout << "Seleccione un color" << endl;
    cout << "Red, Green, Blue, Yellow" << endl;
    do
    {
        getline(cin, color);
        cout << "Color: " << color << endl;
    }
    while (color != "Red" && color != "Green" && color != "Blue" && color != "Yellow");
    theTable.color = color;
}

void reverse(Player players[PLAYERS], int size, int &i)
{
    Player copy[PLAYERS];
    for (int u = 0; u < size; u++)
    {
        copy[u] = players[u];
    }//Hacer una copia
    int u = size - 1;
    int v = 0;
    do
    {
        players[u] = copy[v];
        u--;
        v++;
    }
    while (u > -1);
    i = abs(i - size + 1);//Arregla la posicion
}



//funciones para manejo de arreglos


void createCards(Table& a, string x)
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

            // VARIBLE      =   CONDICION ?    SI :    NO;
            a.pick[i].value = value <= 12 ? value : (value - 13);


            a.pick[i].score = a.pick[i].value > 9 ? 20 : a.pick[i].value;
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
            a.pick[i].score = 50;
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


    //Anadir carta a deck
    if (x == "initial") {
        a.Ndeck = 0;
        int PickP = 0;//posicion
        while (a.pick[PickP].type == "Special")
        {
            PickP++;    //garantizar que primera carta no es especial
        }
        Card PickCard = a.pick[0];
        a.pick[0] = a.pick[PickP];
        a.pick[PickP] = PickCard;
        a.deck[a.Ndeck] = a.pick[0];
        a.color = a.deck[a.Ndeck].color;
        deleteCard(a);
    }
}; //crea maso de 108 en pick y carta inicial

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
}//elimina una carta del inicio de pick

void insertCard(Table& theTable, Card card)
{
    if (theTable.color != card.color)
    {
        theTable.color = card.color;
    }
    theTable.Ndeck++;
    theTable.deck[theTable.Ndeck] = card;
}//inserta una carta en deck

void insertCardPlayer(Player& thePlayer, Table& table)
{
    if (table.Npick == 0) {
        createCards(table, "Nan");
    }
    thePlayer.deck[thePlayer.NCards] = table.pick[0];
    thePlayer.NCards++;
    deleteCard(table);
}//inserta una carta en jugador

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
}//elimina una carta de jugador, por indice

int mockingPlayers(Player players[], Table &table)
{
    players[0].nickname = "Martin";
    players[1].nickname = "Jhoseph";
    players[2].nickname = "Jaider";
    players[3].nickname = "David";
    for (int i = 0; i < 4; i++)
    {
        players[i].NCards = 0;
        players[i].score = 0;
        for (int j= 0; j < 7; j++)
        {
            insertCardPlayer(players[i], table);
        }
    }
    return 4;
}//crea los jugadores

int createPlayers(Player players[], Table& table)
{
    int NP = 0;
    cout << "Cuantos Jugadores Van a jugar: max."<< PLAYERS << endl;
    do
    {
        cin >> NP;
    } while (NP > PLAYERS || NP <= 0);
    cin.ignore(1);
    cout << "Ingrese los nombres:" << endl;
    for (int i = 0; i < NP; i++) {
       //cin >> players[i].nickname;
       getline(cin, players[i].nickname);
       players[i].score = 0;
    }

    system("cls");
    return NP;
}//crea los jugadores y retorna el numero de ellos

void createCards4Players(Player players[], Table& table, int NP) {
    for (int i = 0; i < NP; i++)
    {
        players[i].NCards = 0;
        for (int j = 0; j < 7; j++)
        {
            insertCardPlayer(players[i], table);
        }
    }
}
