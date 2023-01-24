#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

typedef char typFormule[5];

void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

//Convertit tout en majuscule
char toUpper(char c)
{
    return toupper(c);
}

//Colore mes chaines de caracteres
string colorize(const std::string& str, const std::string& colorCode)
{
    return colorCode + str + "\033[0m";
}


//Fonction pour placer chaque element a une place precise
void afficheValeur(int x, int y, int val){
    gotoxy(x, y);
    cout << val;
}


//Fonction pour controle si les couleurs entrer par l'utilisateur sont valide
bool carcaValide(char c) {
    int i = 0;
    char varCouleur[7] = {'R','V','J','B','R','C','G'};
    while(varCouleur[i] != c && i < 6) {
        i++;
    }
    return(varCouleur[i] == c);
}



//Fonction pour choisir les couleurs que l'on veut dans son code
char saisieCouleur(int x, int y) {
    char c;
    do {
        gotoxy(x, y);
        c = getch();
        c = toUpper(c);
        cout << c;

    }while (!carcaValide(c));
    return c ;
}

//Fonction pour caculer si les couleurs sont bien places
int calculBp(typFormule &vec1, typFormule &vec2){
    int Bp = 0;
    for(int i = 0; i < 5; i++) {
        if(vec1[i] == vec2[i]){
            Bp = Bp + 1;
            vec1[i] = 'X';
            vec2[i] = 'Y';
        }
    }
    return Bp;
}

//Fonction pour caculer si les couleurs sont mal places
int calculMp(typFormule &vec1, typFormule &vec2) {
    int Mp = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(vec1[i] == vec2[j]){
                Mp = Mp + 1;
                vec1[i] = 'X';
                vec2[j] = 'Y';
            }
        }
    }
    return Mp;
}


int main() {

    string retry = "Y" ;

    //Boucle pour relancer le jeu
    while (retry == "Y" || retry == "y") {

    typFormule varOriginal, varCopie, varEssai;
    int Bp, Mp, nbEssai;
    int i;
    int x, y;
    char couleur;

    // Boucle pour remplir la variable varOriginal
    for(i = 0; i < 5; i++) {
        gotoxy(0,0);
        cout << "Entrez votre code secret !";
        gotoxy(30,0);
        cout << colorize("'R'", "\033[1;31m") << colorize(" 'V'", "\033[1;32m") << colorize(" 'J'", "\033[1;33m") << colorize(" 'B'", "\033[1;34m") << colorize(" 'R'", "\033[1;35m") << colorize(" 'C'", "\033[1;36m") << colorize(" 'G'", "\033[1;37m") ;
        gotoxy(0, 3);
        cout << "Joueur 1";
        couleur = saisieCouleur(10 + i*4,3);
        varOriginal[i] = couleur;
    }

    nbEssai = 0;
    system("cls");
    gotoxy(0,0);
    cout << "Tentez de decouvrir le code secret ! " << colorize("'R'", "\033[1;31m") << colorize(" 'V'", "\033[1;32m") << colorize(" 'J'", "\033[1;33m") << colorize(" 'B'", "\033[1;34m") << colorize(" 'R'", "\033[1;35m") << colorize(" 'C'", "\033[1;36m") << colorize(" 'G'", "\033[1;37m") ;
    gotoxy(0,1);
    cout << "Joueur 2";
    gotoxy(0, nbEssai + 1 );

    //Incremente varEssai et copie varOriginal dans la variable varCopie
    do {
        nbEssai = nbEssai + 1;
        gotoxy(7, nbEssai + 1);
        cout << "Essai " << nbEssai;
        for(i = 0; i < 5; i++) {
            couleur = saisieCouleur(20 + i*4, nbEssai + 1);
            varEssai[i] = couleur;
			varCopie[i] = varOriginal[i];
        }
        Bp = calculBp(varCopie, varEssai);
        gotoxy(85, nbEssai + 1);
        cout << "Bien place: ";
        afficheValeur(87 + i*2, nbEssai + 1, Bp);

        Mp = calculMp(varCopie, varEssai);
        gotoxy(70, nbEssai + 1);
        cout << "Mal place: ";
        afficheValeur(71 + i*2, nbEssai + 1, Mp);

    } while(Bp != 5);

    //Permet d'afficher un etat quand le joueur a touver la bonne reponse
    if(nbEssai <= 5){
        gotoxy(40,nbEssai + 5);
        cout << " Bravo !!!";
    } else if(nbEssai <= 10){
        gotoxy(40,nbEssai + 5);
        cout << "  Correct !";
    } else{
        gotoxy(40,nbEssai + 5);
        cout << "  Decevant.";
    }
    gotoxy(20,nbEssai + 5);
    cout << "Nombre d'essais: " << nbEssai << " -";

    gotoxy(70,nbEssai + 5);
    cout << "VOULEZ-VOUS RELANCER ?? (Y/N)  ";
    gotoxy(70, nbEssai + 30);
    cin >> retry;
    system("cls");
    }

    return 0;
}
