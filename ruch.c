/*************************************
Ruch
Autorzy: Jedrzej Kubala, Zuzanna Krzysztofik

Plik zawiera funkcje wykorzystywane w grze Hneftafl do wczytania i wykonania ruchu:

ruch()

wczytaj_ruch()
sprawdz_ruch()
wykonaj_ruch()
tonumber()
*************************************/

#include <stdio.h>
#include <stdlib.h> //koniecnze do wartosci bezwzglednej

extern char plansza[12][12];   //Deklaruje plansze jako zmienna globalna.

/*Deklaracje funkcji*/
int ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y, int *p_krol_x, int *p_krol_y);
void wczytaj_ruch(int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y);
int sprawdz_ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y);
int wykonaj_ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y, int *p_krol_x, int *p_krol_y);
int tonumber(char character);

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/*Funkcja wykonuje ruch:
1. Pozwala graczowi wprowadzic wspolrzedne
2. Sprawdza poprawnosc ruchu
3. Zmienia stan planszy
4. Zwraca 1 jesli ruch konczy sie uwolnieniem krola, 0 w kazdym innym wypadku.
*/
int ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y, int *p_krol_x, int *p_krol_y) {
    int poprawny_ruch=0;
    do {
    wczytaj_ruch(p_start_x,p_start_y,p_end_x,p_end_y);
    poprawny_ruch=sprawdz_ruch(gracz_aktywny, p_start_x,p_start_y,p_end_x,p_end_y);
    if (poprawny_ruch==0) printf("Nie wolno Ci wykonac takiego ruchu. Odyn zabrania. Sprobuj raz jeszcze.\n");
    } while (poprawny_ruch==0);
    return wykonaj_ruch(gracz_aktywny,p_start_x,p_start_y,p_end_x,p_end_y,p_krol_x,p_krol_y);
}

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/* Funkcja wprowadza ruch:
Pozwala graczowi wprowadzic wspolrzedne ruchu, wczytuje je do zmiennych poprzez wskazniki.
 */
void wczytaj_ruch(int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y) {
    char linia[8];
    char start_x_char=0, end_x_char=0;
    int i, poprawny=0;
    *p_start_x=0; *p_start_y=0; *p_end_x=0; *p_end_y=0; //Czyszcze zmienne z poprzedniego ruchu
    do {
        fgets(linia, 7, stdin); //Wczytuje z wejscia standardowego ciag znakow podany przez gracza
        for (i=0; linia[i]!='\0'; i++) linia[i]=(tolower(linia[i]));
        sscanf(linia, "%c%i%c%i", &start_x_char, p_start_y, &end_x_char, p_end_y);
        *p_start_x=tonumber(start_x_char);
        *p_end_x=tonumber(end_x_char);
        if(((*p_start_x>=1)&&(*p_start_x<=11))
           &&((*p_start_y>=1)&&(*p_start_y<=11))
           &&((*p_end_x>=1)&&(*p_end_x<=11))
           &&((*p_end_x>=1)&&(*p_end_x<=11))
           &&(((*p_end_x!=*p_start_x)&&(*p_end_y==*p_start_y))
           ||((*p_end_x==*p_start_x)&&(*p_end_y!=*p_start_y)))){
           poprawny=1;
        } else printf("Wiem ze wiking nie umie pisac, ale wprowadz prawidlowe dane.\n");
    } while (poprawny==0);
    return;
//np. e4c10 - program zjada to do czterech zmiennych start_x=5, start_y=4, end_x=3, end_y=10
//Jedrzej
}
/* Funkcja pomocmnicza do wczytaj_ruch, ktora zmienia wspolrzedne literowe na liczbowe */
int tonumber(char character) {
    if (character=='a') return 1;
    if (character=='b') return 2;
    if (character=='c') return 3;
    if (character=='d') return 4;
    if (character=='e') return 5;
    if (character=='f') return 6;
    if (character=='g') return 7;
    if (character=='h') return 8;
    if (character=='i') return 9;
    if (character=='j') return 10;
    if (character=='k') return 11;
    return 0;
}
/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/

/* Funkcja sprawdza ruch:
1. Sprawdza czy na startowym polu znajduje sie pionek aktywnego gracza
3. Sprawdza czy wspolrzedne ruchu znajduja sie w tej samej linii
2. Sprawdza czy pole docelowe jest dozwolone
4. Sprawdza czy na trasie ruchu nie ma innego pionka
5. Jesli wszystkie warunki zostaly spelnione, zwraca 1. W przeciwnym razie zwraca 0
 */
int sprawdz_ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y) {
    int flag=0, tmp, i, licznik=0;
    if(gracz_aktywny==1){ //pierwszy gracz
/* Jezeli poruszanym pionkiem jest & */
        if(plansza[*p_start_x][*p_start_y]=='&'){ //sprawdzam czy pionek istnieje
            if(plansza[*p_end_x][*p_end_y]=='.'){ //czy pole docelowe jest wolne
                if(*p_start_y==*p_end_y){ //jesli są w jednej linii po osi x
                    tmp=abs(*p_start_x-*p_end_x)-1; //odleglosc miedzy pionkami
                    if(*p_start_x<*p_end_x){ //jezeli pionek jest z lewej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x+i][*p_start_y]=='.') licznik++;
                    	}
                    }
                    else if (*p_start_x>*p_end_x){ //jezeli pionek z prawej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x-i][*p_start_y]=='.') licznik++;
                        }
                    }
                    if(licznik==tmp) flag=1;
                }
                else if(*p_start_x==*p_end_x){ //czy sa w jednej linii po osi y
                    tmp=abs(*p_start_y-*p_end_y)-1; //obliczam odległosc
                    if(*p_start_y<*p_end_y){ //jezeli pionek jest powyżej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x][*p_start_y+i]=='.') licznik++;
                    	}
                    }
                    else if (*p_start_y>*p_end_y){ //jezeli pionek poniżej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x][*p_start_y-i]=='.') licznik++;
                        }
                    }
                    if(licznik==tmp) flag=1;
                }
            }
        }
/* Jezeli poruszanym pionkiem jest krol */
        if(plansza[*p_start_x][*p_start_y]=='$'){ //sprawdzam czy krol
            if(plansza[*p_end_x][*p_end_y]=='.' //czy pole docelowe jest wolne
               || plansza[*p_end_x][*p_end_y]=='O'  //lub narozne
               || plansza[*p_end_x][*p_end_y]=='o'){    //lub tronowe
                if(*p_start_y==*p_end_y){ //jesli są w jednej linii po osi x
                    tmp=abs(*p_start_x-*p_end_x)-1; //odleglosc miedzy pionkami
                    if(*p_start_x<*p_end_x){ //jezeli pionek jest z lewej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x+i][*p_start_y]=='.') licznik++;
                    	}
                    }
                    else if (*p_start_x>*p_end_x){ //jezeli pionek z prawej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x-i][*p_start_y]=='.') licznik++;
                        }
                    }
                    if(licznik==tmp) flag=1;
                }
                else if(*p_start_x==*p_end_x){ //czy sa w jednej linii po osi y
                    tmp=abs(*p_start_y-*p_end_y)-1; //obliczam odległosc
                    if(*p_start_y<*p_end_y){ //jezeli pionek jest powyżej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x][*p_start_y+i]=='.') licznik++;
                    	}
                    }
                    else if (*p_start_y>*p_end_y){ //jezeli pionek poniżej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x][*p_start_y-i]=='.') licznik++;
                        }
                    }
                    if(licznik==tmp) flag=1;
                }
            }
		}
    }
/* Jezeli poruszanym pionkiem jest X */
    if(gracz_aktywny==2){ //drugi gracz
        if(plansza[*p_start_x][*p_start_y]=='X'){ //sprawdzam czy pionek istnieje
            if(plansza[*p_end_x][*p_end_y]=='.'){ //czy pole docelowe jest wolne
                if(*p_start_y==*p_end_y){ //jesli są w jednej linii po osi x
                tmp=abs(*p_start_x-*p_end_x)-1; //odleglosc miedzy pionkami
                    if(*p_start_x<*p_end_x){ //jezeli pionek jest z lewej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x+i][*p_start_y]=='.') licznik++;
                    	}
                    }
                    else if (*p_start_x>*p_end_x){ //jezeli pionek z prawej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x-i][*p_start_y]=='.') licznik++;
                        }
                    }
                    if(licznik==tmp) flag=1;
                }
                else if(*p_start_x==*p_end_x){ //czy sa w jednej linii po osi y
                    tmp=abs(*p_start_y-*p_end_y)-1; //obliczam odległosc
                    if(*p_start_y<*p_end_y){ //jezeli pionek jest powyżej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x][*p_start_y+i]=='.') licznik++;
                    	}
                    }
                    else if (*p_start_y>*p_end_y){ //jezeli pionek poniżej
                    	for(i=1; i<=tmp; i++){
                    		if(plansza[*p_start_x][*p_start_y-i]=='.') licznik++;
                        }
                    }
                    if(licznik==tmp) flag=1;
                }
            }
        }
    }
    return flag;
    //Zuzia
}

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\*/
/* Funkcja wykonuje ruch:
1. Usuwa pionek ze startowego pola
2. Umieszcza pionek na docelowym polu
3. Jesli pionkiem byl krol, aktualizuje jego wspolrzedne
4. Jesli ruch konczy sie uwolnieniem krola, zwraca 1. W przeciwnym razie zwraca 0.
 */
int wykonaj_ruch(int gracz_aktywny, int *p_start_x, int *p_start_y, int *p_end_x, int *p_end_y, int *p_krol_x, int *p_krol_y) {
    int flag=0; //oznaczenie
    if(gracz_aktywny==1){ //dla gracza 1
        if(plansza[*p_start_x][*p_start_y]=='$' && plansza[*p_end_x][*p_end_y]=='o') flag=1; //warunek uwolnienia krola
        if(plansza[*p_start_x][*p_start_y]=='$'){ //w przypadku krola
            if((*p_start_x==6)&&(*p_start_y==6)) plansza[*p_start_x][*p_start_y]='O';
            else plansza[*p_start_x][*p_start_y]='.';
            plansza[*p_end_x][*p_end_y]='$';
            *p_krol_x=*p_end_x;                 //zmieniam wspolrzedne krola
            *p_krol_y=*p_end_y;
        }
        else{
            plansza[*p_start_x][*p_start_y]='.'; //przesuwam zwykly pionek
            plansza[*p_end_x][*p_end_y]='&';
        }
    }
    else if(gracz_aktywny==2){ //dla gracza 2
        plansza[*p_start_x][*p_start_y]='.';
        plansza[*p_end_x][*p_end_y]='X';
    }

    return flag; //zwracam flage
    //Zuzia
}
