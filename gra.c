/*************************************
Gra
Autorzy: Jedrzej Kubala, Zuzanna Krzysztofik

Plik zawiera podstawowe funkcje wykorzystywane w grze Hneftafl:

gra()

zainicjuj_plansze()
wypisz_plansze()
sprawdz_zwyciestwo()
*************************************/

#include <stdio.h>
#include "ruch.h"
#include "bicie.h"

char plansza[12][12];   //Deklaruje plansze jako zmienna globalna.

/*Deklaracje funkcji*/
int gra(void);
void zainicjuj_plansze (void);
void wypisz_plansze(void);
int sprawdz_zwyciestwo(int krol_uwolniony, int krol_x, int krol_y);
int krol_otoczony(int krol_x, int krol_y, int czy_krol);

/*/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/*/
/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/*Glowna funkcja, ktora rozgrywa partie pomiedzy 2 graczami w Hneftafla */
int gra(void) {
    int start_x=0, start_y=0, end_x=0, end_y=0, krol_x=6, krol_y=6; //wspolrzedne pola startowego, pola docelowego i krola
    int *p_start_x=&start_x, *p_start_y=&start_y, *p_end_x=&end_x, *p_end_y=&end_y, *p_krol_x=&krol_x, *p_krol_y=&krol_y; //wskazniki do powyzszych zmiennych
    int zwyciestwo=0; //0 - nierozstrzygniete, 1 - wygral gracz 1, 2 - wygral gracz 2.
    int krol_uwolniony=0; //0 - krol na planszy, 1 - krolowi udalo sie uciec (zwyciestwo gracza 1)
    int licznik_ruchow=0;
    int gracz_aktywny; //1 - gracz 1; 2 - gracz 2.

/*       Rozpoczynamy gre                                         */

    zainicjuj_plansze();
    printf("----------------------------\n");
    printf("    Rozpoczynam nowa gre    \n");
    printf("----------------------------\n\n");

    do {
        /*Na poczatek aktualizujemy licznik ruchow, okreslamy ktory gracz jest aktywny i wypisujemy plansze */
        licznik_ruchow++;
        gracz_aktywny=2-(licznik_ruchow%2);
        wypisz_plansze();
        printf("\nRuch wykonuje gracz %i.\n", gracz_aktywny);
        /*Teraz pozwalamy wykonac graczowi ruch, sprawdza jego poprawnosc, aktualizuje plansze i wspolrzedne.
        Dodatkowo ustawiamy wartosc zmiennej krol_uwolniony na 1, jesli pionek krola dortarl do rogu. */
        krol_uwolniony=ruch(gracz_aktywny,p_start_x,p_start_y,p_end_x,p_end_y,p_krol_x,p_krol_y);
        /*Teraz sprawdzamy i wykonujemy bicie dla pola docelowego */
        bicie(end_x, end_y, gracz_aktywny);
        /* Teraz sprawdzamy, czy jeden z graczy nie osiagnal zwyciestwa*/
        zwyciestwo=sprawdz_zwyciestwo(krol_uwolniony, krol_x, krol_y);   //Ustawia wartosc zmiennej zwyciestwo na 1, jesli spelnione sa warunki wygranej
        /*Petla ta bedzie wykonywac sie tak dlugo, az wygra jeden z graczy*/
    } while (zwyciestwo==0); //Warunek wyjscia z petli w momencie osiagniecia zwyciestwa przez jednego z graczy
    /*Gra zakonczona, wypisujemy wynik i plansze */
    wypisz_plansze();
    printf("\nKoniec gry. Zwyciezyl gracz %i. Gra zakonczyla sie w %i ruchach.\n\n", zwyciestwo, licznik_ruchow);
    /*Wracamy do funkcji main */
    return zwyciestwo;
}

/*/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/*/
/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/

/* Funkcja inicjalizuje plansze na:
 a b c d e f g h i j k
1 o . . X X X X X . . o
2 . . . . . X . . . . .
3 . . . . . . . . . . .
4 X . . . . & . . . . X
5 X . . . & & & . . . X
6 X X . & & $ & & . X X //pole tronowe jest du¿ym O
7 X . . . & & & . . . X
8 X . . . . & . . . . X
9 . . . . . . . . . . .
10. . . . . X . . . . .
11o . . X X X X X . . o
*/
void zainicjuj_plansze (void) {
    int x, y=0;
    char litera='@', cyfra='0';
    plansza[0][0]=' ';
    for (x = 1; x <= 11; x++){
        plansza[x][y] = litera;   //Pierwszy rzad to litery indeksujace plansze
    }
    for (y = 1; y <= 11; y++) {
        plansza[0][y]=cyfra+y;  //Pierwsza kolumna to liczby indeksujace plansze
        for (x = 1; x <= 12; x++){
            if (((x==1)||(x==11))&&((y==1)||(y==11))) plansza[x][y] = 'o';  //Pola narozne
            else if ((x==6)&&(y==6)) plansza[x][y] = '$';   //Pole tronowe z krolem
            else if (((y==6)&&(x>=4)&&(x<=8))
                     ||((x==6)&&(y>=4)&&(y<=8))
                     ||((x==5)||(x==7))&&((y==7)||(y==5))) plansza[x][y] = '&';   //Pionki krola - gracza 1
            else if ((((x==6)&&(y==2))||((y==6)&&(x==2)))
                     ||(((x==6)&&(y==10))||((y==6)&&(x==10)))
                     ||(((y==1))&&((x>=4)&&(x<=8)))
                     ||(((y==11))&&((x>=4)&&(x<=8)))
                     ||(((x==1))&&((y>=4)&&(y<=8)))
                     ||(((x==11))&&((y>=4)&&(y<=8)))) plansza[x][y] = 'X'; //Pionki napastnika - gracza 2
            else plansza[x][y] = '.';
        }
    }
}

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/*Funkcja wypisuje plansze w aktualnym stanie */
void wypisz_plansze(void) {
    int x, y;
        printf("\n%2c",' ');
    for (x = 1; x < 12; x++){
        printf("%2c", '@'+x);   //Wypisuje numery indeksujace kolumny
    }
    printf("\n");
    for (y = 1; y < 12; y++){
        printf("%2i", y);   //Wypisuje liczby indeksujace wiersze
        for (x = 1; x < 12; x++){
            printf("%2c", plansza[x][y]);   //Wypisuje plansze
        }
        printf("\n");
    }
}

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/*Jesli nie nastapily warunki zwyciestwa, zwraca 0.
Jesli wygral jeden z graczy, zwraca jego numer. */
int sprawdz_zwyciestwo(int krol_uwolniony, int krol_x, int krol_y) {
    int i, j, krol_otoczon;
    if (krol_uwolniony) return 1;
    krol_otoczon=(krol_otoczony(krol_x, krol_y, 1));
    for (i=1; i<=11; i++) {
        for (j=1; j<=11; j++) { //Poniewaz rekurencja troche nasmiecila, sprzatamy
            if (plansza[i][j]=='#') plansza[i][j]='&';
            if (plansza[i][j]=='@') plansza[i][j]='$';
        }
    }
    if (krol_otoczon==0) return 2;
    return 0;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*Rekurencyjnie sprawdza otoczenie krola.
Jesli krol jest otoczony, zwraca  */
int krol_otoczony(int x, int y, int czy_krol) {
    int i=0;
    int krol=0; //Jest ustawiana na 1, jesli na polu jest krol, aby przekazac to wywolaniu rekurencyjnemu jako 3. argument
    if ((plansza[x][y]=='@')||(plansza[x][y]=='#')) return 0; //To znaczy, ze to pole juz sprawdzalismy.
    if (plansza[x][y]=='$') {
        krol=1;
        plansza[x][y]='@'; //Zamieniamy krola na @, zeby sie nie powtarzac
    }
    if (plansza[x][y]=='&') plansza[x][y]='#';  //Zamieniamy pionek na #, zeby sie nie powtarzac

    if ((x==0)||(x==12)||(y==0)||(y==12)) return 0; //Jesli dojechalismy do brzegu, otacza nas
    if (plansza[x][y]=='X') return 0;   //Jesli dojechalismy do pionka atakujacego, otacza nas
    if (plansza[x][y]=='.') return 1;   //Jesli dojechalismy do pustego pola, wyzwala nas
    if ((plansza[x][y]=='o')||(plansza[x][y]=='O')) {   //Jesli dojechalismy do pola naroznego lub tronowego, zalezy:
        if (czy_krol) return 1; //Jesli dojechalismy krolem, wyzwala nas
        else return 0;  //Jesli dojechalismy zwyklym plebsem, otacza nas
    }
    //Jesli na polu stoi krol lub pionek krolewski, rekurencyjnie sprawdzamy pola obok
    i+=krol_otoczony(x-1,y,krol); //pole po lewej
    i+=krol_otoczony(x+1,y,krol); //pole po prawej
    i+=krol_otoczony(x,y-1,krol); //pole u gory
    i+=krol_otoczony(x,y+1,krol); //pole u dolu
    return i;   //Jesli gdziekolwiek sie uwolnilismy, funkcja zwroci liczbe dodatnia. Jesli jestesmy zewszad otoczeni, zwroci 0.
}
