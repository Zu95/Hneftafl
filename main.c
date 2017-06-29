/*************************************
Hneftafl
Autorzy: Jedrzej Kubala, Zuzanna Krzysztofik

Program stworzony w ramach projektu na przedmiot Wprowadzenie Do Programowania
w roku 2016 na kierunku Elektroniczne Przetwarzanie Informacji.

Program umozliwia 2 graczom gre w Hneftafl - sredniowieczna skandynawska gre zwana Szachami Wikingow.
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include "gra.h"
#include "ruch.h"
#include "bicie.h"




int main() { //wprowadzenie, switch: zasady gry, instrukcja dzia³ania, gra, wyjscie
    int wybor;
    printf(" .-'-._,-'_`-._,-'_`-._,-'_`-._,-'_`-,_,-'_`-,_,-'_`-,_,-'_`-,_,-'_`-,.\n");
    printf("(  ,-'_,-<.>-'_,-<.>-'_,-<.>-'_,-<.>-'_,-<.>-'_,-<.>-'_,-<.>-'_,-~-} ;.\n");
    printf(" \\ \\.'_>-._`-<_>-._`-<_>-._`-<_>-._`-<_>-._`-<_>-._`-<_>-._`-._~--. \\ .\n");
    printf(" /\\ \\/ ,-' `-._,-' `-._,-' `-._,-' `-._,-' `-._,-' `-._,-' `-._`./ \\ \\ .\n");
    printf("( (`/ /                                                        `/ /.) ) .\n");
    printf(" \\ \\ / \\                                                       / / \\ / .\n");
    printf("  \\ \\') )                                                     ( (,\\ \\ .\n");
    printf(" / \\ / /   Zuzanna Krzysztofik i Jedrzej Kubala prezentuja     \\ / \\ \\ .\n");
    printf("  (`/ /                                                        / /.) ) .\n");
    printf(" \\ \\ / \\                                                       / / \\ / .\n");
    printf("  \\ \\') )                   HNEFTAFL                          ( (,\\ \\ .\n");
    printf(" / \\ / /                                                       \\ / \\ \\ .\n");
    printf("( (`/ /                 Szachy wikingow                         / /.) ) .\n");
    printf(" \\ \\ / \\                                                       / / \\ / .\n");
    printf("  \\ \\') )     1 - start                                       ( (,\\ \\ .\n");
    printf(" / \\ / /                                                       \ / \\ \\ .\n");
    printf("( ( / /       2 - instrukcja dzialania                          / /.) ) .\n");
    printf(" \\ \\ / \                                                       / / \\ /.\n");
    printf("  \\ \\') )     3 - zasady gry                                  ( (,\\ \\ .\n");
    printf(" / \\ / /                                                       \\ / \\ \\ .\n");
    printf("( ( / /       4 - wyjscie                                       / /.) ) .\n");
    printf(" \\ \\ / \\                                                       / / \\ / .\n");
    printf("  \\ \\') )                                                     ( (,\\ \\ .\n");
    printf(" / \\ / /                                                       \\ / \\ \\ .\n");
    printf("( ( / /                                                         / /.) ) .\n");
    printf(" \\ \\ / \\       _       _       _       _       _       _       / / \\ /.\n");
    printf("  \\ `.\\ `-._,-'_`-._,-'_`-._,-'_`-._,-'_`-._,-'_`-._,-'_`-._,-'_/,\\ \\ .\n");
    printf(" ( `. `,~-._`-<,>-._`-<,>-._`-<,>-._`-<,>-._`-<,>-._`-<,>-._`-<,' ,\\ \\ .\n");
    printf("  `. `'_,-<_>-'_,-<_>-'_,-<_>-'_,-<_>-'_,-<_>-'_,-<_>-'_,-<_>-'_,'-' ; .\n");
    printf("    `-' `-._,-' `-._,-' `-._,-' `-._,-' `-._,-' `-._,-' `-._,-' `-.-' .\n\n");

/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^*/
    while(scanf("%d", &wybor)){
        getchar();
        switch(wybor){
            case 1:           //gra
                gra();
                printf("1-nowa gra\n2-instrukcja\n3zasady\n4-wyjscie\n");
            break;
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
            case 2:             //instrukcja
                printf("           ,                                            \n");
                printf("       ,   |\ ,__                                       \n");
                printf("       |\   \/   `.         Gracz 1 - druzyna krolewska \n");
                printf("       \ `-.:.     `\       Gracz 2 - druzyna atakujaca \n");
                printf("        `-.__ `\=====|                                  \n");
                printf("           /=`'/   ^_\      Ruch wprowadzamy poprzez:   \n");
                printf("         .'   /\   .=)		a5a10 - z pola a5 ruszymy sie na a10 \n");
                printf("      .-'  .'|  '-(/_|		                            \n");
                printf("    .'  __(  \  .'`         Powodzenia!                 \n");
                printf("   /_.'`  `.  |`                                        \n");
                printf("            \ |                                         \n");
                printf("             |/                                         \n\n\n");
                printf("1-nowa gra\n2-instrukcja\n3zasady\n4-wyjscie\n");
            break;
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
            case 3:            //zasady gry
                printf("    ______           Zasady gry                                    \n");
                printf(" _  \\ \\ \\ \\    Druzyna krolewska ma za zadanie uciec               \n");
                printf("<'\\ /_/_/_/    krolem w ktores z pol naroznych                     \n");
                printf(" ((____!___/)                                                      \n");
                printf("  \\0\\0\\0\\0\\/   Druzyna atakujaca stara sie otoczyc krola           \n");
                printf(" ~~~~~~~~~~~   ze wszystkich stron, aby nie mogl sie ruszyc.       \n\n");

                printf(" Bicie odbywa sie poprzez przechwycenie pionka                     \n");
                printf(" - oskrzydlenie go z dwoch stron w linii prostej.                  \n");
                printf(" Dodatkowo bicie odbywa sie, gdy pionek stoi przy polu naroznym    \n");
                printf(" lub tronowym. Krol tez moze zbijac.                               \n\n");

                printf(" Kazdy pionek porusza sie o dowolna ilosc pol w linii prostej.     \n");
                printf(" Nie mozna przeskakiwac pionkow.                                   \n\n");

                printf(" Zwykle pionki nie moga stawac na polu tronowym lub                \n");
                printf(" na polach naroznych.                                              \n\n\n");
                printf("1-nowa gra\n2-instrukcja\n3zasady\n4-wyjscie\n");
            break;
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
            case 4: 			//wyjscie
                exit(0);
            break;
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
            default:
                printf("Bledna komenda. Prawdziwy wiking nie wprowadza blednych komend.Sprobuj jeszcze raz.\n\n");
                printf("1-nowa gra\n2-instrukcja\n3zasady\n4-wyjscie\n");

        }
/*\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^\_/^*/
    }
    return 0;
}
