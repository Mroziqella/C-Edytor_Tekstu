/**
******************* Edytor tekstu 2014/2015 *******************
********************** Autor: Mr�z Kamil **********************
****************** e-mail: mroziqella@o2.pl *******************
************ Github:https://github.com/Mroziqella *************
**/






#include <windows.h>// ustawienia konsoli, gotoxy
#include <conio.h>
#include "lista.h"
#include "interfejs.h"


int main()
{
    wezel lista,*adres;//tworzenie listy i wska�nika na pierwszy jej elemnt
    adres=&lista;
    int znacznikMenu=-1;//w kt�rym miejscu menu znajduje sie strza�ka -1 �eby by�o na pierwszym elemencie przy pierwszym wykonaniu petli
    int flag=0;// m�wi czy plik by� edytowany 0-nie by�, by�
    char znakWybor=80,zapis[100]="plik.txt",odczyt[100]="plik.txt";//znakwyboru pozwala na wejscie do petli i p�niej przechowuje wciskane klawisze
    int unsigned znakNumer=0,wierszNumer=0;//po�o�enie kursora na tekscie
    ////////////////////////////////////////////////////////////////////////////////////////
    SMALL_RECT windowSize = {0, 0,SZEROKOSC_KONSOLI,WYSOKOSC_KONSOLI}; //ustawienia konsoli
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);//ustawienia konsoli

    CONSOLE_CURSOR_INFO ci;//ukrywanie kursora
    HANDLE hC=GetStdHandle(STD_OUTPUT_HANDLE);// utworzenie uchwytu
    GetConsoleCursorInfo(hC, &ci);
    ci.bVisible=0;//ukrycie znaku zachety
    SetConsoleCursorInfo(hC, &ci);
    ////////////////////////////////////////////////////////////////////////////////////////
    ekranPowitalny();// wpypisje ekran powitalny
    ZerujL(adres);// zeruje wszystkie wska�niki na liscie
    gotoxy(22,16); //wypisanie tekstu w danym miejscu
    MENUWYPISZNOWY;//makro wypisujace menu
    while(znakWybor!=27)
    {
    CONSOLE_CURSOR_INFO ci;//urywanie kursora
    HANDLE hC=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hC, &ci);
    ci.bVisible=0;
    SetConsoleCursorInfo(hC, &ci);
        gprintf("    ",31,20+znacznikMenu);//zamazanie strzalki w menu
        switch(znakWybor)
        {
            case 80:{   //jezeli wcisniemy strzalke w d�
                    if (znacznikMenu<ROZMIAR_MENU-1)//zabezpiecza przed wyjsciem poza gorna granice menu
                        znacznikMenu++;
                    break;
                    }//end 80:
            case 72:{ //jezeli wcisniemy strzalk� w g�r�
                    if (znacznikMenu>0)//zabezpiecza przed wyjsciem poza doln� granice menu
                        znacznikMenu--;
                    break;
                    }//end 72:
            case 13: //jez�li wcisniemy enter
                    {
                    system("cls");//czy�ci ekran
                    PasekOpcjiGorny();//wypisuje tekst w nag��wku progaru(nazwa programu autorzy....)
                    wybierz(adres,&znakNumer,&wierszNumer,znacznikMenu,zapis,odczyt,&flag);//przechodzimy do funcji kt�ra wska�e jaka opcja w menu zosta�a wybrana
                    //argumenty funkcji to adres listy,licznik kolumn-znakNumer, licznik wierszy,sciezka zapisu pliku, odczytu pliku i flaga okre�laj�ca zmianae tekstu z nowy plik na kontynu�uj edycje
                    break;
                    }//end 13:
        }//end switch
        gprintf("===>",31,20+znacznikMenu);//wypisanie strzalki
        if ((wierszNumer==0)&&(znakNumer==0)&&(flag==0)){//sprawdza czy to jest nowy plik czy nie
            PasekOpcjiGorny();
            MENUWYPISZNOWY;
        }//end if
        else{
            PasekOpcjiGorny();
            MENUWYPISZKONTYNULUJ;
        }//end else
        gprintf(STEROWANIE_MENU_OPIS,0,WYSOKOSC_MENU_GORNEGO-2);//wyswietla teksc pomocniczy jakich przyciskow mozna u�ywa� w menu
        gprintf("MENU",WysrodkujTekst("MENU"),5);//wysrodkowuje napis menu
        znakWybor=getch();
    }//end while

    return 0;

}
