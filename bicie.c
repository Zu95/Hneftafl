/*************************************
Ruch
Autorzy: Jedrzej Kubala, Zuzanna Krzysztofik

Plik zawiera funkcje wykorzystywane w grze Hneftafl do sprawdzenia i wykonania bicia:

bicie()

sprawdz_bicie()
zbij()
*************************************/

#include <stdio.h>

extern char plansza[12][12];   //Deklaruje plansze jako zmienna globalna.

/*Deklaracje funkcji*/
int sprawdz_bicie_lewo(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
int sprawdz_bicie_prawo(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
int sprawdz_bicie_gora(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
int sprawdz_bicie_dol(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny);
void bicie(int end_x, int end_y, int gracz_aktywny);
void zbij(int zbity_x, int zbity_y);

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/*Funkcja sprawdza i wykonuje bicie:
1. Sprawdza, czy nastapilo bicie
2. Zmienia stan planszy */
void bicie(int end_x, int end_y, int gracz_aktywny) {
    int czy_bicie;
    int zbity_x, zbity_y; //wspolrzedne pionka zbijanego
    int *p_zbity_x=&zbity_x, *p_zbity_y=&zbity_y; //wskazniki do tych wspolrzednych
    /*Sprawdzamy bicie we wszystkich 4 kierunkach */
    czy_bicie=sprawdz_bicie_lewo(end_x, end_y, p_zbity_x, p_zbity_y, gracz_aktywny);    //W lewo
    if(czy_bicie) zbij(zbity_x, zbity_y);
    czy_bicie=sprawdz_bicie_prawo(end_x, end_y, p_zbity_x, p_zbity_y, gracz_aktywny);    //W prawo
    if(czy_bicie) zbij(zbity_x, zbity_y);
    czy_bicie=sprawdz_bicie_gora(end_x, end_y, p_zbity_x, p_zbity_y, gracz_aktywny);    //W gore
    if(czy_bicie) zbij(zbity_x, zbity_y);
    czy_bicie=sprawdz_bicie_dol(end_x, end_y, p_zbity_x, p_zbity_y, gracz_aktywny);    //W dol
    if(czy_bicie) zbij(zbity_x, zbity_y);
}

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/*Ponizsze funkcje sprawdzaja, czy nastapilo bicie.
1. Sprawdzaja czy na polu o 1 dalej znajduje sie pionek wroga
2. Sprawdzaja czy na nastepnym polu znajduje sie pionek gracza zbijajacego lub pole tronowe lub narozne albo brzeg planszy
3. Jesli bicie nastapilo, wczytuja poprzez wskazniki wspolrzedne zbijanego pionka i zwracaja 1. Inaczej zwracaja 0.
*/
/* Funkcja sprawdza, czy nastapilo bicie w lewo. */
int sprawdz_bicie_lewo(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny) {
    if(gracz_aktywny==1){   //dla pierwszego gracza
        if ((end_x-1>0)&&(plansza[end_x-1][end_y]=='X')){ //sprawdza czy na polu w lewo znajduje sie pionek przeciwnika
            if(((end_x-2)==0) //czy lewa krawedz planszy
            || (plansza[end_x-2][end_y]=='&') //czy pionek gracza
            || (plansza[end_x-2][end_y]=='O') //czy pole tronowe
            || (plansza[end_x-2][end_y]=='o')){ //czy naroznik
                *p_zbity_x=(end_x-1);
                *p_zbity_y=(end_y);
                return 1;
            }
        }
    }
    else { //dla drugiego gracza
        if ((end_x-1>0)&&(plansza[end_x-1][end_y]=='&')){ //sprawdza czy na polu w lewo znajduje sie pionek przeciwnika
            if((end_x-2)==0 //czy lewa krawedz planszy
            || plansza[end_x-2][end_y]=='X' //czy pionek gracza
            || plansza[end_x-2][end_y]=='O' //czy pole tronowe
            || plansza[end_x-2][end_y]=='o'){ //czy naroznik
                *p_zbity_x=end_x-1;
                *p_zbity_y=end_y;
                return 1;
            }
        }
    }
    return 0;   //Jezeli zaden z warunkow nie zostal spelniony zwraca 0
}
/* Funkcja sprawdza, czy nastapilo bicie w prawo. */
int sprawdz_bicie_prawo(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny) {
    if(gracz_aktywny==1){   //dla pierwszego gracza
        if ((end_x+1<12)&&(plansza[end_x+1][end_y]=='X')){ //sprawdza czy na polu w prawo znajduje sie pionek przeciwnika
            if((end_x+2)==12 //czy prawa krawedz planszy
            || plansza[end_x+2][end_y]=='&' //czy pionek gracza
            || plansza[end_x+2][end_y]=='O' //czy pole tronowe
            || plansza[end_x+2][end_y]=='o'){ //czy naroznik
                *p_zbity_x=end_x+1;
                *p_zbity_y=end_y;
                return 1;
            }
        }
    }
    else { //dla drugiego gracza
        if ((end_x+1<12)&&(plansza[end_x+1][end_y]=='&')){ //sprawdza czy na polu w prawo znajduje sie pionek przeciwnika
            if((end_x+2)==12 //czy prawa krawedz planszy
            || plansza[end_x+2][end_y]=='X' //czy pionek gracza
            || plansza[end_x+2][end_y]=='O' //czy pole tronowe
            || plansza[end_x+2][end_y]=='o'){ //czy naroznik
                *p_zbity_x=end_x+1;
                *p_zbity_y=end_y;
                return 1;
            }
        }
    }
    return 0;   //Jezeli zaden z warunkow nie zostal spelniony zwraca 0
}
/* Funkcja sprawdza, czy nastapilo bicie w gore. */
int sprawdz_bicie_gora(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny) {
    if(gracz_aktywny==1){   //dla pierwszego gracza
        if ((end_y-1>0)&&(plansza[end_x][end_y-1]=='X')){ //sprawdza czy na polu w gore znajduje sie pionek przeciwnika
            if((end_y-2)==0 //czy gorna krawedz planszy
            || plansza[end_x][end_y-2]=='&' //czy pionek gracza
            || plansza[end_x][end_y-2]=='O' //czy pole tronowe
            || plansza[end_x][end_y-2]=='o'){ //czy naroznik
                *p_zbity_x=end_x;
                *p_zbity_y=end_y-1;
                return 1;
            }
        }
    }
    if(gracz_aktywny==2){   //dla drugiego gracza
        if ((end_y-1>0)&&(plansza[end_x][end_y-1]=='&')){ //sprawdza czy na polu w gore znajduje sie pionek przeciwnika
            if((end_y-2)==0 //czy gorna krawedz planszy
            || plansza[end_x][end_y-2]=='X' //czy pionek gracza
            || plansza[end_x][end_y-2]=='O' //czy pole tronowe
            || plansza[end_x][end_y-2]=='o'){ //czy naroznik
                *p_zbity_x=end_x;
                *p_zbity_y=end_y-1;
                return 1;
            }
        }
    }
    return 0;   //Jezeli zaden z warunkow nie zostal spelniony zwraca 0
}
/* Funkcja sprawdza, czy nastapilo bicie w dol. */
int sprawdz_bicie_dol(int end_x, int end_y, int *p_zbity_x, int *p_zbity_y, int gracz_aktywny) {
    if(gracz_aktywny==1){   //dla pierwszego gracza
        if ((end_y+1<12)&&(plansza[end_x][end_y+1]=='X')){ //sprawdza czy na polu w dol znajduje sie pionek przeciwnika
            if((end_y+2)==12 //czy dolna krawedz planszy
            || plansza[end_x][end_y+2]=='&' //czy pionek gracza
            || plansza[end_x][end_y+2]=='O' //czy pole tronowe
            || plansza[end_x][end_y+2]=='o'){ //czy naroznik
                *p_zbity_x=end_x;
                *p_zbity_y=end_y+1;
                return 1;
            }
        }
    }
    else { //dla drugiego gracza
        if ((end_y+1<12)&&(plansza[end_x][end_y+1]=='&')){ //sprawdza czy na polu w dol znajduje sie pionek przeciwnika
            if(end_y+2==12
                //czy dolna krawedz planszy
            || plansza[end_x][end_y+2]=='X' //czy pionek gracza
            || plansza[end_x][end_y+2]=='O' //czy pole tronowe
            || plansza[end_x][end_y+2]=='o'){ //czy naroznik
                *p_zbity_x=end_x;
                *p_zbity_y=end_y+1;
                return 1;
            }
        }
    }
    return 0;   //Jezeli zaden z warunkow nie zostal spelniony zwraca 0
}

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/*Funkcja wykonuje bicie:
Usuwa zbijany pionek z pola.
*/
void zbij(int zbity_x, int zbity_y) {
	plansza[zbity_x][zbity_y]='.';
//Zuzia
}
